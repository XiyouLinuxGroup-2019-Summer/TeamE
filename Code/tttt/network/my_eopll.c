#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<sys/types.h>

#define PORT 4507
#define LISTENQ 10
#define EPOLLLEN 2000

int listenfd_accept(int epfd,int fd);
int do_read();
int do_write();

int main(int argc ,char ** argv)
{
	int listenfd;
	struct sockaddr_in servaddr;
	int optval;
	//创建一个套接字
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	//设置该套接字使之可以重新绑定端口
	optval = 1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)    printf( "setsockopt error\n");

	//初始化服务器地址
	memset(&servaddr,0,sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//将套接字绑定到本地端口
	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr_in)) < 0)   printf( "bind error\n");

	//化被动为主动  转为 监听套接字
	if(listen(listenfd,LISTENQ) < 0)  printf( "listen error\n");

	int epfd;
	//创建一个epoll
	//EPOLLLEN  为监视的个数
	epfd = epoll_create(EPOLLLEN);
	//创建一个 事件数组
	struct epoll_event events[EPOLLLEN];
	struct epoll_event ev;
	ev.events = EPOLLIN;   //监听事件
	ev.data.fd = listenfd;  //监听套接字
	//将listenfd 加入epoll 
	epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
	int ret = 0;
	while(1)
	{
		//委托内核监测事件
		ret = epoll_wait(epfd,events,EPOLLLEN,-1);
		
		if(ret > 0)  //若有事件发生
		{
			for(int i = 0;i < ret;i++)
			{
				int fd = events[i].data.fd;
				if(fd == listenfd) //请求是来自 客户端发起连接
				{
					listenfd_accept(epfd,fd);    //连接
				}
				else //是客户端发 收 数据
				{
					//判断该事件是读
					if(events[i].events & EPOLLIN)
					{
						do_read();
					}
					else if(events[i].events & EPOLLOUT)    //判断改事件是 写 
					{
						do_write();
					}
				}
			}
		}

	}

}

int listenfd_accept(int epfd,int fd)
{
	int clifd;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen;
	struct epoll_event ev;
	cliaddrlen = sizeof(struct sockaddr);   //切记要初始化
		
	//接受连接
	clifd = accept(fd,(struct sockaddr *)&cliaddr,&cliaddrlen);

	if(clifd == -1)   printf( "accept error\n");
	else 
	{
					//ip 和  端口		
		printf( "accept a new client : %s : %d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
		//将该客户端加入epoll 事件中
		ev.data.fd = clifd;
		ev.events = EPOLLIN;
		epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);
	}
}

int do_read()
{

}

int do_write()
{

}
