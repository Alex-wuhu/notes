#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
int main(void)
{
	int shmid;
	void *shmaddr;
	int ret;
	char temp[20];
	//get shared memory id 
	shmid=shmget((key_t)1234,1024,IPC_CREAT|0666);
	if(shmid==-1)
	{
		perror("shared memory failed\n");
		return 0;
	}
	//attach shared memory 
	
	shmaddr=shmat(shmid,(void*)0,0);
	if(shmaddr==(char *)-1)
	{
		perror("attach failed\n");
		return 0;
	}
	while(1)
	{
		if(strlen(shmaddr)!=0 &&strcmp(shmaddr,temp)!=0)
		{
			printf("Process A received from B:%s\n",(char *)shmaddr);	
			strcpy(temp,shmaddr);
			if(strcmp(temp,"q")==0)
			{
				printf("bye!\n");
				break;
			}
		}
	}
	//detach the shared memory
	ret=shmdt(shmaddr);
	if(ret==-1)
	{
		perror("detach failed\n");
		return 0;
	}
	
	//remove shared memory
	ret=shmctl(shmid,IPC_RMID,0);
	if(ret==-1)
	{
		perror("remove failed\n");
		return 0;
	}
	
	return 0;
}
