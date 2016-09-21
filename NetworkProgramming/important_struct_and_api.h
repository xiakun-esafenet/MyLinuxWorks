#ifndef	_IMPORTANT_STRUCT_API_NO_USE_
#define _IMPORTANT_STRUCT_API_NO_USE_

struct sockaddr_in
{
	sa_family_t sin_family; //AF_INET
	u_int16_t sin_port;
	struct in_addr sin_addr;
};

struct in_addr
{
	u_int32_t s_addr; //htonl(INADDR_ANY)
};

struct epoll_event {
  __uint32_t   events;      /* Epoll events */
  epoll_data_t data;        /* User data variable */
};

typedef union epoll_data {
	void        *ptr;
  int          fd;
  __uint32_t   u32;
  __uint64_t   u64;
} epoll_data_t;

typedef enum _events_enum_no_use
{
	EPOLLIN = 0,
	EPOLLOUT,
	EPOLLRDHUP, //since linux 2.6.17
	EPOLLPRI,
	EPOLLERR,
	EPOLLHUP,
	EPOLLET,
	EPOLLONESHOT
}events_enum_no_use;

typedef enum _epoll_op_no_use
{
	EPOLL_CTL_ADD = 0,
	EPOLL_CTL_MOD,
	EPOLL_CTL_DEL
}epll_op_no_use;

struct hostent {
	char  *h_name;            /* official name of host */
  char **h_aliases;         /* alias list */
  int    h_addrtype;        /* host address type */
  int    h_length;          /* length of address */
  char **h_addr_list;       /* list of addresses */
};
#define h_addr h_addr_list[0] /* for backward compatibility */

struct sigaction {
	void     (*sa_handler)(int);
  void     (*sa_sigaction)(int, siginfo_t *, void *);
  sigset_t   sa_mask;
  int        sa_flags;
  void     (*sa_restorer)(void);
};


#include <sys/types.h>          
#include <sys/socket.h>

int socket(int domain, int type, int protocol);

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
   
int listen(int sockfd, int backlog);

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

ssize_t send(int sockfd, const void *buf, size_t len, int flags);

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);

ssize_t recv(int sockfd, void *buf, size_t len, int flags);

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
   
int inet_aton(const char *cp, struct in_addr *inp);

in_addr_t inet_addr(const char *cp);

in_addr_t inet_network(const char *cp);

char *inet_ntoa(struct in_addr in);

struct in_addr inet_makeaddr(int net, int host);

in_addr_t inet_lnaof(struct in_addr in);

in_addr_t inet_netof(struct in_addr in);

#include <netdb.h>
extern int h_errno;

struct hostent *gethostbyname(const char *name);

#include <sys/socket.h>       /* for AF_INET */
struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type);

void herror(const char *s);

#include <sys/epoll.h>

int epoll_create(int size);

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

#include <unistd.h>

unsigned int alarm(unsigned int seconds);

#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);

#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, ... /* arg */ );
//cmd F_GETFL / F_SETFL

#include <pthread.h>
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int pthread_detach(pthread_t thread);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int pthread_attr_getstacksize(pthread_attr_t *attr, size_t *stacksize);
int pthread_join(pthread_t thread, void **retval);
void pthread_exit(void *retval);


#include <string.h>
char *strerror(int errnum);
void perror(const char *s);

#include <strings.h>
void bzero(void *s, size_t n);

#include <arpa/inet.h>
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);

#include <stdlib.h>
void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#include <stdlib.h>
int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);
long long atoq(const char *nptr);

#include <sys/types.h>          
#include <sys/socket.h>
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

#endif

