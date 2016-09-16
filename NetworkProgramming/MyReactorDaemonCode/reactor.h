#ifndef _REACTOR_DAEMON_H_
#define _REACTOR_DAEMON_H_

#include "../AppCommon/singleton.h"
#include "../AppCommon/time_heap.h"
#include "event_handler.h"
#include "event_demultiplexer.h"

namespace ReactorDaemon
{
	class Reactor
	{
	public:
		Reactor();
		~Reactor();
		int RegisterHandler(event_t evt, EventHandler* pEvtHdr);
		int RemoveHandler(EventHandler* pEvtHdr);
		void HandleEvents(void);
		int RegisterTimeTask(TimeHeaper* timerevent);
	private:
		typedef std::map<handle_t, EventHandler*>	EVENTHANDLERLIST;
		Reactor* m_pReactor;
		EventDemultiplexer* m_pEvtDemultiplexer;
		EVENTHANDLERLIST m_mapHandlers;
		TimeHeap* m_pEventTimer;
	};
}

#endif