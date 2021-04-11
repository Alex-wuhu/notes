#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#define CON 40000

struct smStruct
{
	int processidassign;
	int turn;
	int flag[2];
	int critical;
};
void lock(struct smStruct* s,int order)
{
	s->flag[order]=1;
	s->turn=1-order;
	while(s->flag[1-order]==1 && s->turn==1-order);
}
void unlock(struct smStruct* s,int order)
{
	s->flag[order]=0;
}
int main(int argc, char *argv[])
{
	int shmid;
	void *shmaddr;
	int i,ret;
	int localcount=0;
	int Myorder=atoi(argv[0]);
	printf("Myorder = %d,process pid= %d\n",Myorder,getpid());
	// get shared memory
	shmid=shmget((key_t)1234,1024,IPC_CREAT|0666);
	if(shmid==-1)
	{
		perror("shared memory failed\n");
		return 0;
	}
	// attch shared memory
	shmaddr=shmat(shmid,(void *)0,0);
	if(shmaddr==(char*)-1)
	{
		perror("attahc failed\n");
		return 0;
	}
	struct smStruct * smstruct=shmaddr;
	// sum start
	for(i=0;i<CON;i++)
	{
		localcount++;
		lock(smstruct,Myorder);
		smstruct->critical++;
		unlock(smstruct,Myorder);
	}
	// detach the shared memory
	ret=shmdt(shmaddr);
	if(ret==-1)
	{
		perror("detach failed\n");
		return 0;
	}
	printf("child finish! local count=%d\n",localcount);
	return 0;
}
