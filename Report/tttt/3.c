#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

typedef struct node
{
	int data;
	struct node *next;

}Node;
Node *head = NULL;
void *producer(void *arg)
{
	int i = 0;
	while(1)
	{
	//	sleep(1);
		i++;
		Node*pnew = (Node *)malloc(sizeof(Node));
		pnew->data = i;
		pthread_mutex_lock(&mutex);
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

		printf( "contusm %d\n",temp->data);

		free(temp);
		pthread_mutex_unlock(&mutex);
	}


}


int main()
{
	pthread_t tid1,tid2;
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&mutex,NULL);


	//生产者
	pthread_create(&tid1,NULL,producer,NULL);
	//消费者
	pthread_create(&tid2,NULL,contusm,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);


}
