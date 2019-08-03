#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

pthread_cond_t cond;
pthread_cond_t cond1;
pthread_mutex_t mutex;

typedef struct node
{
	int data;
	struct node *next;

}Node;
Node *head = NULL;
int sum = 0;     //10 个为满
void *producer(void *arg)
{
	int i = 0;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(sum == 10)
		{
			pthread_cond_wait(&cond1,&mutex);
		}
	//	sleep(1);
		i++;
		Node*pnew = (Node *)malloc(sizeof(Node));
		sum++;
		pnew->data = i;
		printf( "生产 了%d\n",i);
		pnew->next = head;
		head = pnew;
		pthread_mutex_unlock(&mutex);
		
		pthread_cond_signal(&cond);
	}
	
}

void *contusm(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(head == NULL)
		{
			pthread_cond_wait(&cond,&mutex);
		}
		
		Node * temp;
		temp = head;
		head = head->next;
		sum--;
		printf( "消费了 %d\n",temp->data);

		free(temp);
	
		pthread_mutex_unlock(&mutex);
		
		pthread_cond_signal(&cond1);
	}


}


int main()
{
	pthread_t tid1,tid2;
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond1,NULL);


	//生产者
	pthread_create(&tid1,NULL,producer,NULL);
	//消费者
	pthread_create(&tid2,NULL,contusm,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);


}
