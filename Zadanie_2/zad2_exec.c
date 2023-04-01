/*
################

Jeremi Toroj, zadanie 2.
plik do wywolania poprzec execlp

################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("\nChild process:\n");
    printf("user id: %d\n",getuid());
    printf("user group id: %d\n",getgid());
    printf("process id: %d\n",getpid());
    printf("parent process id: %d\n",getppid());
    printf("process group id: %d\n",getpgid(0));

    return 0;
}
