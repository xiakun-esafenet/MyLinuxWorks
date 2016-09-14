#include "reactor.h"

namespace ReactorDaemon
{
	Reactor::Reactor()
	{
		m_pReactor = new Reactor;
	}

	Reactor::~Reactor()
	{
		delete m_pReactor;
		m_pReactor = NULL;
	}

	int Reactor::RegisterHandler(event_t evt, EventHandler* pEvtHdr)
	{
		handle_t handle = pEvtHdr->GetHandle();
		
		EVENTHANDLERLIST::iterator iter = m_mapHandlers.find(handle);
		if( iter==m_mapHandlers.end() )
		{
			m_mapHandlers.insert(std::make_pair<handle_t, EventHandler*>(handle, pEvtHdr));
		}

		m_pEvtDemultiplexer->RequestEvent(evt, handle);
	}

	int Reactor::RemoveHandler(EventHandler* pEvtHdr)
	{
		handle_t handle = pEvtHdr->GetHandle();
		
		m_mapHandlers.erase(handle);

		m_pEvtDemultiplexer->UnRequestEvent(handle);
	}

	void Reactor::HandleEvents(void)
	{
		
	}
}
