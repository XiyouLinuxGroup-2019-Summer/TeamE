#include"apue.h"

int main(void)
{
//	getpid() 的返回值 为 pid_t  类型,  ld
	printf("这个进程的进程ID为 %ld\n",(long)getpid()); // 标准会保证 getpid 的返回值是 long ,长整型可以提高可移植性

	exit(0);
}
