// int flock(int fd, int operation);
// 调用 flock 有两个参数：
// 参数 fd 是一个已打开文件的文件描述符；
// 参数 operation 可设定为下述各值：
// LOCK_SH 共享锁
// LOCK_EX 互斥锁
// LOCK_UN 解锁
// LOCK_NB 当文件已被锁定时不阻塞
// 使用 flock()来请求对指定文件的咨询式锁定和解锁。4.3BSD 的咨询锁
// 有共享锁和互斥锁两种。在任一给定时刻，多个进程可以用于属于同一文件的共享锁，但
// 是某共享文件不能同时具有多个互斥锁或存在共享锁和互斥锁共存的情况。如果锁定成功，
// flock 将返回零，否则返回-1。

// flock()允许的锁操作有下列几种：
// LOCK_SH 阻塞性共享锁
// LOCK_EX 阻塞性互斥锁
// LOCK_SH | LOCK_NB 非阻塞性共享锁
// LOCK_EX | LOCK_NB 非阻塞性互斥锁
// LOCK_UN 解锁
#include <sys/file.h>
my_flock(int fd)
{
    if (flock(fd, LOCK_EX) == -1)
        {
            perror("can't LOCK_EX");
            exit(1);
        }
}
my_unload(fd)
{
    if (flock(fd, LOCK_UN) == -1)
    {
        perror("can’t LOCK_UN");
        exit(1);
    }
}
