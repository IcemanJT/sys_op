/*
################

Jeremi Toroj, zadanie 1 d)

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


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
        sleep(4-i); // 4 cuz max i is 2 (line #49)
    }
    else if(id == 0)
    {
        printf("\nChild process:\n");
        DisplayInfo();
        sleep(3-i);

    }
    else
    {
        perror("Fork error\n");
        exit(EXIT_FAILURE);
    }
}

    return EXIT_SUCCESS;
}
