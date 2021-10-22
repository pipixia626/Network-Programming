#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 4000

#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
    int sock_fd, numbytes;

    char buf[MAXDATASIZE];

    struct hostent *he;

    struct sockaddr_in their_addr;

    if (argc != 3)
    {
        fprintf(stderr, "usage:client hostname\n");
        exit(1);
    }
    if ((he = gethostbyname(argv[2])) == NULL)
    {
        herror("gethostname");
        exit(1);
    }
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);

    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8);
   
    if (connect(sock_fd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    fprintf(stderr,"I am connect");
    if ((numbytes = recv(sock_fd, buf, MAXDATASIZE, 0)) == -1)
    {
        perror("recv");
        exit(1);
    }
    fprintf(stderr,"I am recv");
    buf[numbytes] = '\0';
    printf("Recevived%s", buf);
    close(sock_fd);
    return 0;
}
