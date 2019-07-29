#ifdef _MY_RECV_H
#define _MY_RECV_H

#define BUFSIZE 1024

void my_err(const char *s,int line);
int my_recv(int conn_fd,char *data_buf,int len);
#endif
