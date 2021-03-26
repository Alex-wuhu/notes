#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define PIPENAME "./named_pipe_file"
#define MSG_SIZE 80

int main(void)
{
	char msg[MSG_SIZE];
	int fd;
	int ret,i;
	fd=open(PIPENAME,O_WRONLY);
	if(fd<0)
	{
		printf("OPen failed\n");
		return 0;
		}
	while(1)
	{
		printf("Process B Send msg to A(q for quit):");
		scanf("%s",msg);
		
		ret=write(fd,msg,sizeof(msg));
		if(ret<0)
		{
			printf("Write failed\n");
			return 0;
		}
		if(strcmp(msg,"q")==0)
		{
			printf("bye!\n");
			break;
		}
	}
	return 0;
}

