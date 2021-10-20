#include <stdio.h>

#define MAXSTRS 5

int main()
{
    int cntr;
    FILE *pipe_fp;
    char *strings[MAXSTRS] = {"roy", "zixia", "gouki", "supper", "mmwan"};
    /* 用 popen 建立管道 */

    if ((pipe_fp = popen("sort", "w")) == NULL)
    {
        perror("popen");
        exit(1);
    }

    for (cntr = 0; cntr < MAXSTRS; ++cntr)
    {
        fputs(strings[cntr], pipe_fp);
        fputc('\n', pipe_fp);
    }
    /* 关闭管道 */
    pclose(pipe_fp);
    return (0);
}