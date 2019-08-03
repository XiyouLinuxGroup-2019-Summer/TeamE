#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

pthread_mutex_t chopstick[6];   //5 把锁的数组

void get(int *left,int *right,char phi) 
{
	switch (phi)
	{
		 case 'A':
		 *left = 5;
		 *right = 1;
		 break;

	 	 case 'B':
		 *left = 1;
		 *right = 2;
		break;

		case 'C':
		 *left = 2;
		 *right = 3;
		break;

		case 'D':
		 *left = 3;
		 *right = 4;
		break;

		case 'E':
		 *left = 4;
		 *right = 5;
		break;
	}
}
void *eat_think(void *arg)
{
	 char phi = *(char *)arg;   //将参数传入
	 int left,right;
	 get(&left,&right,phi);    //根据不同的 哲学家 给 每个哲学家 在左 边 和右边 的 筷子
	 for(;;)
	 {
		 usleep(10);
		 pthread_mutex_lock(&chopstick[left]);   // 给每个人 左 手 那一只筷子
		 printf("left = Philosopher %c fetches chopstick %d\n", phi,left); 
	//	getchar( );
	//	getchar();
		//进行尝试 看他右手边的筷子 被人拿了没
		if (pthread_mutex_trylock(&chopstick[right]) ==EBUSY)  //只有同时 拿了左手边的锁和右手边的锁 才可以 进行就餐
		{
			 pthread_mutex_unlock(&chopstick[left]);  //如果 右手边的筷子 被拿走了  ,将它的左手边 的筷子也释放掉
			 continue;  //重新进行 拿筷子
		}
	//	printf( "-----------------------------------------------------\n");

		printf("right = Philosopher %c fetches chopstick %d\n", phi,right);
		 printf("Philosopher %c is eating.\n",phi);
		 usleep(10);
		 pthread_mutex_unlock(&chopstick[left]);  //将 左手边的筷子 放回 原位
		 printf("left = Philosopher %c release chopstick %d\n", phi,left);
		 pthread_mutex_unlock(&chopstick[right]);  //将右手边的筷子 放回原位
		 printf("right = Philosopher %c release chopstick %d\n", phi,right);

//		getchar( );
	}
 }
int main()
{
	pthread_t A,B,C,D,E; //5个哲学家

	 int i;
	 for (i = 0; i < 5; i++)     pthread_mutex_init(&chopstick[i],NULL);  //创建 5 把锁

	 //让 5个哲学家  吃
	 pthread_create(&A,NULL, eat_think, (void *)"A");
	 pthread_create(&B,NULL, eat_think, (void *)"B");
	 pthread_create(&C,NULL, eat_think, (void *)"C");
	 pthread_create(&D,NULL, eat_think, (void *)"D");
	 pthread_create(&E,NULL, eat_think, (void *)"E");

	 pthread_join(A,NULL);
	 pthread_join(B,NULL);
	 pthread_join(C,NULL);
	 pthread_join(D,NULL);
	 pthread_join(E,NULL);

	return 0;
}
