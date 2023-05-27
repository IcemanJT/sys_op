/*
################

Jeremi Toroj, zadanie 7

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

#include "semaphore.h"

#define FAILURE -1

sem_t *init_semaph(const char *name, int val)
{
    sem_t *semaph_adress;
    if( (semaph_adress = sem_open(name, O_CREAT | O_EXCL, 0644, val)) == SEM_FAILED)
    {
        perror("semaphore init error.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return semaph_adress;
    }
}

sem_t *open_semaph(const char *name)
{
    sem_t *semaph_adress;
    if( (semaph_adress = sem_open(name, 0)) == SEM_FAILED )
    {
        perror("semaphore open error.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return semaph_adress;
    }
}

int semaph_get_val(sem_t *sem)
{
    int semval;

    if( sem_getvalue(sem, &semval) == FAILURE )
    {
        perror("get val error.\n");
        exit(EXIT_FAILURE);
    }
    return semval;
}

void semaph_up(sem_t *sem)
{
    if( sem_post(sem) == FAILURE)
    {
        perror("sem post error.\n");
        exit(EXIT_FAILURE);
    }
}

void semaph_down(sem_t *sem)
{
    if( sem_wait(sem) == FAILURE )
    {
        perror("sem wait error.\n");
        exit(EXIT_FAILURE);
    }
}

void close_semaph(sem_t *sem)
{
    if( sem_close(sem) == FAILURE )
    {
        perror("sem close error.\n");
        exit(EXIT_FAILURE);
    }
}

void delete_semaph(const char *name)
{
    if( sem_unlink(name) == FAILURE )
    {
        perror("sem unlink error.\n.");
        exit(EXIT_FAILURE);
    }
}
