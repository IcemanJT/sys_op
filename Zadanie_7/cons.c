/*
################

Jeremi Toroj, zadanie 7

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>

#include "semaphore.h"
#include "sm_lib.h"

#define NELE 10
#define NBUF 5

#define FAILURE -1

typedef struct
{
    char buffor[NBUF][NELE];
    int insert;
    int get;

} ShM_Segment;

int ifend(ShM_Segment *SHM)
{
    int i;
    for(i = 0; i < NELE; i++)
    {
        if(SHM->buffor[SHM->get][i] == '\0')
        {
            return 1;
        }
    }
    return 0;
}

int main(int argn, char *argv[])
{

    // argn check
    if (argn != 5)
    {
        printf("5 args expected {prod_semaph, cons_semaph, shm_name and dfile}.\n");
        exit(EXIT_FAILURE);
    }

    // variables - argv
    char *prod_semaph = argv[1];
    char *cons_semaph = argv[2];
    char *shm_name = argv[3];
    char *dfile = argv[4];
    int fd, shmdesc;

    // opening file to write only
    fd = open(dfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == FAILURE)
    {
        perror("open error.\n");
        exit(EXIT_FAILURE);
    }

    // producent semaphore
    sem_t *prod_semaph_address = open_semaph(prod_semaph);
    printf("Consumer: Address of producent's samephore: %p\n", (void *)prod_semaph_address);

    // consumer semaphore
    sem_t *cons_semaph_address = open_semaph(cons_semaph);
    printf("Consumer: Address of consumer's samephore: %p\n", (void *)cons_semaph_address);

    // opening shared memory
    shmdesc = open_sm(shm_name);

    // mapping shared memory
    ShM_Segment *SHM;
    SHM = (ShM_Segment *)map_sm(shmdesc, sizeof(ShM_Segment));
    printf("Consumer: Shared memory ad: %d, size of:%ld\n", shmdesc, sizeof(ShM_Segment));

    SHM->get = 0;

    // saving from shared memory to file
    while(1)
    {
        sleep(1);

        printf("\nConsumer: Value of consumer's samephore: %d\n", semaph_get_val(cons_semaph_address));
        // sem_wait() of cons
        semaph_down(cons_semaph_address);


        // reading from shared memory to file
        if (!(ifend(SHM)))
        {
            if (write (fd, SHM->buffor[SHM->get], NELE) == FAILURE)
            {
				perror("write error.\n");
				exit(EXIT_FAILURE);
			}

			if(write (STDOUT_FILENO, "Consumer: Data: ", 17) == FAILURE)
            {
				perror("write error.\n");
				exit(EXIT_FAILURE);
			}

			if(write (STDOUT_FILENO, SHM->buffor[SHM->get], NELE) == FAILURE)
            {
				perror("write error.\n");
				exit(EXIT_FAILURE);
			}

			printf ("\nConsumer: Buffor idx: %d\n", SHM->get);
        }
        else
        {
            if (write (fd, SHM->buffor[SHM->get], strlen (SHM->buffor[SHM->get])) == FAILURE)
            {
				perror("write error.\n");
				exit(EXIT_FAILURE);
			}
			printf ("    Consumer: Bytes: %ld Data: %s\n", strlen (SHM->buffor[SHM->get]), SHM->buffor[SHM->get]);
			printf ("Consumer end of file.\n");


			semaph_up(prod_semaph_address);
			printf ("Konsument: po SK semafor: %d\n", semaph_get_val(prod_semaph_address));

			break;
        }

        // idx incrementation
        SHM->get = (SHM->get + 1) % NBUF;

        // sem_wait()
        semaph_up(prod_semaph_address);

    }

    // closing file, shared memory and semaphore
    if (close(fd) == FAILURE)
    {
        perror("close error.\n");
        _exit(EXIT_FAILURE);
    }
    close_semaph(prod_semaph_address);
    close_semaph(cons_semaph_address);
    close_sm(shmdesc);

    printf("\nConsumer end.\n");

    _exit(EXIT_SUCCESS);
}
