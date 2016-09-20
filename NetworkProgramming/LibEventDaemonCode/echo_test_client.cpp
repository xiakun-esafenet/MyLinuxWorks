/************** 服务器回射实例 ***************/
/***	使用libevent编程 				   ***/
/***	客户端部分		 				   ***/

#include "../myhead.h"

using namespace std;

extern int errno;

int on_connect(const char* ip, int port)
{
	int sockfd = 0;
	struct sockaddr_in srvAddr;
	
	if( (sockfd=socket(AF_INET, SOCK_STREAM, 0))<=0 )
	{
		perror("socket");
		return -1;
	}

	bzero(&srvAddr, sizeof(srvAddr));

	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(port);
	inet_aton(ip, &srvAddr.sin_addr);

	if( connect(sockfd, (struct sockaddr*)&srvAddr, sizeof(struct sockaddr))<0 )
	{
		perror("connect");
		close(sockfd);
		return -1;
	}

	cout<<"connect with server successful."<<endl;
	
	return sockfd;
}

void on_read(int sockfd, short event, void* arg)
{
	(void*) arg;

	int nRecvCnt = 0;
	char szMsgBuf[MAX_BUFFER_SIZE] = {0};

	if( (nRecvCnt=recv(sockfd, szMsgBuf, MAX_BUFFER_SIZE, 0))<=0 )
	{
		perror("recv");
		return;
	}

	cout<<"[Recv From Server]: "<<szMsgBuf<<endl;

	return;
}

//另一个线程中处理服务器回射数据
void* init_read_event(void* arg)
{
	int sockfd = *((int*)arg);

	//1-初始化libevent,创建event base
	struct event_base* base = event_base_new();

	//2-定义event
	struct event* rd_event = (struct event*)malloc(sizeof(struct event));

	//3-设置event
	event_set(rd_event, sockfd, EV_READ|EV_PERSIST, on_read, NULL);

	//4-设置event_base
	event_base_set(base, rd_event);

	//5-添加event
	event_add(rd_event, NULL);

	//6-执行
	event_base_dispatch(base);

	//---------------------------------------------
	event_del(rd_event);
	free(rd_event);
	event_base_free(base);

	return (void*)NULL;
}

void init_read_base_thread(int sockfd)
{
	pthread_t tid;

	pthread_create(&tid, NULL, init_read_event, (void*)&sockfd);

	pthread_detach(tid);

	return;
}

void on_write(int sockfd)
{
	bool isbreak = false;
	char szMsgBuf[MAX_BUFFER_SIZE] = {0};
	string strMsg;
	
	while( isbreak==false )
	{
		cout<<"input msg you wanna send to server, \"q\" for quit."<<endl;
		cin>>strMsg;
		if( *strMsg.c_str()=='q' )
			break;
		if( send(sockfd, strMsg.c_str(), strMsg.size(), 0)<=0 )
			continue;
		sleep(2);
	}

	return;
}

int main(int argc, char* argv[])
{
	if( argc<3 )
	{
		cout<<"input ip and port."<<endl;
		return -1;
	}

	int sockfd;
	int port = atoi(argv[2]);
	char* ip = argv[1];
	if( (sockfd=on_connect(ip, port))<0 )
		return -1;

	on_write(sockfd);

	close(sockfd);

	return 0;
}

