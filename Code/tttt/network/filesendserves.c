#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<error.h>
#include<memory.h>
#include<stdlib.h>

#define MAXLINE 4096
#define BUFFER_SIZE 1024

int main()
{
	int sockfd,temp,n;
	struct sockaddr_in server,client;
	char filename[100];
	char filepath[100];

	char *buffer;//文件 buffer 
	int fileTrans;
	buffer = (char *)malloc(sizeof(char)*BUFFER_SIZE);
	bzero(buffer,BUFFER_SIZE);

	if((sock))
}
