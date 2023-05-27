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
#include <semaphore.h>
#include <string.h>

#include "sm_lib.h"
#include "semaphore.h"

#define NELE 10
#define NBUF 5
#define FAILURE -1

typedef struct
{
    char buffor[NBUF][NELE];
    int insert;
    int get;

} ShM_Segment;

int main(int argn, char *argv[])
{

    // argn check
    if (argn != 5)
    {
        printf("5 args expected {prod_semaph, cons_semaph, shm_name and sfile}\n");
        exit(EXIT_FAILURE);
    }

    // variables - argv
    char *prod_semaph = argv[1];
    char *cons_semaph = argv[2];
    char *shm_name = argv[3];
    char *sfile = argv[4];
    int fd, bytes_read, shmdesc;

    // opening file to read only
    fd = open(sfile, O_RDONLY, 0666);
    if (fd == FAILURE)
    {
        perror("open error.\n");
        exit(EXIT_FAILURE);
    }

    // producent semaphore
    sem_t *prod_semaph_address = open_semaph(prod_semaph);
    printf("Producent: Address of producent's samephore: %p\n", (void *)prod_semaph_address);

    // consumer semaphore
    sem_t *cons_semaph_address = open_semaph(cons_semaph);
    printf("Producent: Address of consumer's samephore: %p\n", (void *)cons_semaph_address);

    // opening shared memory
    shmdesc = open_sm(shm_name);

    // mapping shared memory
    ShM_Segment *SHM;
    SHM = (ShM_Segment *)map_sm(shmdesc, sizeof(ShM_Segment));
    printf("Producent: Shared memory ad: %d, size of: %ld\n", shmdesc, sizeof(ShM_Segment));

    SHM->insert = 0;

    // saving read bytes to shared memory
    while(1)
    {
        sleep(1);


        printf("\nProducent: Value of producent's samephore before CS: %d\n", semaph_get_val(prod_semaph_address));
        // sem_wait() of prod
        semaph_down(prod_semaph_address);

        // reading frome source file to shared memory
        bytes_read = read(fd, SHM->buffor[SHM->insert], NELE);
        if (bytes_read == FAILURE)
        {
            perror("read error.\n");
            _exit(EXIT_FAILURE);
        }

        if (bytes_read != NELE)
        {
            SHM->buffor[SHM->insert][bytes_read] = '\0';
            printf ("Producent:   Bytes read: %ld Data: %s\n", strlen (SHM->buffor[SHM->insert]), SHM->buffor[SHM->insert]);
			printf ("Producent end of file.\n");

			// cons sempahore up
			semaph_up(cons_semaph_address);
			printf("\nProducent: Value of producent's samephore after CS: %d\n", semaph_get_val(cons_semaph_address));

            break;
        }
        else
        {
            if(write (STDOUT_FILENO, "Producent:  Data: ", 19) == FAILURE)
            {
				perror("write error.\n");
				exit(EXIT_FAILURE);
			}
			if(write (STDOUT_FILENO, SHM->buffor[SHM->insert], NELE) == FAILURE)
            {
				perror("write error.\n");
				exit(EXIT_FAILURE);
			}
			printf ("\nProducent: Buffor index: %d\n", SHM->insert);
        }


        // idx incrementation
        SHM->insert = (SHM->insert + 1) % NBUF;

        // sem_post() for cons
        semaph_up(cons_semaph_address);

        printf("\nProducent: Value of producent's samephore after CS: %d\n", semaph_get_val(cons_semaph_address));
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

    printf("Producent end.\n");

    _exit(EXIT_SUCCESS);
}
