/*
################

Jeremi Toroj, zadanie 3(b)

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
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

    int id, val, status;
    char *signumber_str = argv[1];
    char *sigaction_str = argv[2];
    int signumber_int = atoi(argv[1]);

    id = fork();

    if(id > 0)
    {
        // waiting for child process
        sleep(1); // sleep? else ends too soon ?

        // checking if child process exists ??
        while ( kill(id, 0) == FAILURE || errno == ESRCH )
        {
            errno = ECHILD; // error - no child process
        }

        // sanding signal
        kill(id, signumber_int);

    }
    else if (id == CHILD_PROCESS)
    {

        // signumber_str, signumber_str - signal nr and action for execlp
        if((val = execlp("./zad3_a.x", "zad3_a.x", signumber_str, sigaction_str, NULL)) == EXIT_FAILURE)
        {
            // execlp error
            perror("execlp() error.\n");
            _exit( EXIT_FAILURE );
        }

    }
    else
    {

        // fork error
        perror("fork() error.\n");
        exit( EXIT_FAILURE );

    }


    // waiting for all child processes to end
    if ( ( wait( &status ) )  == EXIT_FAILURE )
        {
            perror("wait() error - no processes to wait for.\n");
            exit( EXIT_FAILURE );
        }
    else
    {
        if ( WIFSIGNALED(status) ) // checking if proces was terminated with signal
        {
            printf("Process exit status: %d.\n", WTERMSIG(status));
            printf("Signal name: %s\n", strsignal(WTERMSIG(status)) );
        }
    }




    return EXIT_SUCCESS;
}
