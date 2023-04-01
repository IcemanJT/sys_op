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

int main(int argc, char *argv[])
{
// argv[1] - path to program
// argv[2] - program name

    if (argc != 3) // not needed cuz of makefile???
    {
        printf("Three args are needed.\n");
        exit(EXIT_FAILURE);
    }

int i, id, val;

printf("\nParent process: \n");
DisplayInfo();

for (i = 0; i < 3; i++)
{
    id = fork();

    if(id > 0)
    {}
    else if(id == CHILD_PROCESS)
    {
        if((val = execlp(argv[1], argv[2], NULL)) == EXIT_FAILURE)
        {
            perror("execlp() error.");
            _exit(EXIT_FAILURE); // _exit ?? 
        }
    }
    else
    {
        perror("fork() error.\n");
        exit(EXIT_FAILURE);
    }

    // parent process waits for ANY child process
    if(wait(NULL)==EXIT_FAILURE) // wait(NULL) == waitpid(-1, NULL, 0)
        {
            perror("wait() error - no processes to wait for.\n");
            exit(EXIT_FAILURE);
        }

}

    return EXIT_SUCCESS;
}
