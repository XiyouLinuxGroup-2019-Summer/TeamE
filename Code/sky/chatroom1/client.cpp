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
#include <pthread.h>

#define LISTENQ 12                    //连接请求队列的最大长度
#define SERV_ADDRESS  "127.0.0.1"
#define EPOLL_SIZE    5000
#define SERV_PORT    4507    
#define EPOLLEVENTS 100
#define MAXSIZE     1024
#define FDSIZE      1000
#define REGISTER 1
#define LOGIN        2

int listenfd;
//消息结构体
typedef struct message
{
    int flag;
    char mg[256];
}message;

//账户信息结构体
typedef struct  account
{
    int flag;
    int  username;
    char passwd[30];
    char nickname[30];
}account;



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
void Print_welcome(char *buf)
{
    message msg;
    memcpy(&msg,buf,sizeof(msg));
    printf("******%s******\n",msg.mg);
}

//处理读请求的事件
void do_read(int epollfd,int fd,int sockfd,char *buf)//fd表示待处理事件的描述符
{
    printf("处理读事件\n");
    int ret;
    ret = recv(fd,buf,MAXSIZE,0);
    if(ret == -1){
        my_err("读事件处理错误",__LINE__);
        close(fd);
    }
    else if(ret == 0){
        fprintf(stderr,"服务器关闭\n");
        close(fd);
        exit(1);
    }

    int choice;
    memcpy(&choice,buf,4);
    printf("choice = %d\n",choice);
    switch(choice)
    {
        case 0:
            Print_welcome(buf);
    }
    
    

    memset(buf,0,MAXSIZE);
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
void  Account_register()
{
    char second[30];
    char str[MAXSIZE];
    account reg;
    memset(str,0,sizeof(str));
    printf("昵称:");
    scanf("%s",reg.nickname);
    int tag = 0;
    do{
            if(tag) puts("两次输入密码不一致!请重新输入");
            printf("密码:");
            scanf("%s",reg.passwd);
            printf("再次输入密码:");
            scanf("%s",second);
    }while( strcmp(second,reg.passwd));
    reg.flag = REGISTER;
    memcpy(str,&reg,sizeof(account));
    if(send(listenfd,str,MAXSIZE,0) == -1){
        my_err("注册账户时发送出错",__LINE__);
    }
    else{
        printf("按[ENTER]返回上层");
        getchar();
    }


    // account tmp;
    // memcpy(&tmp,str,MAXSIZE);
    // printf("标志是%d\n",tmp.flag);
    // printf("昵称是%s\n",tmp.nickname);
    // printf("密码是%s\n",tmp.passwd);
    return ;
    
}
void Main_menu()
{
    int choice = -1;
    while(choice){
        usleep(100);
        puts("[1]注册     [2]登录         [0]退出");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                puts("注册");
                Account_register();
                break;
            case 2:
                puts("登录");
                break;
            case 3:
                break;
        }
    }
    
    return ;
}

void *do_epoll(void *arg)
{
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

                //只处理读写事件
                if(events[i].events & EPOLLIN)
                    do_read(epfd,fd,listenfd,buf);
             }
    }
    close(epfd);
    return NULL;
}
int main()
{
    setbuf(stdin,NULL);
    pthread_t thid;
    char buf[MAXSIZE];
     listenfd = socket_connect(SERV_ADDRESS,SERV_PORT);


    //创建子线程专门接受消息
    if(pthread_create(&thid,NULL,do_epoll,NULL) != 0){
        my_err("创建线程失败",__LINE__);
    }

    //主线程进入菜单
    Main_menu();

    
    

}
