#include <unistd.h>
// int lockf(int fd, int function, long size);
// 参数 fd 是在文件打开操作中获得的文件描述符；
// 参数 function 可以取如下的参数值：
// F_ULOCK 为一个先前锁定的区域解锁
// F_LOCK 锁定一个区域
// F_TLOCK 测试并锁定一个区域
// F_TEST 测试一个区域是否已经上锁。
// 参数 size 指明了从文件当前位置开始的一段连续锁定区域的长度，当 size 为 0 时，锁
// 定记录将由当前位置一直扩展到文件尾。
my_lock(int fd)
{
    /* 将文件指针移回文件头 */
    lseek(fd, 0L, 0);
    /* 锁定整个文件 */
    if (lockf(fd, F_LOCK, 0L) == -1)
    {
        perror("can't F_LOCK");
        exit(1);
    }
}
my_unlock(int fd)
{
    lseek(fd, 0L, 0);
    if (lockf(fd, F_ULOCK, 0L) == -1)
    {
        perror("can't F_UNLOCK");
        exit(1);
    }
}