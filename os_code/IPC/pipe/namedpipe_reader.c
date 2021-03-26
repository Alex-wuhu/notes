#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define PIPENAME "./named_pipe_file"

int main()
{
	int ret;
	char msg[512];
	int fd;
	pid_t pid;

	//delete if named pipe exists
	ret =access(PIPENAME,F_OK);
	if(ret ==0){
		unlink(PIPENAME); //delete the pipe
	}
	ret=mkfifo(PIPENAME,0666);
	if(ret<0)
	{
		printf("creation of named pipe failed\n");
		return 0;
	}
	fd=open(PIPENAME,O_RDWR);
	if(fd<0)
	{
		printf("Opening of named pipe failed\n");
		return 0;
	}
	while(1)
	{
		ret=read(fd,msg,sizeof(msg));
		if(ret<0)
		{
			printf("Read failed\n");
			return 0;
		}
		printf("Process A received from B:%s\n",msg);
		if(strcmp(msg,"q")==0)
		{
			printf("bye!\n");
				break;
		}
	}
	return 0;
}
