# Socket
套接字是通过标准的unix文件描述符和其他的进程通讯的一个方法



## 本质
提供了进程通信的端点，进程通信之前都必须各自创建一个端点
每一个Socket都用一个半相关的描述
{协议，本地地址，本地端口}；
一个完整的Socket则用一个相关描述
{协议，本地地址，本地端口，远程地址，远程端口}
每一个 Socket 有一个本地的唯一 Socket 号，由操作系统分配

Socket 是面向客户－服务器模型而设计的，针对客户和服务器程序提供
不同的 Socket 系统调用。客户随机申请一个 Socket 号

## 套接字三种类型

### 流式套接字(SOCK_STREAM)
流式的套接字可以提供可靠的、面向连接的通讯流。如果你通过流式套接字发送了顺
序的数据：“1”、“２”。那么数据到达远程时候的顺序也是“１”、“２”。 

使用了TCP

### 数据报套接字(SOCK_DGRAM)
数据报套接字定义了一种无连接的服务，数据通过相互独立的报文进行传输，是无序
的，并且不保证可靠，无差错。原始套接字允许对低层协议如 IP 或 ICMP 直接访问，主要
用于新的网络协议实现的测试等。

使用了UDP

为什么说它们是“无连接”的呢？因为它（UDP）不像流式套接字那样维护一个打开的连接，你只需要把数据打成一个包，把远程的 IP 贴上去，然后把这个包发送出去。这个
过程是不需要建立连接的。UDP 的应用例子有： tftp, bootp 等。

### 原始套接字
原始套接字主要用于一些协议的开发，可以进行比较底层的操作。它功能强大，但是
没有上面介绍的两种套接字使用方便，一般的程序也涉及不到原始套接字。

## TCP/IP分类

### 控制数据的协议
1. TCP（传输控制协议 Transmission Control Protocol）以连接为基础，也就是说两台电脑
必须先建立一个连接，然后才能传输数据。事实上，发送和接受的电脑必须一直互相通讯
和联系。
2. UDP（使用者数据报协议 User Datagram Protocol）它是一个无连接服务，数据可以直接发送而不必在两台电脑之间建立一个网络连接。它和有连接的 TCP 相比，占用带宽少，
但是你不知道你的数据是否真正到达了你的客户端，而客户端收到的数据也不知道是否还
是原来的发送顺序。
### 数据路由协议
路由协议分析数据包的地址并且决定传输数据到目的电脑最佳路线。他们也可以把大的数据分成几部分，并且在目的地再把他们组合起来。
1. IP（因特网协议 Internet Protocol）处理实际上传输数据。
2. ICMP（因特网控制信息协议 Internet Control Message Protocol）处理 IP 的状态信息，
比如能影响路由决策的数据错误或改变。
3. RIP（路由信息协议 Routing Information Protocol）它是几个决定信息传输的最佳路由
路线协议中的一个。
4. OSPF（Open Shortest Path First）一个用来决定路由的协议。网络地址协议决定了命名电脑地址的方法：使用一个唯一的数字和一个字母名字。
5. ARP（地址决定协议 Address Resolution Protocol）确定网络上一台电脑的数字地址。
DNS（域名系统 Domain Name System）从机器的名字确定一个机器的数字地址。
RARP（反向地址决定协议 Reverse Address Resolution Protocol）确定网络上一台计算
机的地址，和 ARP（地址决定协议 Address Resolution Protocol）正好相反。
### 用户服务
1. FTP（文件传输协议 File Transfer Protocol）通过国际互连网从一台计算机上传输一个
或多个文件到另外一台计算机。
TELNET（远程登陆）允许一个远程登陆，使用者可以从网络上的一台机器通过 TELNET
连线到另一台机器，就像使用者直接在本地操作一样。
2. EGP（外部网关协议 Exterior Gateway Protocol）为外部网络传输路由信息。
3. GGP（网关到网关协议 Gateway-to-Gateway Protocol）在网关和网关之间传输路由协
议。
4. IGP（内部网关协议 Interior Gateway Protocol）在内部网络传输路由信息。
3．其他协议(也为网络提供了重要的服务)
NFS（网络文件系统 Network File System）允许将一台机器的目录被另一台机器上的
用户 安装（Mount）到自己的机器上，就像是对本地文件系统进行操作一样进行各式各样
的操作。
NIS（网络信息服务 Network Information Service）对整个网络用户的用户名、密码进
行统一管理，简化在 NIS 服务下整个网络登陆的用户名／密码检查。
RPC（远程过程调用 Remote Procedure Call）通过它可以允许远程的应用程序通过简
单的、有效的手段联系本地的应用程序，反之也是。
SMTP（简单邮件传输协议 Simple Mail Transfer Protocol）一个专门为电子邮件在多台
机器中传输的协议，平时发邮件的 SMTP 服务器提供的必然服务。
SNMP（简单网络管理协议 Simple Network Management Protocol）这是一项为超级用
户准备的服务，超级用户可以通过它来进行简单的网络管理。

