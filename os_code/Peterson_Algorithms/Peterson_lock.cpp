#include<atomic>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define CON 2000000
using namespace std;

int critical_section=0;
atomic_int turn(0);
atomic_int flag0(0),flag1(0);

void lock(int self)
{
	if(self==0)
	{
		flag0.store(1);
		turn.store(1);
		while(flag1.load()==1 && turn.load()==1);
	}
	else
	{
		flag1.store(0);
		turn.store(0);
		while(flag0.load()==1 &&turn.load()==0);
	}	
}
void unlock(int self)
{
	if(self==0)
		flag0.store(0);
	else
		flag1.store(0);
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
