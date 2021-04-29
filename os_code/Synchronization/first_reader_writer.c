#include<unistd.h>
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#define COUNT 10000
sem_t wrt;
sem_t s;
int readcount=0;
void writer();
void reader();

int cur_writer=0;
int cur_count=0;
int main(void)
{
	int i;
	sem_init(&wrt,0,1);
	sem_init(&s,0,1);
	int argu[5]={0,1,2,3,4};
	pthread_t thread_reader[2],thread_writer[5];
	for(i=0;i<2;i++)
		pthread_create(&thread_reader[i],NULL,(void *)&reader,NULL);

	for(i=0;i<5;i++)
		pthread_create(&thread_writer[i],NULL,(void *)&writer,(void *)&argu[i]);

	for(i=0;i<2;i++)
		pthread_join(thread_reader[i],NULL);
	for(i=0;i<5;i++)
		pthread_join(thread_writer[i],NULL);

	sem_destroy(&wrt);
	sem_destroy(&s);
	return 0;
}
void writer(void *n )
{
	int i;
	int *number=(int*)n;
	for(i=0;i<COUNT;i++)
	{
		usleep(100000);
		sem_wait(&wrt);   //LOCK
		cur_count++;
	        cur_writer=*number;	// critical section
	
		sem_post(&wrt);   //UNLOCK
	}
}
void reader()
{
	int i;
	for(i=0;i<COUNT;i++)
	{
		usleep(30000);
		sem_wait(&s);     // Lock
		readcount++;
		if(readcount==1)
			sem_wait(&wrt);  //if id is the first reader,it will block writer
	
		sem_post(&s);     //UNLOCK
		
		printf("The most recent writer id: [%d],count :[%d]\n",cur_writer,cur_count); //critical section
		
		sem_wait(&s);    //LOCK  before change readcount
		readcount--;
		if(readcount==0)
			sem_post(&wrt);
		sem_post(&s);   //unlock
	}
}


