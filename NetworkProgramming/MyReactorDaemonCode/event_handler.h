#ifndef	_EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include <sys/epoll.h>
#include <unistd.h>
#include <map>

namespace ReactorDaemon
{
//定义Event事件(也称作Handle)
	typedef enum _REACTOR_EVENT
	{
		REACTOR_EVENT_READ = 0,
		REACTOR_EVENT_WRITE,
		REACTOR_EVENT_ERROR,
		REACTOR_EVENT_UNKNOWN
	}REACTOR_EVENT;

	typedef unsigned int event_t;
	typedef int handle_t;

	class EventHandler
	{
	public:
		virtual handle_t GetHandle() const = 0;
		virtual void HandleEvent(event_t event){}
	protected:
		EventHandler(){}
		virtual ~EventHandler(){}
	};
}

#endif

