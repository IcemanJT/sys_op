/*
################

Jeremi Toroj, zadanie 5 - producer

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FAILURE -1

int main(int argn, char* argv[])
{
    if( argn != 3)
    {
        printf("Program needs 2 arguments.\n 1 - source, 2 - target\n");
        exit(EXIT_FAILURE);
    }

    int file_target, mf, bytes_num;
    char buffer[10];
    char *tgt_file = argv[1];
    char *fifo_path = argv[2];

    file_target = open(tgt_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    mf = open(fifo_path, O_RDONLY);

    while(1)
    {
        bytes_num = read(mf, buffer, 6);

        if( bytes_num == FAILURE )
        {
            perror("read error.");
            _exit(EXIT_FAILURE);
        }
        else if( bytes_num == 0)
        {
            break;
        }
        else
        {
            if( write(STDOUT_FILENO, buffer, bytes_num) == FAILURE )
            {
                perror("write error.");
                _exit(EXIT_FAILURE);
            }
            if( write(file_target, buffer, bytes_num) == FAILURE )
            {
                perror("write error.");
                _exit(EXIT_FAILURE);
            }
        }
    }

    close(mf);
    close(file_target);
    _exit(EXIT_SUCCESS);
}
