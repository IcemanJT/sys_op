/*
################

Jeremi Toroj, zadanie 2.

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define CHILD_PROCESS 0

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

int i, id;

printf("\nParent process: \n");
DisplayInfo();

for (i = 0; i < 3; i++)
{
    id = fork();
    if(id > 0)
    {}
    else if(id == CHILD_PROCESS)
    {
        printf("\nChild process: \n");
        DisplayInfo();
    }
    else
    {
        perror("Fork error\n");
        exit(EXIT_FAILURE);
    }

    if(wait(NULL)==EXIT_FAILURE)
        {
            perror("Wait error");
            exit(EXIT_FAILURE);
        }

}

    return EXIT_SUCCESS;
}
