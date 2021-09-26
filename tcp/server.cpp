#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
int main(int argc,char* argv[])
{
	//creat socket
	int serv_sock;	
	if((serv_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==0)
	{
		perror("socket error!");
		return 1;
	}
	//绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(1234);  //port

	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
	{
		perror("bind error!");
		return 1;
	}
	//waiting requests
	if(listen(serv_sock,20)<0)
	{
		perror("listen error!");
		return 1;
	}

	//accept
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size=sizeof(clnt_addr);
	int clnt_sock;
	if((clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size))<0)
	{
		perror("accept error!");
		return 1;
	}

	char buffer[100];
	read(clnt_sock,buffer,sizeof(buffer));
	write(clnt_sock,buffer,sizeof(buffer));

	//close
	close(clnt_sock);
	close(serv_sock);

	return 0;
}
