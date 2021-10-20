#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    printf("Now only one process\n");

    printf("Calling fork...\n");

    pid = fork();

    if (!pid)
    {
        printf("I am the child pid=%d\n",pid );
    }
    else if (pid > 0)
        printf("I am the parent,chiled has pid%d", pid);
    else
        printf("fail\n");
    return 0;
}