## 套接字地址
socket 文件描述符：一个文件描述符只是一个简单的整形数值，代表一个被打开的文件（这里的文件是广
义的文件，并不只代表不同的磁盘文件，它可以代表一个网络上的连接，一个先进先出队
列，一个终端显示屏幕，以及其他的一切）。在 UNIX 系统中任何东西都是一个文件
## 基本结构

struct sockaddr{
    unsigned short sa_famaliy;//地址族 AF
    char sa_datas[14];//14bytes的协议地址->远程电脑的地址，端口和套接字数目
};

相似的结构 
struct sockaddr_in{
    short int sin_family;//internet地址族
    unsigned short int sin_port;//端口号 网络字节序
    struct in_addr sin_addr//internet地址 网络字节序
    unsigned char sin_zero[8];//添0
}

struct in_addr{
    unsigned long s_addr;
}


## 基本转化函数

### 网络字节序

1. 将低序字节存储在起始地址，这称为小端字节序。
2. 将高序字节存储在起始地址，这称为大端字节序

每一个机器内部对变量的字节存储顺序不同(大小端)，而网络传输是要统一的顺序的，多余对于内部字节表示顺序和网络字节顺序就要对数据进行转化(例如ip地址，端口号)

在网络传输中，TCP/IP协议在保存IP地址这个32位二进制数时，协议规定采用在低位存储地址中包含数据的高位字节的存储顺序，这种顺序格式就被称为网络字节顺序格式。在实际网络传输时，数据按照每32位二进制数为一组进行传输，由于存储顺序的影响，实际的字节传输顺序是由高位字节到低位字节的传输顺序。其实网络字节序也就是大端字节序。

### 在 struct sockaddr_in 中的 sin_addr 和 sin_port 他们的字节顺序都是网络字节顺序，而sin_family 却不是网络字节顺序的。为什么呢？

这个是因为 sin_addr 和 sin_port 是从 IP 和 UDP 协议层取出来的数据，而在 IP 和 UDP
协议层，是直接和网络相关的，所以，它们必须使用网络字节顺序。然而， sin_family 域
只是内核用来判断 struct sockaddr_in 是存储的什么类型的数据，并且， sin_family 永远也
不会被发送到网络上，所以可以使用主机字节顺序来存储。
### 有关的转化函数

针对两种数据类型 短型(2bytes) 和长型(4bytes)
h:host 表示主机
to:
n:网络
s:短型||l:长型
->htons/htonl  主机字节顺序转换为网络字节顺序

ntohs/ntohl    网络字节序转化位主机字节序

## 基本套接字调用

1. int socket(int domain ,int type,int protocol)
   取得套接字描述符
   domain:AF_INET or AF_INET6 or AF_UNIX  or AF_APPLETAKE 
   type:“SOCK_STREAM”或是“SOCK_DGRAM” or SOCK_RAW

