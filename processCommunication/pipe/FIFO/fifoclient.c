#include <stdlib.h>
#include <stdio.h>

#define FIFO_FILE "sampleFIFO"

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc != 2)
    {
        printf("UASGE:fifoclieny[string]\n");
        exit(1);
    }

    /*打开有名管道*/
    if ((fp = fopen(FIFO_FILE, "w")) == NULL)
    {
        perror("fopen");
        exit(1);
    }
    /*向有名管道中写入数据*/
    fputs(argv[1], fp);
    /*关闭有名管道*/
    close(fp);
    return 0;
}