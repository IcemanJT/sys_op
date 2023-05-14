/*
################

Jeremi Toroj, zadanie 5(a)

################
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SUCCESS 0
#define FAILURE -1
#define CHILD_PROCESS 0


#define MYFIFO "/tmp/myfifo"

// function deleting pipe
void close_pipe()
{
    if( remove(MYFIFO) != SUCCESS )
    {
        perror("close_pype error.");
        exit(EXIT_FAILURE);
    }
}


int main(int argn, char* argv[])
{

    // args number val
    if( argn != 3)
    {
        printf("Program needs 2 arguments.\n 1 - source, 2 - target\n");
        exit(EXIT_FAILURE);
    }

    // deleting pipe at exit
    atexit(close_pipe);
    int id, val, id2;
    char *src_file = argv[1];
    char *tgt_file = argv[2];

    // creating named pipe
    if( ( val = mkfifo(MYFIFO , 0666) ) == FAILURE )
    {
        perror("fifo_pipe error.\n");
        exit(EXIT_FAILURE);
    }

    id = fork();

    // parent process
    if( id > 0 )
    {
        // creating another child
        id2 = fork();
        if (id2 > 0)
        {
            wait(NULL);
        }
        else if (id2 == CHILD_PROCESS)
        {
            execlp("./cons.x", "cons.x", tgt_file, MYFIFO, NULL);
            perror("execlp error\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
        wait(NULL);
    }
    else if( id == CHILD_PROCESS)
    {
        execlp("./prod.x", "prod.x", src_file, MYFIFO, NULL);
        perror("execlp error\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }


    // exit cuz of atexit()
    exit(EXIT_SUCCESS);
}
