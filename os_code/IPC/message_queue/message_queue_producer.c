#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

struct msgbuf
{
	long msgtype;
	char mtext[20];
};
int main(void)
{
	key_t key_id;
	int i=0;
	struct msgbuf sndbuf;

	key_id=msgget((key_t)1234,IPC_CREAT|0666);
	if(key_id==-1)
	{
		perror("msgget error:");
		return 0;
	}
	sndbuf.msgtype=3;
	while(1)
	{
		printf("Procss B send msg to A(q for quit):");
		scanf("%s",sndbuf.mtext);
		if(msgsnd(key_id,(void *)&sndbuf,sizeof(struct msgbuf),IPC_NOWAIT)==-1)
			perror("msgsend error;");
		if(strcmp(sndbuf.mtext,"q")==0)
		{
			printf("bye!\n");
			break;
		}

	}
	return 0;
}
