#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if( argc<2 )
	{
		printf("input sendfile path...\n");
		return -1;
	}

	int file_fd, sock_fd, conn_fd, clntAddrLen, fileLen, sendLen;
	struct sockaddr_in srvAddr, clntAddr;
	struct stat fileStat;
	
	if( (file_fd=open(argv[1], O_RDONLY, 0666))<=0 )
	{
		printf("open %s failed.\n", argv[1]);
		return -1;
	}

	if( fstat(file_fd, &fileStat)<0 )
	{
		printf("fstat failed!\n");
		close(file_fd);
		return -1;
	}

	fileLen = fileStat.st_size;
	
	if( (sock_fd=socket(AF_INET, SOCK_STREAM, 0))<=0 )
	{
		perror("socket");
		close(file_fd);
		return -1;
	}

	bzero(&srvAddr, sizeof(srvAddr));
	bzero(&clntAddr, sizeof(clntAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_port = htons(9999);

	if( bind(sock_fd, (struct sockaddr*)&srvAddr, sizeof(srvAddr))<0 )
	{
		perror("bind");
		close(file_fd);
		close(sock_fd);
	}

	if( listen(sock_fd, 5)<0 )
	{
		perror("listen");
		close(file_fd);
		close(sock_fd);
	}
	
	clntAddrLen = sizeof(struct sockaddr);
	if( (conn_fd=accept(sock_fd, (struct sockaddr*)&clntAddr, (socklen_t*)&clntAddrLen))<0 )
	{
		//printf("accept failed!\n");
		perror("accept");
		close(file_fd);
		close(sock_fd);

		return -1;
	}

	printf("new connection, ip:%s, port:%d\n",
		inet_ntoa(clntAddr.sin_addr), ntohs(clntAddr.sin_port));

	if( (sendLen=sendfile(conn_fd, file_fd, NULL, fileLen))<0 )
	{
		printf("sendfile failed!\n");
	}else{
		printf("sendfile ok, send len:%d\n", sendLen);
	}

	close(conn_fd);
	close(file_fd);
	close(sock_fd);

	return 0;
}

