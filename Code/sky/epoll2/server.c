#include "utility.h"
 
int main() {
	//服务器IP+PORT
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
 
	//创建监听socket
	int listener = socket(PF_INET, SOCK_STREAM, 0);
	if (listener < 0) {
		perror("listener"); exit(1);
	}
	printf("监听套接字创建 \n");
 
	//绑定地址
	if (bind(listener, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("bind error");
		exit(1);
	}
	//监听设置套接字为监听套接字
	int ret = listen(listener, 128);   //设置最大连接排队请求个数
	if (ret < 0) {
		perror("listen error");
		exit(1);
	}
	printf("开始监听 %s\n", SERVER_IP);
 
 
	//在内核中创建事件表
	int epfd = epoll_create(EPOLL_SIZE);
	if (epfd < 0) {
		perror("epfd error");
		exit(1);
	}
	printf("epoll[%d]创建成功\n", epfd);
	static struct epoll_event events[EPOLL_SIZE];
 
	//往内核事件表里添加事件  ，并且设置为非阻塞监听，即轮询
    //将监听事件加入内核事件列表
	addfd(epfd, listener, true); 
 
 
	//主循环
	while (1) {

		//epoll_events_count表示就绪事件的数目
		int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
		if (epoll_events_count < 0) {
			perror("epoll failure");
			break;
		}
 
		/* printf("epoll_events_count = %d\n", epoll_events_count); */
		//处理这epoll_events_count个就绪事件
		for (int i = 0; i < epoll_events_count; i++) {
			int sockfd = events[i].data.fd;
			//若是新用户连接的情况
			if (sockfd == listener) {
				struct sockaddr_in client_address;
				socklen_t client_addrLength = sizeof(struct sockaddr_in);
				int clientfd = accept(listener, (struct sockaddr*)&client_address, &client_addrLength);
 
				printf("新客户端请求连接 %s : % d(IP : port), clientfd = %d \n",
					inet_ntoa(client_address.sin_addr),
					ntohs(client_address.sin_port),
					clientfd);
 
				addfd(epfd, clientfd, true);
 
 
				// 服务端用list保存用户连接
                // 服务端socket加入list
				clients_list.push_back(clientfd);
				printf("新客户端[%d]连接\n", clientfd);
				printf("聊天室中有%d个客户端\n", (int)clients_list.size());
 
 
				// 服务端发送欢迎信息
				printf("向新连接客户端发送欢迎消息\n");
				char message[BUF_SIZE];
				bzero(message, BUF_SIZE);
				sprintf(message, SERVER_WELCOME, clientfd);
				int ret = send(clientfd, message, BUF_SIZE, 0);//clientfd表示新连接客户端
				if (ret < 0) { perror("send error"); exit(-1); }
			}
 
			//不是新建连接事件的话，处理用户发来的消息，并广播，使其他用户收到信息
			else 
            {
				int ret = sendBroadcastmessage(sockfd);
				if (ret < 0) { perror("error"); exit(-1); }
			}
		}
	}
	close(listener);//关闭socket
	close(epfd);//关闭
	return 0;
}
