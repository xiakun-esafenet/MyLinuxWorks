#ifndef _EVENT_DEMULTIPLEXER_H_
#define _EVENT_DEMULTIPLEXER_H_

#include "event_handler.h"

namespace ReactorDaemon
{
	class EventDemultiplexer
	{
	public:
		typedef std::map<handle_t, EventHandler*>	EVENTHANDLERLIST;
		EventDemultiplexer(){}
		virtual ~EventDemultiplexer(){}
		virtual int RequestEvent(event_t evt, handle_t handle) = 0;
		virtual int UnRequestEvent(handle_t handle) = 0;
		virtual int WaitEvents(EVENTHANDLERLIST* pHandlers, int timeout=0, TimeHeaper* event_timer = NULL) = 0;
	private:
	};

	class EpollDemultiplexer : public EventDemultiplexer
	{
	public:
		EpollDemultiplexer();
		~EpollDemultiplexer();
		virtual int RequestEvent(event_t evt, handle_t handle);
		virtual int UnRequestEvent(handle_t handle);
		virtual int WaitEvents(EVENTHANDLERLIST* pHandlers, int timeout=0, TimeHeaper* event_timer = NULL);
	private:
		int m_epoll_fd;
		int m_fd_num;
	};
}
#endif
