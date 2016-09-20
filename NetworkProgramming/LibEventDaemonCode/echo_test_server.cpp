/************** 服务器回射实例 ***************/
/***	使用libevent编程 				   ***/
/***	服务器端部分		 				   ***/

#include "../myhead.h"

using namespace std;

#define SERV_PORT	(9999)

struct sock_ev
{
	struct event_base* base;
	struct event* ev_read;
};

struct sock_ev_write
{
	struct event* ev_write;
	char* msg_buffer;
};

void destroy_sock_event(struct sock_ev* p_sock_ev)
{
	if( p_sock_ev==NULL )
		return;

	//注意销毁顺序
	//1-删除event事件
	event_del(p_sock_ev->ev_read);

	//2-停止循环
	event_base_loopexit(p_sock_ev->base, NULL);

	//3-指针销毁
	if( p_sock_ev->ev_read!=NULL )
		free(p_sock_ev->ev_read);

	//4-删除event base,因为base指针是调用event_base_new创建的，所以由libevent负责销毁
	event_base_free(p_sock_ev->base);

	//5-删除指针
	free(p_sock_ev);

	return;
}

void destroy_sock_event_write(struct sock_ev_write* p_sock_ev_write)
{
	if( p_sock_ev_write==NULL )
		return;

	//因为写事件没有EV_PERSIST,因此不需要event_del
	//event_del(p_sock_ev_write->ev_write);

	if( p_sock_ev_write->ev_write!=NULL )
		free(p_sock_ev_write->ev_write);

	if( p_sock_ev_write->msg_buffer!=NULL )
		free(p_sock_ev_write->msg_buffer);

	free(p_sock_ev_write);
	
	return;
}

void on_write(int sockfd, short event, void* param)
{
	struct sock_ev_write* ev_write = (struct sock_ev_write*)param;

	int write_cnt = write(sockfd, ev_write->msg_buffer, strlen(ev_write->msg_buffer));

	cout<<"write to client: "<<write_cnt<<" bytes"<<endl;

	destroy_sock_event_write(ev_write);
}

void on_read(int sockfd, short event, void* param)
{
	struct sock_ev* ev_read = (struct sock_ev*)param;

	char* p_buffer = (char*)malloc(MAX_BUFFER_SIZE*sizeof(char));
	int read_cnt;
	if( p_buffer==NULL )
		return;

	memset(p_buffer, 0, MAX_BUFFER_SIZE);
	if( (read_cnt=read(sockfd, p_buffer, MAX_BUFFER_SIZE))<=0 )
	{
		destroy_sock_event(ev_read);
		close(sockfd);
		return;
	}

	struct sock_ev_write* ev_write = (struct sock_ev_write*)malloc(sizeof(struct sock_ev_write));
	ev_write->ev_write = (struct event*)malloc(sizeof(struct event));
	ev_write->msg_buffer = p_buffer;
	
	event_set(ev_write->ev_write, sockfd, EV_WRITE, on_write, (void*)ev_write);
	event_base_set(ev_read->base, ev_write->ev_write);
	event_add(ev_write->ev_write, NULL);

	return;
}

void* process_new_client(void* param)
{
	int conn_fd = *((int*)param);

	struct sock_ev* ev_read = (struct sock_ev*)malloc(sizeof(struct sock_ev));
	struct event_base* base = event_base_new();

	ev_read->base = base;
	ev_read->ev_read = (struct event*)malloc(sizeof(struct event));

	//一般来讲，设置了EV_PERSIST，都需要调用event_base_dispatch
	event_set(ev_read->ev_read, conn_fd, EV_READ|EV_PERSIST, on_read, (void*)ev_read);
	event_base_set(base, ev_read->ev_read);
	event_add(ev_read->ev_read, NULL);

	event_base_dispatch(base);

	cout<<"client quit."<<endl;
	
	return (void*)NULL;
}

void create_client_thread(int conn_fd)
{
	pthread_t tid;

	pthread_create(&tid, NULL, process_new_client, (void*)&conn_fd);

	pthread_detach(tid);

	return;
}

void on_accept(int sockfd, short event, void* param)
{
	int conn_fd;
	struct sockaddr_in client_addr;
	int client_addr_len = 0;

	bzero(&client_addr, sizeof(struct sockaddr_in));
	if( (conn_fd=accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_len))<0 )
	{
		perror("accept");
		close(sockfd);
		return;
	}

	cout<<"new connection, ip: "<<inet_ntoa(client_addr.sin_addr)<<", port: "<<ntohs(client_addr.sin_port)<<endl;
	create_client_thread(conn_fd);

	return;
}

int main(int argc, char* argv[])
{
	struct sockaddr_in local_addr;
	int sockfd;

	if( (sockfd=socket(AF_INET, SOCK_STREAM, 0))<=0 )
	{
		perror("socket");
		return -1;
	}

	bzero(&local_addr, sizeof(struct sockaddr_in));
	if( bind(sockfd, (struct sockaddr*)&local_addr, sizeof(struct sockaddr))<0 )
	{
		perror("bind");
		close(sockfd);
		return -1;
	}

	if( listen(sockfd, 5)<0 )
	{
		perror("bind");
		close(sockfd);
		return -1;
	}

	struct event_base* base = event_base_new();
	struct event* ev_accept = (struct event*)malloc(sizeof(struct event));

	event_set(ev_accept, sockfd, EV_READ|EV_PERSIST, on_accept, (void*)NULL);
	event_base_set(base, ev_accept);
	event_add(ev_accept, NULL);

	event_base_dispatch(base);

	event_del(ev_accept);
	free(ev_accept);
	event_base_free(base);

	return 0;
}
