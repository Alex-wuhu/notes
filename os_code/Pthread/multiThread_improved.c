#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define ARGUMENT_NUMBER 20
long long result=0;
void *ThreadFunc(void*n)
{
	long long i;
	long long x=0;
	long long number=*((long long*)n);
	printf("number=%lld\n",number);
	for(i=0;i<25000000;i++)
		x+=number;  //  temroarily store 
	result+=x;
}
int main(void)
{
	pthread_t threadID[ARGUMENT_NUMBER];

	long long argument[ARGUMENT_NUMBER];
	long long i;
	for(i=0;i<ARGUMENT_NUMBER;i++)    // assign the numbers
		argument[i]=i;
	
	for(i=0;i<ARGUMENT_NUMBER;i++)
	{
		pthread_create(&(threadID[i]),NULL,ThreadFunc,(void*)&argument[i]);  //create threads
	}
	printf("Main Thread is waiting for child Thread!\n");

	for(i=0;i<ARGUMENT_NUMBER;i++)
	{
		pthread_join(threadID[i],NULL);               // waiting for other threads
	}
	printf("result:%lld",result);
	return 0;
}
