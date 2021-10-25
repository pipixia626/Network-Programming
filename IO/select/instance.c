#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include<assert.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage:%s ip_address port_number \n", basename(argv[0]));
        return 1;

    }
    const char*ip=argv[1];
    int port=atoi(argv[2]);

    int ret=0;
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    int listenfd=socket(PF_INET,SOCK_STREAM,0);

    assert(listenfd>=0);
    ret=bind(listenfd,(struct sockaddr*)&address,sizeof(address));
    assert(ret!=-1);
    ret=listen(listenfd,5);
    assert(ret!=-1);

    struct sockaddr_in client_address;
    socklen_t client_addlength=sizeof(client_address);
    int connfd=accept(listenfd,(struct sockaddr*)&client_address,&client_addlength);

    if(connfd<0){
        printf("error is %d\n",errno);
        close(listenfd);
    }
    char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);

    while (1)
    {
        memset(buf,'\0',sizeof(buf));

        FD_SET(connfd,&read_fds);
        FD_SET(connfd,&exception_fds);

        ret=select(connfd+1,&read_fds,NULL,&exception_fds,NULL);
        if(ret<0){
            printf("select error");
            break;
        }

        if(FD_ISSET(connfd,&read_fds)){
            //do recv
        }
        else if(FD_ISSET(connfd,&exception_fds)){
            //do recv
        }
    }
    close(connfd);
    close(listenfd);
    return 0;
    
}
