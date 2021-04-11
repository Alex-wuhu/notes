#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#define CON 40000
struct smStruct
{
	int processidassign;
	int turn;
	int flag[2];
	int critical;
};
int main(void)
{
	int shmid;
	void *shmaddr;
	int ret;
	struct smStruct* smstruct;
	// get shared memory id
	shmid=shmget((key_t)1234,1024,IPC_CREAT|0666);
	if(shmid==-1)
	{
		perror("shared memory failed\n");
		return 0;
	}
	// attach shared memory 
	shmaddr=shmat(shmid,(void*)0,0);
	if(shmaddr==(char *)-1)
	{
		perror("attach failed\n");
		return 0;
	}
	//initialize smstruct
	smstruct=shmaddr;
	smstruct->turn=0;
	smstruct->processidassign=0;
	smstruct->flag[0]=0;
	smstruct->flag[1]=0;
	smstruct->critical=0;
	
	pid_t pid1;    //child1
	pid_t pid2;    //child2
	pid1=fork();
	if(pid1==0)		
	{
		execl("./child","0",NULL);
	}
	else
	{
		pid2=fork();
		if(pid2==0)
			execl("./child","1",NULL);
	}


	int st1,st2;
	waitpid(pid1,&st1,0);
	waitpid(pid2,&st2,0);
	printf("Actual Count: %d|Expected Count:%d\n",smstruct->critical,CON*2);
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

