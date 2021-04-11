#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define CON 2000000

int critical_section=0;
int turn=0;
int flag[2]={0,0};

void lock(int self)
{
	flag[self]=1;
	turn=1-self;
	while(flag[1-self]==1 &&turn==1-self);
}
void unlock(int self)
{
	flag[self]=0;

}
void *Func(void *s)
{
	int i;
	int *thread_number=(int *)s;
	for (i=0;i<CON;i++)
	{
		lock(*thread_number);
		critical_section++;
		unlock(*thread_number);
	}

	
}
int main(void)
{
	pthread_t p1,p2;

	int argument[2]={0,1};

	pthread_create(&p1,NULL,Func,(void *)&argument[0]);
	pthread_create(&p2,NULL,Func,(void *)&argument[1]);
	
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	
	printf("Actual Count: %d |Expected Count:%d\n",critical_section,CON*2);
	return 0;
}
