#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// Before fork: 10
// Child before read: 10
// child after read: 20
// parent after wait: 20
failure(char *s)
{
    perror(s);
    exit(1);
}
//show the pos of a floder' pointer
printpos(char *string, int fildes)
{
    long pos;
    if ((pos == lseek(fildes, 0L, 1)) < 0L)
        failure("lseek failed");
    printf("%s:%ld\n", string, pos);
}

main()
{
    int fd;
    int pid;
    char buf[10];
    if ((fd == open("data", O_RDONLY)) < 0)
        failure("open failed");
    read(fd, buf, 10);
    printpos("before fork", fd);
    if ((pid = fork()) < 0)
        failure("fork failed");
    else if (!pid)
    {
        /* 子进程 */
        printpos("Child before read", fd);
        read(fd, buf, 10);
        printpos("child after read", fd);
    }
    else
    {
        /* 父进程 */
        /* 等待子进程运行结束 */
        wait(NULL);
        printpos("parent after wait", fd);
    }
}