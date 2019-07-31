#pragma once
 
#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <iostream>
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
using namespace std;

//用来保存所有的客户端的套接字
// clients_list save all the clients's socket
list<int> clients_list;
 
//客户端IP
/**********************   macro defintion **************************/
// server ip
#define SERVER_IP "127.0.0.1"
 
//端口
// server port
#define SERVER_PORT 8888
 
//epoll大小?
//epoll size
#define EPOLL_SIZE 5000
 
//消息的大小
//message buffer size
#define BUF_SIZE 0xFFFF
 
//欢迎语句

#define SERVER_WELCOME "欢迎加入聊天室！你的ID是:%d"
 
#define SERVER_MESSAGE "用户[%d]:%s"
 
// exit退出
#define EXIT "EXIT"
 
//提醒
#define CAUTION "当前聊天室中仅有一人!"
 
/**********************   some function **************************/
/**
  * @param sockfd: socket descriptor
  * @return 0
**/
//设为非阻塞监听，即轮询
int setnonblocking(int sockfd)
{
	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);   //设为非阻塞监听，即轮询
	return 0;
}
 
/**
  * @param epollfd: epoll handle
  * @param fd: socket descriptor
  * @param enable_et : enable_et = true, epoll use ET; otherwise LT
**/
void addfd(int epollfd, int fd, bool enable_et)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if (enable_et)						//传进来的使能位为1时，才指定监听的事件
		ev.events = EPOLLIN | EPOLLET;    //监听客户端的写事件和读事件
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	setnonblocking(fd);
	printf("fd成功添加到epoll!\n\n");
}
 
 
 
/**
  * @param clientfd: socket descriptor
  * @return : len
**/
int sendBroadcastmessage(int clientfd)
{
	// buf[BUF_SIZE] receive new chat message
	// message[BUF_SIZE] save format message
	char buf[BUF_SIZE], message[BUF_SIZE];
	bzero(buf, BUF_SIZE);
	bzero(message, BUF_SIZE);
 
	// receive message
	printf("收到来自[%d]的消息\n", clientfd);
	int len = recv(clientfd, buf, BUF_SIZE, 0);
 
	if (len == 0)  // len = 0 means the client closed connection  若len<0则表示出错
	{
		close(clientfd);
		clients_list.remove(clientfd); //server remove the client
		printf("[%d]关闭\n 当前聊天室中有%d个用户\n", clientfd, (int)clients_list.size());
 
	}
	else  //broadcast message 
	{
		if (clients_list.size() == 1) { // this means There is only one int the char room
			send(clientfd, CAUTION, strlen(CAUTION), 0);
			return len;
		}
		// format message to broadcast
		sprintf(message, SERVER_MESSAGE, clientfd, buf);
 
		list<int>::iterator it;
		for (it = clients_list.begin(); it != clients_list.end(); ++it) {
			if (*it != clientfd) {
				if (send(*it, message, BUF_SIZE, 0) < 0) { perror("error"); exit(-1); }
			}
		}
	}
	return len;
}
#endif // UTILITY_H_INCLUDED
