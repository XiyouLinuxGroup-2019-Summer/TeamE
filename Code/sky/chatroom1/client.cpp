#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LISTENQ 12                    //连接请求队列的最大长度
#define CLI_ADDRESS  "127.0.0.1"
#define EPOLL_SIZE    5000
#define CLI_PORT    4507
#define EPOLLEVENTS 100
#define MAXSIZE     1024
#define FDSIZE      1000

//自定义错误处理函数
void my_err(const char *s,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(s);
    exit(1);
}

//创建套接字并进行连接,返回新创建的套接字文件描述符
int socket_connect(char *ip,int port)
{
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET,SOCK_STREAM,0);//获取新创建的套接字的文件描述符
    if(listenfd == -1) {
        my_err("套接字创建失败",__LINE__);
    }
    bzero(&servaddr,sizeof(servaddr)); //初始化套接字地址结构体
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    
    if(connect(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
        my_err("连接失败",__LINE__);
    }
    else printf("成功连接至服务器。。。\n");
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

//处理读请求的事件
void do_read(int epollfd,int fd,int sockfd,char *buf)//fd表示待处理事件的描述符
{
    printf("处理读事件\n");
    int nread;
    nread = recv(fd,buf,MAXSIZE,0);
    if(nread == -1){
        my_err("读事件处理错误",__LINE__);
        close(fd);
    }
    else if(nread == 0){
        fprintf(stderr,"服务器关闭\n");
        close(fd);
    }
    else{
        printf("接收到的消息是:%s\n",buf);
    }

    return ;
}

void do_write(int epollfd,int fd,int sockfd,char *buf)
{
    printf("处理写事件\n");
    /* write(fd,"hello",5); */
    int nwrite;
    nwrite = send(fd,buf,strlen(buf),0);
    if(nwrite == -1){
        my_err("写事件处理错误",__LINE__);
        close(fd);
    }
    else{
        printf("发送消息成功\n");
    }
    memset(buf,0,MAXSIZE);
}

int main()
{
    int listenfd = socket_connect(CLI_ADDRESS,CLI_PORT);
    int epfd;
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    int ret;
    epfd = epoll_create(FDSIZE);
    add_event(epfd,listenfd,EPOLLIN);
    //获取已经准备好的描述符事件,主循环
    while(1) {
        int epoll_event_count = epoll_wait(epfd,events,EPOLLEVENTS,-1);//等待事件发生,ret表示需要处理的事件数目
        if(epoll_event_count < 0) my_err("需要处理事件异常",__LINE__);//<0的时候出错
            for(int i = 0;i < epoll_event_count;i++ ){

                int fd = events[i].data.fd;//根据事件类型做相应的处理

                //处理读写事件
                if(events[i].events & EPOLLIN)
                    do_read(epfd,fd,listenfd,buf);
                else if(events[i].events & EPOLLOUT)
                    do_write(epfd,fd,listenfd,buf);
             }
    }
    close(epfd);

}
