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

    int file_source, mf, bytes_num;
    char buffer[10];
    char *src_file = argv[1];
    char *fifo_path = argv[2];

    file_source = open(src_file, O_RDONLY, 0666);
    mf = open(fifo_path, O_WRONLY);

    while(1)
    {
        bytes_num = read(file_source, buffer, 6);

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
            if( write(mf, buffer, bytes_num) == FAILURE )
            {
                perror("write error.");
                _exit(EXIT_FAILURE);
            }
        }
    }

    close(mf);
    close(file_source);
    _exit(EXIT_SUCCESS);
}
