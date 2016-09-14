#include "event_demultiplexer.h"

namespace ReactorDaemon
{
	EpollDemultiplexer::EpollDemultiplexer()
	{
		m_epoll_fd = epoll_create(256);
		m_fd_num = 0;
	}

	EpollDemultiplexer::~EpollDemultiplexer()
	{
		close(m_epoll_fd);
		m_fd_num = 0;
	}

	int EpollDemultiplexer::RequestEvent(event_t evt, handle_t handle)
	{
		int nRet = 0;
		struct epoll_event ev;
		ev.data.fd = handle;
		ev.events = 0;
		
		if( evt & REACTOR_EVENT_READ )
			ev.events |= EPOLLIN;
		else if( evt & REACTOR_EVENT_WRITE )
			ev.events |= EPOLLOUT;
		ev.events |= EPOLLONESHOT;
		
		if( (nRet=epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handle, &ev))!=0 )
		{
			if( nRet==ENOENT )
				epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handle, &ev);
			else
				return -1;
		}
		m_fd_num++;

		return 0;
	}

	int EpollDemultiplexer::UnRequestEvent(handle_t handle)
	{
		struct epoll_event ev;
		ev.data.fd = handle;

		epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handle, &ev);
		m_fd_num--;

		return 0;
	}

	void EpollDemultiplexer::WaitEvents(EVENTHANDLERLIST * pHandlers,int timeout,TimeHeaper * event_timer)
	{
	
	}
	
}
