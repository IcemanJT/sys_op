/*
################

Jeremi Toroj, zadanie 3(a)

################
*/



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


#define DEFAULT 1
#define IGNORE 2
#define USER 3


void sig_handler(int sig)
{
    printf("Custom signal handler for signal %d in action.\n", sig);
}




int main(int argc, char *argv[])
{

    char err[20];

    if ( argc != 3)
    {
        printf("Wrong number of args, 3 expected.\n");
        exit(EXIT_FAILURE);
    }

    int sig_num = atoi(argv[1]);
    int sig_act = atoi(argv[2]);


    if (sig_act != DEFAULT && sig_act != IGNORE && sig_act != USER)
    {
        printf("Wrong first arg, expected 1, 2 or 3.\n");
        exit(EXIT_FAILURE);
    }

    if ( sig_act == DEFAULT )
    {
        printf("Default signal handler for signal: %d.\n", sig_num );
        if ( signal( sig_num, SIG_DFL ) == SIG_ERR )
        {
            sprintf(err, "Signal %d %s", sig_num, "error.\n");
            perror(err);
            exit(EXIT_FAILURE);
        }
    }

    if ( sig_act == IGNORE )
    {
        printf("Ignore signal handler for signal: %d.\n", sig_num );
        if ( signal( sig_num, SIG_IGN ) == SIG_ERR )
        {
            sprintf(err, "Signal %d %s", sig_num, "error.\n");
            perror(err);
            exit(EXIT_FAILURE);
        }
    }

    if ( sig_act == USER )
    {
        if ( signal( sig_num, sig_handler ) == SIG_ERR )
        {
            sprintf(err, "Signal %d %s", sig_num, "error.\n");
            perror(err);
            exit(EXIT_FAILURE);
        }
    }

    pause();

    return 0;
}