2. int bind(int sockfd,struct sockaddr *my_addr,int addrlen)
   指定一个套接字使用的端口
   sockfd:socket()函数返回的套接字描述符
   my_addr 是一个指向struct sockaddr的指针，包含了地址信息(名称，端口，ip地址)；
   addrlen:sizeof(sockaddr)

   其中 
   my_addr.sin_port =0
   my_addr.sin_addr.s_addr=INADDR_ANY
   bind()会帮你选择合适的端口

   bind中最好不要将端口号设置小于1024->保留下来作为系统使用端口的，没有root权力无法使用 1024~65535

3. int connect(int sockfd,struct sockaddr *serv_addr,int addrlen)
   建立一个套接字描述符
   serv_addr:一个存储远程计算机的IP地址和端口信息的结构

4. int listen(int sockfd,int backlog)
   侦听请求函数，当有人连接时，需要使用Listen函数等待连接请求，然后使用accept()函数处理

   backlog:未经处理的连接请求队列可以容纳最大数目

5. int accept(int sockfd,void*addr,int *addrlen)
   将listen里面等待连接的队列进行调用，告诉他准备连接
   返回一个新的套接字描述符代表连接
   
   sockfd :listen下的一个套接字描述符
   addr:指向struct sockaddr_in结构的指针，里面存储远程链接过来的计算机信息(ip地址和端口)

   addrlen(size of sockaddr_in)

6. int send(int sockfd,const void*msg,int len,int flags)
   最基本，通过连接的套接字流进行通讯的函数
   sockfd:和远程程序连接的套接字描述符
   msg:一个指针，指向你想发送的信息的地址
   len:发送信息的长度
   flags:发送标记。一般设置为0

   调用后会返回真正发送数据的长度

7. int recv(int sockfd,void*buf,int len,unsigned int flags)
   sockfd:和远程程序连接的套接字描述符
   buf:一个指针，指向能存储数据的内存缓存区域
   len:发送信息的长度
   flags:接收标记。一般设置为0

8. int sendto(int sockfd,const void*msg,int len,unsigned int flags,const struct sockaddr *to,in tolen)
   无连接UDP通信时使用的，会在没有建立任何连接的网络上传输
   sockfd:与远程程序连接的套接字描述符
   msg:指向想发送的信息的地址
   len：发送信息的长度
   flags:发送标记。一般设置为0
   to :指向struct sockaddr结构的指针，里面包含了远程主机的IP地址和端口数据
   tolen：sizeof(struct sockaddr)
9. int recvform(int sockfd, void *buf, int len, unsigned int flags
struct sockaddr *from, int *fromlen)
   sockfd:和远程程序连接的套接字描述符
   buf:一个指针，指向能存储数据的内存缓存区域
   len:发送信息的长度
   flags:接收标记。一般设置为0
   form:本地指针，指向一个struct sockaddr的结构
   formlen:实际大小
10. close(int sockfd) ,shutdown(int sockfd)
   前者是全关的，后者进行单向的关闭操作或者全部禁止掉（0->接收，1->发送，2全部）


11. setsockopt() 和 getsockopt() 
你不能为一个套接字重
新启用同一个端口号，即使在你正常关闭该套接字以后。例如，比方说，你编写一个服务
器在一个套接字上等待的程序．服务器打开套接字并在其上侦听是没有问题的。无论如何，
总有一些原因（不管是正常还是非正常的结束程序）使你的程序需要重新启动。然而重启
动后你就不能把它绑定在原来那个端口上了。从 bind()系统调用返回的错误代码总是报告
说你试图连接的端口已经被别的进程所绑定

12. int getpeername(int sockfd, struct sockaddr *addr, int *addrlen)
    获取远程信息的主机名字
      sockfd 是你想取得远程信息的那个套接字描述符。
      addr 是一个指向 struct sockaddr （或是 struct sockaddr_in）的指针。
      addrlen 是一个指向 int 的指针，应该赋于 sizeof(struct sockaddr)的大小
13. int gethostname(char *hostname, size_t size);
    获取本地主机的信息