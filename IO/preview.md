# 服务器程序框架

1. I/O处理单元
2. 逻辑单元
3. 存储单元
   

## C/S模型

## P2P模型

每台主机即是客户端又是服务器

## 框架

1. I/O处理单元：服务器管理客户链连接的模块，等待并接收新的客户连接，接收客户数据，将服务器响应数据返回给客户端，数据的收发不一定在这里执行，对于一个服务器机群来说，是一个专门的接入服务器，实现负载均衡，从所有逻辑服务器中选取负荷最小的一台来为新客户服务

2. 逻辑单元：通常是一个进程或者线程，分析并处理客户数据，然后将结果传给I/O或者直接发送给客户端

3. 网络存储单元可以是数据库，缓存和文件，甚至是一台独立的服务器
4. 请求队列是各个单元之间的通信方式的抽象

## I/O模型

### 阻塞I/O
程序阻塞于读写函数
### I/O复用
程序阻塞于I/O复用系统调用，但可以同时监听多个I/O事件，对于I/O本身的读写操作是非阻塞的

### SIGIO信号
信号触发读写就绪事件，用户程序执行读写操作，程序没有阻塞阶段
### 异步I/O
内核执行读写操作并触发读写完成事件，程序没有阻塞阶段


## 两种高效的事件处理模式

服务器程序通常需要处理三类事件，I/O事件，信号及定时事件

## 同步I/O的 Reactor
要求主线程(I/O处理单元)只负责监听文件描述上是否有事件发生，有的话就立即将该事件通知工作线程(逻辑单元)，除此之外，主线程不做任何其他实质性的工作，读写数据，接收新的连接，以及处理客户请求均在工作线程中完成

### 流程
1. 主线程往epoll内核事件表注册socket上的读就绪事件
2. 主线程调用epoll_wait等待socket上有数据可读
3. 当socket上有数据可读时，epoll_wait通知主线程，主线程则将socket可读事件放入请求队列
4. 睡眠在请求队列上的某个工作线程被唤醒，它从socket读取数据，并处理客户请求，然后往epoll内核事件表注册该socket上的写就绪事件
5. 主线程调用epoll_wait等待socket可写
6. 当socket可写时,epoll_wait通知主线程，将socket可写事件放入请求队列
7. 睡眠在请求队列上的某个工作线程被唤醒，往socket写入服务器处理客户请求的结果


## 异步I/O的 Proactor

将所有的I/O操作都交给主线程和内核来处理，工作线程只负责业务逻辑

### 流程
1. 主线程调用aio_read函数向内核注册socket上的读完成事件，并告诉内核用户读缓冲区的位置，以及读操作完成时如何通知应用程序
2. 主线程继续处理其他逻辑
3. 当socket上的数据被读入用户缓存区后，内核向应用程序发送一个信号，以通知应用程序数据可用
4. 英寸程序预先定义好的信号处理函数选择一个工作线程来向程序发送一个请求，处理玩请求后，调用aio_write函数注册写完成事件，并且告诉内核用户写缓冲区的位置，以及写操作完成时如何通知应用程序
5. 主线程继续处理其他逻辑
6. 当用户缓冲区的数据被写入socket后，内核将向应用程序发送一个信号，以通知应用程序是否完成