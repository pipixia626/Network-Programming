#include <stdio.h>
#include <unistd.h>

int docommand(char *command)
{
    int pid;
    switch (pid = fork())
    {

    case -1:
        return -1;
    case 0:
        //not using exec to run but exec to run shell to do ls
        execl("/bin/sh", "sh", "-c", command, NULL);
        exit(127);
    default:
        wait(NULL);
    }
    return 0;
}
main()
{
    int pid;
    /*fork child process*/
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork falied\n");
        exit(1);
    case 0:
        execl("/bin/ls", "ls", "-l", "--color", NULL);
        perror("execl faild\n");
        exit(1);
    default:
        wait(NULL);
        printf("ls completed\n");
        exit(0);
    }
}