/*
################

Jeremi Toroj, zadanie 4

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

#define FAILURE -1
#define CHILD_PROCESS 0
#define BUFFERSIZE 15
#define READSIZE 11



int main()
{
    int id, filedes[2], fsource, val, data, data1, random_value, fread;
    char buffer[100], reader[100];
    char statement[255];

    srand(time(NULL));

    if( ( val = pipe(filedes) ) == -1 )
    {
        perror("pipe error.\n");
        exit(EXIT_FAILURE);
    }

    id = fork();


    if( id > 0)
    {
        // opening file
        if( ( fsource = open("text.txt", O_RDONLY , 0644) ) == FAILURE )
        {
            perror("open error.\n");
            exit(EXIT_FAILURE);
        }

        // closing not needed file descriptor
        if( ( val = close(filedes[0]) ) == FAILURE )
        {
            perror("close error.\n");
            exit(EXIT_FAILURE);
        }


        while(1)
        {
            // waiting for rand_value of sec
            random_value = rand() % 3;
            sleep(random_value);

            data = read(fsource, &buffer, BUFFERSIZE);

            if( data == FAILURE )
            {
                perror("read error.\n");
                exit(EXIT_FAILURE);
            }
            else if( data == 0 )
            {
                break;
            }
            else
            {
                // writing to pipe
                if ( ( val = write(filedes[1], &buffer, data) ) == FAILURE )
                {
                    perror("write error 1.\n");
                    exit(1);
                }

                // writing to console
                buffer[data]='\0';
                sprintf(statement, "%s %s", "\nPrinting to pipe:", buffer );
                if( ( val = write(STDOUT_FILENO, statement, strlen(statement)) ) == FAILURE )
                {
                    perror("write error 2.\n");
                    exit(1);
                }
            }
        }

        // freeing file descriptor
        if( ( val =close(fsource) ) == FAILURE )
        {
            perror("close error.\n");
            exit(EXIT_FAILURE);
        }
    }
    else if ( id == CHILD_PROCESS )
    {
        // opening/creating file to copy source
        if( ( fread = open("text_copy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644) ) == FAILURE)
        {
            perror("open error.\n");
            exit(EXIT_FAILURE);
        }

        // closing not needed file descriptor
        if( ( val = close(filedes[1]) ) == FAILURE )
        {
            perror("close error.\n");
            exit(EXIT_FAILURE);
        }

        do
        {
            // waiting for rand_value of sec
            random_value = rand() % 3;
            sleep(random_value);

            data1 = read(filedes[0], &reader, READSIZE);


            if( ( val = write(fread, &reader, data1) ) == FAILURE )
            {
                perror("write error 3.\n");
                exit(EXIT_FAILURE);
            }

            reader[data1]='\0';
            sprintf(statement, "%s %s", "\nCopying to new file:", reader );
            if( ( val = write(STDOUT_FILENO, statement, strlen(statement)) ) == FAILURE )
            {
                perror("write error.\n");
                exit(1);
            }

        } while(data1 != 0);

        // freeing file descriptor
        if ( ( val =close(fread) ) == FAILURE )
        {
            perror("close error.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("fork error.\n");
        exit(EXIT_FAILURE);
    }

    

    return EXIT_SUCCESS;
}
