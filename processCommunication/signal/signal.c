#include<signal.h>
#include<stdio.h>
// 当一个信号的信号处理函数执行时，如果进程又接收到了该信号，该信
// 号会自动被储存而不会中断信号处理函数的执行，直到信号处理函数执行完毕再重新调用
// 相应的处理函数
//但是如果在信号处理函数执行时进程收到了其它类型的信号，该函数的执行就会被中
//断
int interrupt(){
    printf("Interupt called\n");
    sleep(3);
    printf("Interrupt Func called\n");
}

main(){
    signal(SIGINT,interrupt);
    printf("Interrupt set for SIGINT");
    sleep(10);
    printf("Program NORMAL ended\n");
    return;
}