#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t chopstick[6];

void *philosopher();
void eat(int);

int main()
{
	int i,a[6];
	pthread_t tid[6];


	for(i=0;i<6;i++)
		sem_init(&chopstick[i],0,1);
	for(i=0;i<6;i++)
	{
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void*)&a[i]);
	}
	for(i=0;i<6;i++)
		pthread_join(tid[i],NULL);
}
void *philosopher(void *num)
{
	int phil=*(int *)num;
	
	printf("\nPhilosopher %d has entered room",phil+1);    //phil+1 only for better looking
	if(phil%2==0)    // if the philosopher is even grap the left chopstick firstly
	{
		sem_wait(&chopstick[phil]);
		sem_wait(&chopstick[(phil+1)%5]);
		eat(phil);
		sleep(2);
		sem_post(&chopstick[(phil+1)%5]);
		sem_post(&chopstick[phil]);
	}
	else    // if the phiosopher is odd  grap the right chopstick firstly
	{

		sem_wait(&chopstick[(phil+1)%5]);
		sem_wait(&chopstick[phil]);
		eat(phil);
		sem_post(&chopstick[phil]);
		sem_post(&chopstick[(phil+1)%5]);
	}


	printf("\nPhilosopher %d has finished eating",phil+1);
}
void eat(int phil)
{
	printf("\nPhilosopther %d is eating",phil+1);
}
