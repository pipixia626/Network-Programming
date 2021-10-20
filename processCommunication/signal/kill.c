// 建立两个进程，并通过向对方发
// 送信号 SIGUSR1 来实现它们之间的同步。这两个进程都处于一个死循环中，在接收对方发
// 送的信号之前，都处于暂停等待中。这是通过系统调用 pause()来实现的，它能够使一个程
// 序暂停，直至一个信号到达，然后进程输出信息，并用 kill 发送一个信号给对方。当用户
// 按了中断键，这两个进程都将终止。
#include <signal.h>

int ntimes = 0;
p_action()
{
    printf("Patent caught signal #%d\n", ++ntimes);
}
c_action()
{
    printf("Child caught signal #%d\n", ++ntimes);
}

main()
{
    int pid, ppid;
    int p_action(), c_action();
    signal(SIGUSR1, p_action);

    switch (pid = fork())
    {
    case -1:
        perror("synchro");
        exit(1);
    case 0:
        signal(SIGUSR1, c_action);

        ppid = getppid();
        for (;;)
        {
            sleep(1);
            kill(ppid, SIGUSR1);
            pause();
        }
        break;
    default:
        for (;;)
        {
            pause();
            sleep(1);
            kill(pid, SIGUSR1);
        }
        /*死循环*/
    }
}