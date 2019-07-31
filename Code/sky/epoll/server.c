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
//创建套接字并进行绑定,返回新创建的套接字文件描述符
int socket_bind(char *ip,int port)
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
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
    {
        printf("套接字绑定端口失败line:%d\n",__LINE__);
        exit(1);
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

//处理接收到的连接
void handle_accept(int epollfd,int listenfd)
{
    int clifd;//客户端套接字描述符
    struct sockaddr_in cliaddr; //客户端地址
    socklen_t cliaddrlen;

    clifd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen); //接受连接请求
    if(clifd == -1)
    {
        printf("连接失败line:%d\n",__LINE__);
    }
    else 
    {
        printf("连接到新的客户端IP:%s  端口:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
        
        //添加一个客户端描述符事件
        add_event(epollfd,clifd,EPOLLIN);//后面这个客户端套接字有事件发生时会在handle_events根据类型处理这个事件
        int pid; 
        if((pid = fork()) == 0)
        {
            while(1)
            {
            char buf2[256];
            scanf("%s",buf2);
            printf("%s\n",buf2);
            write(clifd,buf2,strlen(buf2));
            
        }
    }
}
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
void do_read(int epollfd,int fd,char *buf)//fd表示待处理事件的描述符
{
    int nread;
    nread = read(fd,buf,MAXSIZE);
    if(nread == -1)
    {
        printf("读出现错误line:%d\n",__LINE__);
        close(fd);
        delete_event(epollfd,fd,EPOLLIN);
    }
    else if(nread == 0)
    {
        fprintf(stderr,"客户端关闭\n");
        close(fd);
        delete_event(epollfd,fd,EPOLLIN);
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


void do_write(int epollfd,int fd,char *buf)//写?
{
    int nwrite;
    nwrite = write(fd,buf,strlen(buf));
    if(nwrite == -1)
    {
        printf("写出现错误line:%d\n",__LINE__);
        close(fd);
        delete_event(epollfd,fd,EPOLLOUT);
    }
    else
        modify_event(epollfd,fd,EPOLLIN);
    memset(buf,0,MAXSIZE);
}
//事件处理函数
void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf)
{
    int fd;
    //遍历需要处理的事件
    for(int i = 0;i<num;i++)
    {
        fd = events[i].data.fd;//根据事件的属性处理事件

        //根据文件描述符类型和事件类型进行处理
        if((fd == listenfd) && (events[i].events & EPOLLIN))
            handle_accept(epollfd,listenfd);
        else if(events[i].events & EPOLLIN) 
            do_read(epollfd,fd,buf);
        else if(events[i].events & EPOLLOUT)
            do_write(epollfd,fd,buf);
    }
}
//IO多路服用epoll
void do_epoll(int listenfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];//注册所感兴趣的事件和回传发生的待处理的事件
    int ret;//return 

    char buf[MAXSIZE];
    memset(buf,0,sizeof(buf));

    //创建一个描述符
    epollfd = epoll_create(FDSIZE);//创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大,后面需要close关闭

    //添加监听描述符事件
    add_event(epollfd,listenfd,EPOLLIN);

    //获取已经准备好的描述符事件
    while(1)
    {

        /* if(GetAsyncKeyState('q') && 0x8000) break; */

        ret = epoll_wait(epollfd,events,EPOLLEVENTS,-1);//等待事件发生,ret表示需要处理的事件数目
        handle_events(epollfd,events,ret,listenfd,buf);
    }
    close(epollfd);//!!!
    return ;
}

int main()
{
    int listenfd = socket_bind(IPADDRESS,PORT);//listenfd表示创建的套接字文件描述符
    listen(listenfd,LISTENQ);//将套接字转化为监听套接字
    do_epoll(listenfd);
    return 0;
}

