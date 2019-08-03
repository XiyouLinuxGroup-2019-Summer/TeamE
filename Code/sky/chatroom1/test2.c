#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
/* 
哲学家只有拿到一双筷子才可以吃饭，而一人拿到筷子其他人就不能同时拿到筷子(但是他自己可以主动释放筷子)
所以利用互斥锁的特点模拟这个过程
１．得到哲学家和筷子的位置关系图
２．每个哲学家试图拿起左边筷子，如果其他人拿到，就等(思考)。否则，他拿到左边筷子(lock)
３．尝试拿到右边筷子(trylock)，如果其他人占用，就释放已得到的左筷子，重新去拿筷子(continue)。否则，拿到右筷子
4.拿到一双筷子，吃饭，释放筷子，重新去尝试拿筷子。
*/

pthread_mutex_t chopstick[6] ;//5把互斥锁　对应五支筷子

//获得哲学家和筷子位置关系
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
        char phi = *(char *)arg;//取出参数哲学家的名字
        int left,right;

        get(&left,&right,phi);//获悉每个哲学家左右两侧的筷子,就是把哲学家和筷子的位置图表示出来
        
        for(int i = 0;i<5;i++)
        {
            usleep(10);

            pthread_mutex_lock(&chopstick[left]);
            //取到他左边的筷子，对筷子加锁，其他人没办法拿到这支筷子,如果其他人拿到那就等，知道有人放弃这支筷子
            printf("Philosopher %c fetches chopstick %d\n", phi,left);

            if (pthread_mutex_trylock(&chopstick[right]) == EBUSY)
            //尝试拿起右边筷子，但不会阻塞当前线程，如果返回EBUSY说明已经被其他人锁住(拿到筷子)那么他解锁(放弃当前筷子)
            {
                pthread_mutex_unlock(&chopstick[left]);//放弃筷子
                continue;//没办法吃东西，直接进入下次思考、取筷子
            }

            //又拿起了右筷子
            printf("Philosopher %c fetches chopstick %d\n", phi,right);
           //同时拥有两支筷子可以吃饭
            printf("Philosopher %c is eating.\n",phi);

            
            usleep(10);

            //进餐完毕，释放两支筷子
            pthread_mutex_unlock(&chopstick[left]);
            printf("Philosopher %c release chopstick %d\n", phi,left);
            pthread_mutex_unlock(&chopstick[right]);
            printf("Philosopher %c release chopstick %d\n", phi,right);
        }
}
int main()
{
            pthread_t A,B,C,D,E; //5个哲学家
            int i;
            for (i = 0; i < 5; i++)//初始化五把锁
                pthread_mutex_init(&chopstick[i],NULL);

            //创建五个线程，即五个哲学家，创建后指向eat_think函数,并把哲学家名字传过去
            pthread_create(&A,NULL, eat_think, (void *)"A");
            pthread_create(&B,NULL, eat_think, (void *)"B");
            pthread_create(&C,NULL, eat_think, (void *)"C");
            pthread_create(&D,NULL, eat_think, (void *)"D");
            pthread_create(&E,NULL, eat_think, (void *)"E");

            //销毁五个线程
            pthread_join(A,NULL);
            pthread_join(B,NULL);
            pthread_join(C,NULL);
            pthread_join(D,NULL);
            pthread_join(E,NULL);
            return 0;
}
