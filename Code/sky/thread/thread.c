#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int number = 10;

void p(void)
{
    int a = 10000;
    while(a--) number++;
    printf("p中%d\n",number);
}
void q(void)
{
    int a = 500;
    while(a--) number++;
    printf("q中%d\n",number);
}

int main(void)
{
    int status;
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,(void*)(&p),NULL);
    pthread_create(&tid2,NULL,(void*)(&q),NULL);
    pthread_join(tid1,(void*)&status);//等待一个线程的结束
    pthread_join(tid2,(void*)&status);

}
