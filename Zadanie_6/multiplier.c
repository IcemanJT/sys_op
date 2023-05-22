/*
################

Jeremi Toroj, zadanie 6

################
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "semaphore.h"

#define FAILURE -1
#define CHILD_PROCESS 0


const char *semaph = "named_sem";
int sem_val;

void atex()
{
    delete_semaph(semaph);
}


int main(int argn, char *argv[])
{
    // at exit function deleting semaphore
    atexit(atex);

    // argn check
    if( argn != 4 )
    {
        printf("Expected 4 args: prog_name, number of proc, number of crits.\n");
        exit(EXIT_FAILURE);
    }

    // variables
    sem_t *semaph_address;
    int i, id, fide;
    char buffer[20];


    // defining variables
    char *program_name = argv[1];
    char *crits_num = argv[3];
    char program_path[50]={0};
    strncat(program_path, "./", 3);
    strncat(program_path, program_name, 20);
    int process_num = strtol(argv[2], NULL, 0);

    // semaphore init
    semaph_address = init_semaph(semaph);
    printf("Semaphore address: %p\n", (void *)semaph_address );
    printf("Semaphore init val: %d\n\n", semaph_get_val(semaph_address) );


    // creating numer.txt and writing 0
    fide = open("numer.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fide == FAILURE)
    {
        perror("open error.\n");
        exit(EXIT_FAILURE);
    }

    if (write(fide, "0", 2) == FAILURE)
    {
        perror("write error.\n");
        exit(EXIT_FAILURE);
    }

    if (close(fide) == FAILURE)
    {
        perror("close error.\n");
        exit(EXIT_FAILURE);
    }

    // creating child processes
    for (i = 0; i < process_num; i++)
    {
        id = fork();
        if (id > 0) // pid
        {
            // ctrl + c handler
            if (signal(SIGINT, atex) == SIG_ERR)
            {
                perror("signal error.\n");
                exit(EXIT_FAILURE);
            }
            sleep(1);
        }
        else if (id == CHILD_PROCESS)
        {
            execlp(program_path, program_name, crits_num, semaph, NULL);
            perror("execlp error.\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("fork error.\n");
            exit(EXIT_FAILURE);
        }
    }

    // ctrl + c handler not needed (?) alrdy in for loop (?)
    if (signal(SIGINT, atex) == SIG_ERR)
    {
        perror("signal error.\n");
        exit(EXIT_FAILURE);
    }

    // waiting for all child processes
    for (i = 0; i < process_num; i++)
    {
        if (waitpid(-1, NULL, 0) == FAILURE)
        {
            perror("wait error.\n");
            exit(EXIT_FAILURE);
        }
    }

    // opening file to read
    fide = open("numer.txt", O_RDONLY, 0666);
    if (fide == FAILURE)
    {
        perror("open error.\n");
        exit(EXIT_FAILURE);
    }

    // reading result from a file
    if (read(fide, buffer, 12) == FAILURE)
    {
        perror("read error.\n");
        exit(EXIT_FAILURE);
    }

    // result to int val
    int check = strtol(buffer, NULL, 0);

    // validation
    if (check == (atoi(crits_num) * process_num))
    {
        printf("Number saved in numer.txt file is correct.\n");
        printf("Number value: %d\n", check);
    }
    else
    {
        printf("Number saved in numer.txt file is incorrect.\n");
        printf("Number value: %d\n", check);
    }

    // closing file
    if (close(fide) == FAILURE)
    {
        perror("File closing error\n");
        exit(EXIT_FAILURE);
    }


    exit(EXIT_SUCCESS);
}
