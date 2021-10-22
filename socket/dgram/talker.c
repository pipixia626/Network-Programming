#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 5000
int main(int argc, char *argv[])
{

    int sock_fd;
    struct sockaddr_in their_addr;
    struct hostent *he;
    int numbytes;

    if (argc != 3)
    {
        fprintf(stderr, "usage:talker hostname message\n");
        exit(1);
    }

    if ((he = gethostbyname(argv[1])) == NULL)
    {
        herror("gethostbyname");
        exit(1);
    }
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(MYPORT);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);

    bzero(&(their_addr.sin_zero), 8);
    if ((numbytes = sendto(sock_fd, argv[2], strlen(argv[2]), 0,
                           (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
    {
        perror("recvform");
        exit(1);
    }

    printf("sent % d bytes to % s\n", numbytes, inet_ntoa(their_addr.sin_addr));
    /* 关闭套接字描述符后退出 */
    close(sock_fd);
    return 0;
}