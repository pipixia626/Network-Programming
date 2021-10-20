#include <strings.h>
#include <unistd.h>
//使用 getpid 产生一个唯一的临时文件名，
static int num = 0;
static char namebuf[20];
static char prefix[] = "/tmp/tmp";

char *gentemp()
{
    int length, pid;
    /* 获得进程标识符 */
    pid = getpid();
    strcpy(namebuf, prefix);
    length = strlen(namebuf);

    /* 在文件名中增加 pid 部分 */
    itoa(pid, &namebuf[length]);
    strcat(namebuf, ".");

    length = strlen(namebuf);
    do
    {
        /* 增加后缀 number */
        itoa(num++, &namebuf[length]);

    } while (access(namebuf, 0) != -1);
    return namebuf;
}