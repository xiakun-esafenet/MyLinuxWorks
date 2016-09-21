#ifndef	_IMPORTANT_MACRO_DEFINE_NO_USE_
#define _IMPORTANT_MACRO_DEFINE_NO_USE_

//系统相关
typedef	unsigned int pthread_t;

//Signal相关宏定义
#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGILL		 4
#define SIGTRAP		 5
#define SIGABRT		 6
#define SIGIOT		 6
#define SIGBUS		 7
#define SIGFPE		 8
#define SIGKILL		 9
#define SIGUSR1		10
#define SIGSEGV		11
#define SIGUSR2		12
#define SIGPIPE		13
#define SIGALRM		14
#define SIGTERM		15
#define SIGSTKFLT	16
#define SIGCHLD		17
#define SIGCONT		18
#define SIGSTOP		19
#define SIGTSTP		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGURG		23
#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTALRM	26
#define SIGPROF		27
#define SIGWINCH	28
#define SIGIO		29
#define SIGPOLL		SIGIO
/*
#define SIGLOST		29
*/
#define SIGPWR		30
#define SIGSYS		31
#define	SIGUNUSED	31

/* These should not be considered constants from userland.  */
#define SIGRTMIN	32
#define SIGRTMAX	_NSIG


//Socket相关宏定义
#define	INADDR_ANY		((in_addr_t) 0x00000000)
typedef struct sockaddr_in struct sockaddr;

enum __socket_type
{
  SOCK_STREAM = 1,		/* Sequenced, reliable, connection-based
				   byte streams.  */
#define SOCK_STREAM SOCK_STREAM
  SOCK_DGRAM = 2,		/* Connectionless, unreliable datagrams
				   of fixed maximum length.  */
#define SOCK_DGRAM SOCK_DGRAM
  SOCK_RAW = 3,			/* Raw protocol interface.  */
#define SOCK_RAW SOCK_RAW
  SOCK_RDM = 4,			/* Reliably-delivered messages.  */
#define SOCK_RDM SOCK_RDM
  SOCK_SEQPACKET = 5,		/* Sequenced, reliable, connection-based,
				   datagrams of fixed maximum length.  */
#define SOCK_SEQPACKET SOCK_SEQPACKET
  SOCK_DCCP = 6,		/* Datagram Congestion Control Protocol.  */
#define SOCK_DCCP SOCK_DCCP
  SOCK_PACKET = 10,		/* Linux specific way of getting packets
				   at the dev level.  For writing rarp and
				   other similar things on the user level. */
#define SOCK_PACKET SOCK_PACKET

  /* Flags to be ORed into the type parameter of socket and socketpair and
     used for the flags parameter of paccept.  */

  SOCK_CLOEXEC = 02000000,	/* Atomically set close-on-exec flag for the
				   new descriptor(s).  */
#define SOCK_CLOEXEC SOCK_CLOEXEC
  SOCK_NONBLOCK = 04000		/* Atomically mark descriptor(s) as
				   non-blocking.  */
#define SOCK_NONBLOCK SOCK_NONBLOCK
};

#define	PF_LOCAL	1	/* Local to host (pipes and file-domain).  */
#define	PF_UNIX		PF_LOCAL /* POSIX name for PF_LOCAL.  */
#define	PF_INET		2	/* IP protocol family.  */
#define	AF_LOCAL	PF_LOCAL
#define	AF_UNIX		PF_UNIX
#define	AF_INET		PF_INET

#define SOL_RAW		255
#define SOL_DECNET      261
#define SOL_X25         262
#define SOL_PACKET	263
#define SOL_ATM		264	/* ATM layer (cell level).  */
#define SOL_AAL		265	/* ATM Adaption Layer (packet level).  */
#define SOL_IRDA	266

enum
{
	MSG_OOB		= 0x01,	/* Process out-of-band data.  */
	#define MSG_OOB		MSG_OOB
    MSG_PEEK		= 0x02,	/* Peek at incoming messages.  */
};

#define SOL_SOCKET	1

#define SO_DEBUG	1
#define SO_REUSEADDR	2
#define SO_TYPE		3
#define SO_ERROR	4
#define SO_DONTROUTE	5
#define SO_BROADCAST	6
#define SO_SNDBUF	7
#define SO_RCVBUF	8
#define SO_SNDBUFFORCE	32
#define SO_RCVBUFFORCE	33
#define SO_KEEPALIVE	9
#define SO_OOBINLINE	10
#define SO_NO_CHECK	11
#define SO_PRIORITY	12
#define SO_LINGER	13
#define SO_BSDCOMPAT	14
#define SO_REUSEPORT	15

#define SO_PASSCRED	16
#define SO_PEERCRED	17
#define SO_RCVLOWAT	18
#define SO_SNDLOWAT	19
#define SO_RCVTIMEO	20
#define SO_SNDTIMEO	21

/* Security levels - as per NRL IPv6 - don't actually do anything */
#define SO_SECURITY_AUTHENTICATION		22
#define SO_SECURITY_ENCRYPTION_TRANSPORT	23
#define SO_SECURITY_ENCRYPTION_NETWORK		24

#define SO_BINDTODEVICE	25

/* Socket filtering */
#define SO_ATTACH_FILTER	26
#define SO_DETACH_FILTER	27

#define SO_PEERNAME		28
#define SO_TIMESTAMP		29
#define SCM_TIMESTAMP		SO_TIMESTAMP

#define SO_ACCEPTCONN		30

#define SO_PEERSEC		31
#define SO_PASSSEC		34
#define SO_TIMESTAMPNS		35
#define SCM_TIMESTAMPNS		SO_TIMESTAMPNS

#define SO_MARK			36

#define SO_TIMESTAMPING		37
#define SCM_TIMESTAMPING	SO_TIMESTAMPING

#define SO_PROTOCOL		38
#define SO_DOMAIN		39

#define SO_RXQ_OVFL		40

#endif

