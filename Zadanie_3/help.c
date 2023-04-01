/*
################

Jeremi Toroj, program do zadania 3(c)

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define CHILD_PROCESS 0
#define FAILURE -1


int main(int argc, char *argv[])
{

    if ( argc != 3)
    {
        printf("Wrong number of args, 3 expected.\n");
        exit(EXIT_FAILURE);
    }

    char err[50];
    char *signumber_str = argv[1];
    char *sigaction_str = argv[2];
    int signumber_int = atoi(argv[1]);

    int id, val, status;
    id = fork();

    if( id > 0 )
    {
        printf("Main child process ignoring signal.\n");
        if ( signal( signumber_int, SIG_IGN ) == SIG_ERR )
        {
            sprintf(err, "Signal %d %s", signumber_int, "error.\n");
            perror(err);
            exit(EXIT_FAILURE);
        }
    }
    else if( id == CHILD_PROCESS )
    {
        if((val = execlp("./zad3_a.x", "zad3_a.x", signumber_str, sigaction_str, NULL)) == FAILURE)
        {
            // execlp error
            perror("execlp() error.\n");
            _exit( EXIT_FAILURE );
        }
    }
    else
    {
        perror("Fork error\n");
        exit(EXIT_FAILURE);
    }



    // waiting
    if ( ( wait( &status ) )  == EXIT_FAILURE )
        {
            perror("wait() error - no processes to wait for.\n");
            exit( EXIT_FAILURE );
        }
    else
    {
        printf("\nPID of child process: %d\n", id);
        if ( WIFSIGNALED(status) )
        {
            printf("Process exit status: %d.\n", WTERMSIG(status));
            printf("Signal name: %s\n", strsignal(WTERMSIG(status)) );
        }
    }

    return 0;
}
