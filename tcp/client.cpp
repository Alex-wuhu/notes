#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
	
	int sock=socket(AF_INET,SOCK_STREAM,0);
	//request
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));            //
	serv_addr.sin_family=AF_INET;                       // using IPV4
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");   //IP address
	serv_addr.sin_port=htons(1234);
	connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));


	//read
	char buffer[100]={0};
	printf("Input a string:");
	scanf("%s",buffer);
	printf("%s",buffer);
	int w;
	if((w=write(sock,buffer,sizeof(buffer)))<0)
	{
		perror("write error!");
		return 1;
	}
	char buffer_rev[100];
	read(sock,buffer_rev,sizeof(buffer_rev));

	printf("Message from server:%s\n",buffer_rev);

	close(sock);

	return 0;

}
