/*
################

Jeremi Toroj, zadanie 1 c)

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define FAILURE -1

void DisplayInfo()
{
    printf("user id: %d\n",getuid());
    printf("user group id: %d\n",getgid());
    printf("process id: %d\n",getpid());
    printf("parent process id: %d\n",getppid());
    printf("process group id: %d\n",getpgid(0));
}


int main()
{

int i, id, val;

char tree[50];

for (i = 0; i < 3; i++)
{

    id = fork();

    if(id > 0)
    {
        if(i == 0)
        {
            printf("\nParent process: \n");
            DisplayInfo();
        }
    }
    else if(id == 0)
    {
        sleep(2);

        printf("\nChild process:\n");
        DisplayInfo();

        sprintf(tree, "pstree -p -s %d\n", getpid());
        val = system(tree);
        if (val == FAILURE)
        {
            perror("System funtion failure.\n");
            exit(EXIT_FAILURE);
        }

    }
    else
    {
        perror("Fork error\n");
        exit(EXIT_FAILURE);
    }
}

    return EXIT_SUCCESS;
}
