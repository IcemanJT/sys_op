/*
################

Jeremi Toroj, zadanie 6

################
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <time.h>

#include "semaphore.h"

#define FAILURE -1

int counter = 1;

void criticalsection(sem_t *semaph_address)
{
    srand(time(NULL));



    printf("        Process %d is executing critical section nr %d.\n", getpid(), counter);
    counter++;

    // variables
    int fide, val;
    char buffer[12];
    char buffer2[12];

    // opening file to read
    fide = open("numer.txt", O_RDONLY, 0666);

    if (fide == FAILURE)
    {
        perror("open error.\n");
        _exit(EXIT_FAILURE);
    }

    if (read(fide, buffer, 12) == FAILURE)
    {
        perror("read error.\n");
        _exit(EXIT_FAILURE);
    }

    printf("Number read from file: %s\n", buffer);

    if (close(fide) == FAILURE)
    {
        perror("close error.\n");
        _exit(EXIT_FAILURE);
    }

    // read number to int and ++
    int number = strtol(buffer, NULL, 0);
    number++;

    // int to char
    if (sprintf(buffer2, "%d", number) < 0)
    {
        perror("sprintf error.\n");
        _exit(EXIT_FAILURE);
    }

    sleep(rand() % 3);

    // opening file to write
    fide = open("numer.txt", O_WRONLY, 0666);
    if (fide == FAILURE)
    {
        perror("open error.\n");
        _exit(EXIT_FAILURE);
    }

    if (write(fide, buffer2, 12) == FAILURE)
    {
        perror("write error.\n");
        _exit(EXIT_FAILURE);
    }

    // semaphore value and closing file
    val = semaph_get_val(semaph_address);
    printf("Value of semaphore in critial section: %d\n", val);
    if (close(fide) == FAILURE)
    {
        perror("File closing error\n");
        _exit(EXIT_FAILURE);
    }
}

int main(int argn, char *argv[])
{

    srand(time(NULL));

    // argn check
    if (argn != 3)
    {
        printf("Expected 3 args: semaph_adress, crits_num.\n");
        _exit(EXIT_FAILURE);
    }

    // variables and opening semaphore
    char *semaph = argv[2];
    sem_t *semaph_address = open_semaph(semaph);
    int i, value;
    int crits_num = strtol(argv[1], NULL, 0);

    for (i = 0; i < crits_num; i++)
    {
        // pid and semaphore val
        printf("Process %d is looping for the %dth time\n", getpid(), i + 1);
        value = semaph_get_val(semaph_address);
        printf("Value of semaphore before critial section: %d\n", value);

        // simulaction of process time
        semaph_down(semaph_address);

        sleep(rand() % 3);
        // cirt section
        criticalsection(semaph_address);
        semaph_up(semaph_address);

        // semaphore val
        value = semaph_get_val(semaph_address);
        printf("Value of semaphore after critial section: %d\n\n", value);
    }


    _exit(EXIT_SUCCESS);
}
