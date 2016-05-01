#ifndef _NETWORKSERVICE_H
#define _NETWORKSERVICE_H

#include <event2/event.h>
#include <map>

class TCPClient;
class Timer;

class EventDriver {
public:
	EventDriver();
	~EventDriver();

	bool init();
	void release();
	bool start();
	void stop();

	bool add(TCPClient *pClient);
	bool add(Timer *pTimer);
	void del(TCPClient *pClient);
	void del(Timer *pTimer);

	bool send(TCPClient *pClient, const char *buffer, size_t size);
private:
	bool addEvent(TCPClient *pClient);
	bool addEvent(Timer *pTimer);
private:
	struct event_base *m_base;
	bool m_isRun;
};


#endif
