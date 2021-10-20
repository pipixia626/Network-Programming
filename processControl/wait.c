#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
// 通过 exit 返回给父进程之值
// 存放在 exit_status 的低位中，为了使其有意义，exit_status 的高 8 位必须为 0（注意，在整
// 型量中，低 8 位在前，高 8 位在后）。因此从 wait()返回后，就可以用按位与操作进行测试，
// 如果它们不为 0，表示该子进程是被另一个进程用一种称为信号的通信机构停止的，而不
// 是通过 exit()结束的。

main()
{
    int pid, status, exit_status;
    if ((pid = fork()) < 0)
    {
        perror("fork failed");
        exit(1);
    }
    if (!pid)
    {
        //child process
        sleep(4);
        exit(5); /* 使用非零值退出，以便主进程观察 */
    }
    //father process
    if (wait(&status) < 0)
    {
        perror("wait failed");
        exit(1);
    }
    /* 将 status 与 0xFF(255)与来测试低 8 位 */
    if (status & 0xFF)
        printf("Somne low-roderbits not zero\n");
    else
    {
        exit_status = status >> 8;
        exit_status &= 0xFF;
        printf("Exit status from %d was %d\n", pid, exit_status);
    }
    exit(0);

}