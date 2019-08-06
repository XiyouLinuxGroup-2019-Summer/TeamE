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
#include <my_global.h>
#include <mysql.h>

#define LISTENQ 12                    //连接请求队列的最大长度
#define SERV_ADDRESS  "127.0.0.1"
#define EPOLL_SIZE    5000
#define SERV_PORT    4507
#define EPOLLEVENTS 100
#define MAXSIZE     1024
#define FDSIZE      1000
#define REGISTER 1
#define LOGIN        2

MYSQL *con = mysql_init(NULL);
//消息结构体
typedef struct message
{
    int flag;
    char mg[256];
}message;


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

//创建套接字并进行绑定,返回新创建的套接字文件描述符
int socket_bind(char *ip,int port)
{
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET,SOCK_STREAM,0);//获取新创建的套接字的文件描述符
    if(listenfd == -1)
        my_err("套接字创建失败",__LINE__);

    //设置套接字使其可以重新绑定端口
    int optval = 1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0){
        my_err("设置套接字失败",__LINE__);
    }

    bzero(&servaddr,sizeof(servaddr)); //初始化套接字地址结构体
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
        my_err("套接字绑定端口失败",__LINE__);
    return listenfd;
}
void finish_with_error(MYSQL *con)
{
    fprintf(stderr,"%s\n",mysql_error(con));
    mysql_close(con);
    return ;
}

void Connect_Database(MYSQL *con)
{
    if(con == NULL) 
        finish_with_error(con);   
    if(mysql_real_connect(con,"localhost","root","2422503084.","chatroom",0,NULL,0) == NULL) 
        finish_with_error(con);
    else printf("成功连接到数据库\n");
    return ;
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
    socklen_t cliaddrlen = sizeof(struct sockaddr_in);

    clifd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen); //接受连接请求
    if(clifd == -1){
        printf("连接失败line:%d\n",__LINE__);
    }
    else  {
        printf("连接到新的客户端IP:%s  端口:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
        
        //添加一个客户端描述符事件,添加到内核监听事件中
        add_event(epollfd,clifd,EPOLLIN);//后面这个客户端套接字有事件发生时会在handle_events根据类型处理这个事件

        message msg;
        msg.flag = 0;//0表示立刻发送
        strcpy(msg.mg,"Welcome");
        char buf[MAXSIZE];
        memcpy(buf,&msg,sizeof(msg));
        if(send(clifd, buf, MAXSIZE, 0) < 0)//clientfd表示新连接客户端
             my_err("发送消息失败",__LINE__);
        else printf("发送消息成功\n");

         if(send(clifd, buf, MAXSIZE, 0) < 0)//clientfd表示新连接客户端
             my_err("发送消息失败",__LINE__);
        else printf("发送消息成功\n");

         if(send(clifd, buf, MAXSIZE, 0) < 0)//clientfd表示新连接客户端
             my_err("发送消息失败",__LINE__);
        else printf("发送消息成功\n");

         if(send(clifd, buf, MAXSIZE, 0) < 0)//clientfd表示新连接客户端
             my_err("发送消息失败",__LINE__);
        else printf("发送消息成功\n");

         if(send(clifd, buf, MAXSIZE, 0) < 0)//clientfd表示新连接客户端
             my_err("发送消息失败",__LINE__);
        else printf("发送消息成功\n");
        
    }
    
    return ;
}

//返回注册的账号失败返回-1
int Account_register_persist(char *buf)
{
    account reg;
    memcpy(&reg,buf,sizeof(reg));
    char insert[MAXSIZE];
    sprintf(insert,"insert into Account (passwd,nickname) values('%s','%s')",reg.passwd,reg.nickname);
    if(mysql_real_query(con,insert,strlen(insert))){
        finish_with_error(con);
    }else printf("新账号成功写入数据库\n");

    //再从数据库中获取插入的主键值
    if(mysql_query(con,"select LAST_INSERT_ID()")){
        finish_with_error(con);
    }
    MYSQL_RES *res  = mysql_store_result(con);
    MYSQL_ROW  row = mysql_fetch_row(res);
    // printf("res = %d\n",atoi(row[0]));
    // printf("标志是%d\n",reg.flag);
    // printf("昵称是%s\n",reg.nickname);
    // printf("密码是%s\n",reg.passwd);
    return atoi(row[0]);
}

void Acount_register(int fd,char *buf)
{
    char s[MAXSIZE];
    int ret = Account_register_persist(buf);
    if(ret < 0){
        my_err("注册账号失败",__LINE__);
    }
    else{
        printf("新账号[%d]注册成功\n",ret);
    }
    
    message msg;
    msg.flag = 0;
    sprintf(msg.mg,"新账号[%d]注册成功",ret);
    memcpy(s,&msg,sizeof(msg));
    int nwrite = send(fd,s,MAXSIZE,0);
    if(nwrite == -1){
        my_err("发送失败",__LINE__);
        close(fd);
    }
    
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
        fprintf(stderr,"客户端[%d]关闭\n",fd);
        close(fd);
        return ;
    }

     int choice = 0;
    memcpy(&choice,buf,4);
    printf("choice = %d\n",choice);
    switch(choice)
    {
        case 1:
            Acount_register(fd,buf);
            break;
    }
    
    // if(Account_exist())
    //     if(send(fd,"N",MAXSIZE,0)< 0) my_err("send err",__LINE__);
    

    

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
    Connect_Database(con);
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

