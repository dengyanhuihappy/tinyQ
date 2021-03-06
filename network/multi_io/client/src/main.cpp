#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("%s: input IP & port\n",argv[0]);
		return 1;
	}
	int sockfd,numbytes;
	char buf[100] = "hello world";
	struct hostent *he;
	struct sockaddr_in their_addr;
	
	//将基本名字和地址转换
	he = gethostbyname(argv[1]);
	
	//建立一个TCP套接口
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}
	
	//初始化结构体，连接到服务器的2323端口
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(atoi(argv[2]));
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero),8);
	
	//和服务器建立连接
	if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}

	
	//向服务器发送字符串
	while(1)
	{
		if(send(sockfd,buf,strlen(buf),0)==-1)
		{
			perror("send");
			exit(1);
		}
		sleep(2);
	}
	memset(buf,0,sizeof(buf));
	
	close(sockfd);
	return 0;
}
