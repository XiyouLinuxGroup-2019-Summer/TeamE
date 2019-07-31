#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<perron.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<sys/types.h>

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define MAXSIZE 1024
#define LISTENQ 5
#define FPSIZE 1000
#define EPOLLEVEBTS 100

//创建套接字并进行绑定
static int socket_bind(const char * ip,int port);
//IO多路复用epoll
static void do_epoll(int listenfd);
//事件处理函数
static void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf);
//处理接收到的连接
static void handle_accept(int epollfd,int listenfd);
//读处理
static void do_read(int epollfd,int fd,char *buf);
//写处理
static void do_write(int epollfd,int fd,char *buf);
//添加事件
static void add_event(int epollfd,int fd,int state);
//修改事件
static void modify_event(int epollfd,int fd,int state);
//删除事件
static void delete_event(int epollfd,int fd,int state);

int main(int argc,char ** argv)
{
	int listenfd;
	//创建套接字并进行绑定
	listenfd = socket_bind(IPADDRESS,PORT);//
	listen(listenfd,LISTENQ); //把套接字化为 被动监听
			//LISTENQ   请求队列的长度
	do_epoll(listenfd);


	return 0;
}

static int socket_bind(const char *ip,int port)
{
	int listenfd;
	struct sockaddr_in servaddr;
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd == -1)
	{
		perror( "socket error:");
		exit(1);
	}

	//初始化 服务器段地址结构
	bzero(&servaddr,sizeof(servaddr)); //置字节字符串前n个字节为零且包括‘\0’。
	//等价于    memset(&servaddr,0,sizeof(struct sockaddr_in ));
	
	
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&servaddr.sin_addr);//inet_pton是一个IP地址转换函数
	//将 ip 转化为网络地址族中的地址结构,然后复制到   servaddr.sin_addr  上

	
	//如果不设置  ,服务器 退出重启是,很可能出现 此地址已经被使用
	//设置了之后  使该套接字可以重新绑定端口
	int on=1;
	if((setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)
	{
		perror("setsockopt failed");
		exit(EXIT_FAILURE);
	}

	servaddr.sin_port = htons(port);  //设置服务器段的 端口
	
	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)   //将套接字绑定到本地端口
	{
		perror("bind error");
		exit(1);
	}
	return listenfd;
}

static void do_epoll(int listenfd)
{
	int epollfd;
	struct epoll_event events[EPOLLEVEBTS];     
	/*
	 * struct epoll_event 
	 * {
		  __uint32_t events;  //  感兴趣 的时间和被触发的事件    例 : EPOLLIN (对应的文件描述符可读)
		  epoll_data_t data;   // //保存触发事件的某个文件描述符相关的数据
	    };
	    */

	int ret;
	char buf[MAXSIZE];
	memset(buf,0,MAXSIZE);
	//创建一个描述符
	epollfd = epoll_create(FPSIZE);   //size 监听的数目 一共有多大 占用 一个fd值,使用完后 一定要关闭 close(),否则会导致fd 被耗尽
	//添加监听描述符事件
	add_event(epollfd,listenfd,EPOLLIN);  //注册新的 fd 到epollfd 中

	while(1)
	{
		//获取已经准备好的描述符事件
		//参数events用来从内核得到事件的集合，
		ret = epoll_wait(epollfd,events,EPOLLEVEBTS,-1);  //-1 表示时间  可能是永久阻塞
		//返回值  : 返回需要处理的事件 数目,0 表示超时
		handle_events(epollfd,events,ret,listenfd,buf);  ////////////////////////////
	}

	close(epollfd);    //一定要记着关闭
}

static void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf)
{
	int i,fd;

	//进行选好遍历
	for(i  = 0;i < num;i++)
	{
		fd = events[i].data.fd;

		//根据描述符的类型和事件类型进行处理   
		if((fd == listenfd) && (events[i].events & EPOLLIN))	handle_accept(epollfd,listenfd);  // epoll 监视自己
		else if(events[i].events & EPOLLIN)	do_read(epollfd,fd,buf);
		else if(events[i].events & EPOLLOUT)	do_write(epollfd,fd,buf);
	}
}

static void handle_accept(int epollfd,int listenfd)
{
	int clifd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen;
	cliaddrlen = sizeof(struct sockaddr);   //切记 要初始化,不然第二次连接 会报参数错误 
	clifd = accept(listenfd,(struct sockaddr *)&cliaddr,&cliaddrlen); //返回一个代表客户端的套接字
	if(clifd == -1)  perror("accept error :");
	else 
	{
		printf( "accept a new client:%s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);

		//添加一个客户端描述符和事件
		add_event(epollfd,clifd,EPOLLIN);
	}
}

static void add_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}

static void do_read(int epollfd,int fd,char *buf)
{
	int nread;
	nread = read(fd,buf,MAXSIZE);
	if(nread == -1)
	{
		perror("read error: ");
		close(fd);
		delete_event(epollfd,fd,EPOLLIN);
	}
	else if(nread == 0)
	{
		fprintf(stderr,"client close.\n");
		close(fd);
		delete_event(epollfd,fd,EPOLLIN);
	}
	else
	{
		printf( "read message is : %s",buf);
		//修改描述符对应的事件
		modify_event(epollfd,fd,EPOLLOUT);
	}
}

static void delete_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}

static void modify_event(int epollfd ,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}

static void do_write(int epollfd,int fd,char *buf)
{
	int nwrite;
	nwrite = write(fd,buf,strlen(buf));
	if(nwrite == -1)
	{
		perror("write error: ");
		close(fd);
		delete_event(epollfd,fd,EPOLLOUT);
	}
	else
		modify_event(epollfd,fd,EPOLLIN);
	memset(buf,0,MAXSIZE);

}

