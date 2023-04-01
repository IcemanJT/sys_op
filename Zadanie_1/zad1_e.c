/*
################

Jeremi Toroj, zadanie 1 e)

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define CHILD_PROCESS 0
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
        wait(NULL);
    }
    else if(id == CHILD_PROCESS)
    {
        printf("\nChild process: \n");
        val = setpgid(getpid(),0);
        if(val == FAILURE)
        {
            perror("Failed to change process lider");
            exit(EXIT_FAILURE);
        }
        DisplayInfo();
    }
    else
    {
        perror("Fork error\n");
        exit(EXIT_FAILURE);
    }
}

    return EXIT_SUCCESS;
}
