#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"my_recv.h"


#define BUFFSIZE 1024
#define MAXSIZE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 4507
#define FDSIZE 1024

char chat[1024];
//void my_err(const char * err_string,int line);

int main(int argc,char **argv)
{
	int i;
	int ret;
	int conn_fd;
	int serv_port;
	struct sockaddr_in serv_addr;
	char recv_buf[BUFFSIZE];

	conn_fd = socket(AF_INET,SOCK_STREAM,0);
	
	memset(&serv_addr,0,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,IPADDRESS,&serv_addr.sin_addr);

	if(connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0)   my_err("connect",__LINE__);
	if((ret = my_recv(conn_fd,recv_buf,sizeof(recv_buf))) < 0)  my_err("recv",__LINE__);
	for(i = 0;i < ret;i++)  printf( "%c",recv_buf[i]); 
	printf( "\n");
	while(1)
	{
		int re;
		//scanf( "%s",chat);
		gets(chat);
		if(( re = send(conn_fd,chat,strlen(chat),0)) < 0)  my_err("client send err",__LINE__);
		if(strcmp(chat,"exit") == 0)  break;
		memset(chat,0,sizeof(chat));
	}

	close(conn_fd);

	return 0;

}

/*void my_err(const char * err_string,int line)
{
	fprintf( stderr,"line:%d ",line);
	perror(err_string);
}*/
