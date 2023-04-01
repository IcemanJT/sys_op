/*
################

Jeremi Toroj, zadanie 1 a)

################
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("user id: %d\n",getuid());
    printf("user group id: %d\n",getgid());
    printf("process id: %d\n",getpid());
    printf("parent process id: %d\n",getppid());
    printf("process group id: %d\n",getpgid(0));

    return 0;
}