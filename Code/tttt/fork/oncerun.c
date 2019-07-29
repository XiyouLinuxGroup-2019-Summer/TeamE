#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
	printf( "Function run is runing in thread %lu\n",pthread_self( ));
}


void *thread1(void *arg)
{
	pthread_t thid = pthread_self( );
	printf( "Current thread's ID is %lu\n",thid);
	pthread_once(&once,run);
	printf( "thread1 ends\n");
}

void *thread2(void *arg)
{
	pthread_t thid = pthread_self();
	printf( "Current thread's ID is %lu\n",thid);
	pthread_once(&once,run);
	printf( "thread2 ends\n");
}

int main( )
{
	pthread_t thid1,thid2;
	pthread_create(&thid1,NULL,thread1,NULL);
	pthread_create(&thid2,NULL,thread2,NULL);

	sleep(3);
	printf( "main is exit !\n");
	exit(0);

}

