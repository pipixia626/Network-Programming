#include<stdio.h>
#include<unistd.h>
// Linux 还提供了系统调用 exec 系列，它可
// 以用于新程序的运行。exec 系列中的系统调用都完成相同的功能，它们把一个新程序装入
// 调用进程的内存空间，来改变调用进程的执行代码，从而形成新进程。如果 exec 调用成功，
// 调用进程将被覆盖，然后从新程序的入口开始执行。这样就产生了一个新的进程，但是它
// 的进程标识符与调用进程相同。这就是说，exec 没有建立一个与调用进程并发的新进程，
// 而是用新进程取代了原来的进程
int main(){

    printf("running ls\n");

    execl("/bin/ls","ls","-l",NULL);

    perror("execl failed to run ls");
    exit(1);
}