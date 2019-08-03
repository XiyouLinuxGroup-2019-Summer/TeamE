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
#define SERV_ADDRESS  "127.0.0.1"
#define EPOLL_SIZE    5000
#define SERV_PORT    4507
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

//创建套接字并进行绑定,返回新创建的套接字文件描述符
int socket_bind(char *ip,int port)
{
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET,SOCK_STREAM,0);//获取新创建的套接字的文件描述符
    if(listenfd == -1)
        my_err("套接字创建失败",__LINE__);
    bzero(&servaddr,sizeof(servaddr)); //初始化套接字地址结构体
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
        my_err("套接字绑定端口失败",__LINE__);
    return listenfd;
}

//添加事件,将监听套接字加入epoll事件
void add_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;//事件类型设置为可读事件
    ev.data.fd = fd;//一定要有

    /* 如果是ET模式，设置EPOLLET */
    // if (epoll_type == EPOLL_ET)
    //  ev.events |= EPOLLET;默认是LT模式?

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
    if(clifd == -1){
        printf("连接失败line:%d\n",__LINE__);
    }
    else  {
        printf("连接到新的客户端IP:%s  端口:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
        
        //添加一个客户端描述符事件,添加到内核监听事件中
        add_event(epollfd,clifd,EPOLLIN);//后面这个客户端套接字有事件发生时会在handle_events根据类型处理这个事件

        //唤醒线程池中的线程去处理连接请求
        int pid; 
        if((pid = fork()) == 0){
            char *buf2 = "Welcome";
            if(send(clifd, buf2, MAXSIZE, 0) < 0)//clientfd表示新连接客户端
                my_err("发送消息失败",__LINE__);
            else printf("发送消息成功");
        } 
    }
    
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
    
    int listenfd = socket_bind(SERV_ADDRESS,SERV_PORT);//listenfd表示创建的套接字文件描述符
    if(listen(listenfd,LISTENQ) < 0)//将套接字转化为监听套接字
        my_err("监听失败\n",__LINE__);
    else printf("开始监听:%s\n",SERV_ADDRESS);
	
     int epfd;
    struct epoll_event events[EPOLLEVENTS];//注册所感兴趣的事件和回传发生的待处理的事件
    int ret;//return 
    char buf[MAXSIZE];//缓冲区
    memset(buf,0,sizeof(buf));

    //创建一个描述符
    epfd = epoll_create(FDSIZE);//创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大,后面需要close关闭
    if(epfd < 0) my_err("epoll创建失败",__LINE__);
    else printf("epoll[%d]创建成功\n",epfd);

    //向内核添加监听描述符事件,并设置非阻塞监听
    add_event(epfd,listenfd,EPOLLIN);

    //获取已经准备好的描述符事件,主循环
    while(1) {
        int epoll_event_count = epoll_wait(epfd,events,EPOLLEVENTS,-1);//等待事件发生,ret表示需要处理的事件数目
        if(epoll_event_count < 0) my_err("需要处理事件异常",__LINE__);//<0的时候出错
            for(int i = 0;i < epoll_event_count;i++ ){

                int fd = events[i].data.fd;//根据事件类型做相应的处理

                //根据文件描述符类型和事件类型进行处理
                if((fd == listenfd) && (events[i].events & EPOLLIN))//事件为服务端监听套接字说明是连接请求
                    handle_accept(epfd,listenfd);
                //处理读写事件
                else if(events[i].events & EPOLLIN) 
                    do_read(epfd,fd,listenfd,buf);
                else if(events[i].events & EPOLLOUT) 
                    do_write(epfd,fd,listenfd,buf);
                    }
        }

    close(epfd);//!!!
    close(listenfd);
    return 0;
 }

