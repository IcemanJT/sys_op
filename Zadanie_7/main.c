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
#include <signal.h>
#include <semaphore.h>

#include "sm_lib.h"
#include "semaphore.h"

#define NELE 20
#define NBUF 5
#define CHILD_PROCESS 0

#define SOURCE_FILE "source.txt"
#define TARGET_FILE "source_copy.txt"

const char *prod_semaph = "prod_semaph";
const char *cons_semaph = "cons_semaph";
const char *sh_m = "shared_memory";

// atexit funcs
void remove_semaphore()
{
    delete_semaph(prod_semaph);
    delete_semaph(cons_semaph);
}

void remove_sh_m()
{
    delete_sm(sh_m);
}


// shared memory struct
typedef struct
{

    char buffor[NBUF][NELE];
    int insert;
    int get;

} ShM_Segment;

// shared memory variable(struct)
ShM_Segment SHM;

int main(int argn, char *argv[])
{

    // argn check
    if (argn != 3)
    {
        printf("Expected 3 args {source_file, target_file}\n");
        exit(EXIT_FAILURE);
    }

    // ctrl + c handler
    if (signal(SIGINT, remove_semaphore) == SIG_ERR)
    {
        perror("signal error.\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, remove_sh_m) == SIG_ERR)
    {
        perror("signal error.\n");
        exit(EXIT_FAILURE);
    }

    // variables
    sem_t *prod_semaph_address, *cons_semaph_address;
    int shmdesc, id1, id2;

    // semaphores init
    prod_semaph_address = init_semaph(prod_semaph, NBUF);
    printf("\nInit of prod's semaphore with\naddress: %p\nvalue: %d\n", (void *)prod_semaph_address, semaph_get_val(prod_semaph_address));

    cons_semaph_address = init_semaph(cons_semaph, 0);
    printf("\nInit of prod's semaphore with\naddress: %p\nvalue: %d\n", (void *)cons_semaph_address, semaph_get_val(cons_semaph_address));

    // shared memory init
    shmdesc = creat_sm(sh_m);
    sm_setlenght(shmdesc, sizeof(SHM));
    printf("\nShared memory:\naddress: %d\nsize: %ld\n", shmdesc, sizeof(SHM));

    // creating child processes to run exclp for prod and cons
    id1 = fork();

    if (id1 > 0)
    {
        id2 = fork();

        if (id2 > 0)
        {
            wait(NULL);
        }
        else if (id2 == CHILD_PROCESS)
        {
            execlp("./cons.x", argv[2] , prod_semaph, cons_semaph, sh_m, TARGET_FILE, NULL);
            perror("execlp error.\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("fork error.\n");
            exit(EXIT_FAILURE);
        }
        wait(NULL);
    }
    else if (id1 == CHILD_PROCESS)
    {
        execlp("./prod.x", argv[1], prod_semaph, cons_semaph, sh_m, SOURCE_FILE, NULL);
        perror("execlp error.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        perror("fork error.\n");
        exit(EXIT_FAILURE);
    }

    // atexit funcs
    atexit(remove_semaphore);
    atexit(remove_sh_m);

    printf("\nMain end.\n");

    exit(EXIT_SUCCESS);
}
