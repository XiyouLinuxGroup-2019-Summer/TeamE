//客户端主要用epoll控制SSTDIN_FILENO、STDOUT_FILENO、和sockfd三个描述符
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#define IPADDRESS "127.0.0.1"
#define PORT      4507
#define LISTENQ   5
#define EPOLLEVENTS 100
#define MAXSIZE     1024
#define FDSIZE      1000

//创建套接字并进行连接,返回新创建的套接字文件描述符
int socket_connect(char *ip,int port)
{
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET,SOCK_STREAM,0);//获取新创建的套接字的文件描述符
    if(listenfd == -1)
    {
        printf("套接字创建失败line:%d\n",__LINE__);
        exit(1);
    }
    bzero(&servaddr,sizeof(servaddr)); //初始化套接字地址结构体
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    
    int ret = connect(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(ret < 0)
    {
        printf("连接失败line:%d\n",__LINE__);
    }
    return listenfd;
}
//添加事件
void add_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);//事件注册函数
    return ;
}

//修改事件
void modify_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
    return ;
}

//删除事件
void delete_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
    return ;
}

//处理读请求的事件
void do_read(int epollfd,int fd,int sockfd,char *buf)//fd表示待处理事件的描述符
{
    int nread;
    nread = read(fd,buf,MAXSIZE);
    if(nread == -1)
    {
        printf("读出现错误line:%d\n",__LINE__);
        close(fd);
    }
    else if(nread == 0)
    {
        fprintf(stderr,"服务器关闭\n");
        close(fd);
    }
    else
    {
        printf("接收到的消息是:%s",buf);
        /* write(fd,"Hello",5); */
        //修改描述符对应事件由读改为写
        modify_event(epollfd,fd,EPOLLOUT);//修改标识符，等待下一个循环时发送数据，异步处理的精髓

    }
    return ;
}
void do_write(int epollfd,int fd,int sockfd,char *buf)
{
    /* write(fd,"hello",5); */
    int nwrite;
    nwrite = write(fd,buf,strlen(buf));
    if(nwrite == -1)
    {
        printf("写出现错误line:%d\n",__LINE__);
        close(fd);
    }
    else
    {
        if(fd == STDOUT_FILENO)
        {
            delete_event(epollfd,fd,EPOLLOUT);
        }
        else
        {
            modify_event(epollfd,fd,EPOLLOUT);
        }
    }
    memset(buf,0,MAXSIZE);
}

//事件处理函数
void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf)
{
    int fd;
    //遍历需要处理的事件
    for(int i = 0;i<num;i++)
    {
        /* printf("fd = %d\n",fd); */
        fd = events[i].data.fd;//根据事件的属性处理事件

        //根据文件描述符类型和事件类型进行处理
        if(events[i].events & EPOLLIN) 
            do_read(epollfd,fd,listenfd,buf);
        else if(events[i].events & EPOLLOUT)
            do_write(epollfd,fd,listenfd,buf);
    }
}

//处理连接
void handle_connection(int sockfd)
{
    
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    int ret;
    epollfd = epoll_create(FDSIZE);
    add_event(epollfd,sockfd,EPOLLIN);
    while(1)
    {
        ret = epoll_wait(epollfd,events,EPOLLEVENTS,-1);
        handle_events(epollfd,events,ret,sockfd,buf);
    }
    close(epollfd);
}

int main(int argc,char **argv)
{
    int sockfd = socket_connect(IPADDRESS,PORT);
    handle_connection(sockfd);//处理连接
    return 0;
}

