#include <sys/signal.h>
#include <event.h>

typedef struct event_base	eb;
void signal_callback(int fd, short event, void* argc)
{
	eb* base = (eb*)argc;
	struct timeval delay = {2,0};

	printf("signal callback function...exit in 2 seconds...\n");
	event_base_loopexit(base, &delay);
}

void timeout_callback(int fd, short event, void* argc)
{
	printf("timeout...\n");
}

int main(int argc, char* argv[])
{
	eb* base = event_init();

	struct event* signal_event = evsignal_new(base, SIGINT, signal_callback, base);
	event_add(signal_event, NULL);

	struct timeval tv = {1,0};
	struct event* timeout_event = evtimer_new(base, timeout_callback, NULL);
	event_add(timeout_event, &tv);

	event_base_dispatch(base);

	event_free(timeout_event);
	event_free(signal_event);
	event_base_free(base);

	return 0;
}
