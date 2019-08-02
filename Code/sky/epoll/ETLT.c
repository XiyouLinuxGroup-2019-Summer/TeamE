  1 /* 
  2  *url:http://www.cnblogs.com/yuuyuu/p/5103744.html
  3  *
  4  */
  5 
  6 #include <stdio.h>
  7 #include <stdlib.h>
  8 #include <string.h>
  9 #include <errno.h>
 10 #include <unistd.h>
 11 #include <fcntl.h>
 12 #include <arpa/inet.h>
 13 #include <netinet/in.h>
 14 #include <sys/socket.h>
 15 #include <sys/epoll.h>
 16 
 17 /* 最大缓存区大小 */
 18 #define MAX_BUFFER_SIZE 5
 19 /* epoll最大监听数 */
 20 #define MAX_EPOLL_EVENTS 20
 21 /* LT模式 */
 22 #define EPOLL_LT 0
 23 /* ET模式 */
 24 #define EPOLL_ET 1
 25 /* 文件描述符设置阻塞 */
 26 #define FD_BLOCK 0
 27 /* 文件描述符设置非阻塞 */
 28 #define FD_NONBLOCK 1
 29 
 30 /* 设置文件为非阻塞 */
 31 int set_nonblock(int fd)
 32 {
 33     int old_flags = fcntl(fd, F_GETFL);
 34     fcntl(fd, F_SETFL, old_flags | O_NONBLOCK);
 35     return old_flags;
 36 }
 37 
 38 /* 注册文件描述符到epoll，并设置其事件为EPOLLIN(可读事件) */
 39 void addfd_to_epoll(int epoll_fd, int fd, int epoll_type, int block_type)
 40 {
 41     struct epoll_event ep_event;
 42     ep_event.data.fd = fd;
 43     ep_event.events = EPOLLIN;
 44 
 45     /* 如果是ET模式，设置EPOLLET */
 46     if (epoll_type == EPOLL_ET)
 47         ep_event.events |= EPOLLET;
 48 
 49     /* 设置是否阻塞 */
 50     if (block_type == FD_NONBLOCK)
 51         set_nonblock(fd);
 52 
 53     epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ep_event);
 54 }
 55 
 56 /* LT处理流程 */
 57 void epoll_lt(int sockfd)
 58 {
 59     char buffer[MAX_BUFFER_SIZE];
 60     int ret;
 61 
 62     memset(buffer, 0, MAX_BUFFER_SIZE);
 63     printf("开始recv()...\n");
 64     ret = recv(sockfd, buffer, MAX_BUFFER_SIZE, 0);
 65     printf("ret = %d\n", ret);
 66     if (ret > 0)
 67         printf("收到消息:%s, 共%d个字节\n", buffer, ret);
 68     else
 69     {
 70         if (ret == 0)
 71             printf("客户端主动关闭！！！\n");
 72         close(sockfd);
 73     }
 74 
 75     printf("LT处理结束！！！\n");
 76 }
 77 
 78 /* 带循环的ET处理流程 */
 79 void epoll_et_loop(int sockfd)
 80 {
 81     char buffer[MAX_BUFFER_SIZE];
 82     int ret;
 83 
 84     printf("带循环的ET读取数据开始...\n");
 85     while (1)
 86     {
 87         memset(buffer, 0, MAX_BUFFER_SIZE);
 88         ret = recv(sockfd, buffer, MAX_BUFFER_SIZE, 0);
 89         if (ret == -1)
 90         {
 91             if (errno == EAGAIN || errno == EWOULDBLOCK)
 92             {
 93                 printf("循环读完所有数据！！！\n");
 94                 break;
 95             }
 96             close(sockfd);
 97             break;
 98         }
 99         else if (ret == 0)
100         {
101             printf("客户端主动关闭请求！！！\n");
102             close(sockfd);
103             break;
104         }
105         else
106             printf("收到消息:%s, 共%d个字节\n", buffer, ret);
107     }
108     printf("带循环的ET处理结束！！！\n");
109 }
110 
111 
112 /* 不带循环的ET处理流程，比epoll_et_loop少了一个while循环 */
113 void epoll_et_nonloop(int sockfd)
114 {
115     char buffer[MAX_BUFFER_SIZE];
116     int ret;
117 
118     printf("不带循环的ET模式开始读取数据...\n");
119     memset(buffer, 0, MAX_BUFFER_SIZE);
120     ret = recv(sockfd, buffer, MAX_BUFFER_SIZE, 0);
121     if (ret > 0)
122     {
123         printf("收到消息:%s, 共%d个字节\n", buffer, ret);
124     }
125     else
126     {
127         if (ret == 0)
128             printf("客户端主动关闭连接！！！\n");
129         close(sockfd);
130     }
131 
132     printf("不带循环的ET模式处理结束！！！\n");
133 }
134 
135 /* 处理epoll的返回结果 */
136 void epoll_process(int epollfd, struct epoll_event *events, int number, int sockfd, int epoll_type, int block_type)
137 {
138     struct sockaddr_in client_addr;
139     socklen_t client_addrlen;
140     int newfd, connfd;
141     int i;
142 
143     for (i = 0; i < number; i++)
144     {
145         newfd = events[i].data.fd;
146         if (newfd == sockfd)
147         {
148             printf("=================================新一轮accept()===================================\n");
149             printf("accept()开始...\n");
150 
151             /* 休眠3秒，模拟一个繁忙的服务器，不能立即处理accept连接 */
152             printf("开始休眠3秒...\n");
153             sleep(3);
154             printf("休眠3秒结束！！！\n");
155 
156             client_addrlen = sizeof(client_addr);
157             connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addrlen);
158             printf("connfd = %d\n", connfd);
159 
160             /* 注册已链接的socket到epoll，并设置是LT还是ET，是阻塞还是非阻塞 */
161             addfd_to_epoll(epollfd, connfd, epoll_type, block_type);
162             printf("accept()结束！！！\n");
163         }
164         else if (events[i].events & EPOLLIN)
165         {
166             /* 可读事件处理流程 */
167 
168             if (epoll_type == EPOLL_LT)    
169             {
170                 printf("============================>水平触发开始...\n");
171                 epoll_lt(newfd);
172             }
173             else if (epoll_type == EPOLL_ET)
174             {
175                 printf("============================>边缘触发开始...\n");
176 
177                 /* 带循环的ET模式 */
178                 epoll_et_loop(newfd);
179 
180                 /* 不带循环的ET模式 */
181                 //epoll_et_nonloop(newfd);
182             }
183         }
184         else
185             printf("其他事件发生...\n");
186     }
187 }
188 
189 /* 出错处理 */
190 void err_exit(char *msg)
191 {
192     perror(msg);
193     exit(1);
194 }
195 
196 /* 创建socket */
197 int create_socket(const char *ip, const int port_number)
198 {
199     struct sockaddr_in server_addr;
200     int sockfd, reuse = 1;
201 
202     memset(&server_addr, 0, sizeof(server_addr));
203     server_addr.sin_family = AF_INET;
204     server_addr.sin_port = htons(port_number);
205 
206     if (inet_pton(PF_INET, ip, &server_addr.sin_addr) == -1)
207         err_exit("inet_pton() error");
208 
209     if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
210         err_exit("socket() error");
211 
212     /* 设置复用socket地址 */
213     if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
214         err_exit("setsockopt() error");
215 
216     if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
217         err_exit("bind() error");
218 
219     if (listen(sockfd, 5) == -1)
220         err_exit("listen() error");
221 
222     return sockfd;
223 }
224 
225 /* main函数 */
226 int main(int argc, const char *argv[])
227 {
228     if (argc < 3)
229     {
230         fprintf(stderr, "usage:%s ip_address port_number\n", argv[0]);
231         exit(1);
232     }
233 
234     int sockfd, epollfd, number;
235 
236     sockfd = create_socket(argv[1], atoi(argv[2]));
237     struct epoll_event events[MAX_EPOLL_EVENTS];
238 
239     /* linux内核2.6.27版的新函数，和epoll_create(int size)一样的功能，并去掉了无用的size参数 */
240     if ((epollfd = epoll_create1(0)) == -1)
241         err_exit("epoll_create1() error");
242 
243     /* 以下设置是针对监听的sockfd，当epoll_wait返回时，必定有事件发生，
244      * 所以这里我们忽略罕见的情况外设置阻塞IO没意义，我们设置为非阻塞IO */
245 
246     /* sockfd：非阻塞的LT模式 */
247     addfd_to_epoll(epollfd, sockfd, EPOLL_LT, FD_NONBLOCK);
248 
249     /* sockfd：非阻塞的ET模式 */
250     //addfd_to_epoll(epollfd, sockfd, EPOLL_ET, FD_NONBLOCK);
251 
252    
253     while (1)
254     {
255         number = epoll_wait(epollfd, events, MAX_EPOLL_EVENTS, -1);
256         if (number == -1)
257             err_exit("epoll_wait() error");
258         else
259         {
260             /* 以下的LT，ET，以及是否阻塞都是是针对accept()函数返回的文件描述符，即函数里面的connfd */
261 
262             /* connfd:阻塞的LT模式 */
263             epoll_process(epollfd, events, number, sockfd, EPOLL_LT, FD_BLOCK);
264 
265             /* connfd:非阻塞的LT模式 */
266             //epoll_process(epollfd, events, number, sockfd, EPOLL_LT, FD_NONBLOCK);
267 
268             /* connfd:阻塞的ET模式 */
269             //epoll_process(epollfd, events, number, sockfd, EPOLL_ET, FD_BLOCK);
270 
271             /* connfd:非阻塞的ET模式 */
272             //epoll_process(epollfd, events, number, sockfd, EPOLL_ET, FD_NONBLOCK);
273         }
274     }
275 
276     close(sockfd);
277     return 0;
278 }
