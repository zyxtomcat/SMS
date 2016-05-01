#include "EventDriver.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <netinet/tcp.h>
#include <string.h>
#include <functions.h>
#include "TCPClient.h"
#include "Timer.h"

static void read_cb(struct bufferevent *bev, void *ctx) {
	TCPClient *pClient = (TCPClient *)ctx;
	if (NULL != pClient) {
		char buffer[4096+1];
		memset(buffer, 0x00, sizeof(buffer));
		struct evbuffer *input = bufferevent_get_input(bev);
		size_t size = evbuffer_remove(input, buffer, sizeof(buffer)-1);
		buffer[size] = '\0';
		pClient->DoRecvData(buffer, size);
	}
}

static void event_cb(struct bufferevent *bev, short what, void *ctx) {
	TCPClient *pClient = (TCPClient *)ctx;
	if (NULL == pClient) return;
	if (what & BEV_EVENT_CONNECTED)	{
		pClient->DoConnect();
	} else if ((what & BEV_EVENT_EOF) || (what & BEV_EVENT_ERROR)) {
		struct bufferevent *ev = (struct bufferevent *)pClient->GetCtx();
		if (NULL != ev) {
			bufferevent_free(ev);
		}

		pClient->SetCtx(NULL);

		pClient->DoDisconnect();
	} 
};

static void timeout_cb(evutil_socket_t fd, short event, void *ctx ) {
	Timer *pTimer = (Timer *)ctx;
	if (NULL == pTimer) return;

	pTimer->DoTimer();

	struct event *evtimer = (struct event *)pTimer->GetCtx();
	U32 time_interval = pTimer->GetInterval();
	struct timeval timeout;
	evutil_timerclear(&timeout);
	timeout.tv_sec = time_interval;
	timeout.tv_usec = 0;
	evtimer_add(evtimer, &timeout);
}

EventDriver::EventDriver() : m_base(NULL) {

}

EventDriver::~EventDriver() {

}

bool EventDriver::init() {
	m_base = event_base_new();
	if (NULL == m_base) {
		MYLOG_ERROR("event_base_new failed");
		return false;
	}

	return true;
}

void EventDriver::release() {

	event_base_free(m_base);

	m_base = NULL;
}

bool EventDriver::start() {
	if (NULL == m_base) {
		return false;
	}

	m_isRun = true;

	while (m_isRun) {
		int result = event_base_dispatch(m_base);
		if (0 != result) {
			MYLOG_ERROR("event_base_dispatch error : %d", result);
			return false;
		}
	}

	return true;
}

void EventDriver::stop() {
	if (NULL == m_base) return;

	m_isRun = false;
	event_base_loopexit(m_base, NULL);
}

bool EventDriver::add(TCPClient *pClient) {
	if (NULL == m_base) {
		return false;
	} else {
		return addEvent(pClient);
	}	
}

bool EventDriver::add(Timer *pTimer) {
	if (NULL == m_base) {
		return false;
	} else {
		return addEvent(pTimer);
	}	
}

void EventDriver::del(Timer *pTimer) {

	if (NULL == pTimer) return;

	struct event *evtimer = (struct event *)pTimer->GetCtx();
	event_del(evtimer);
	pTimer->SetCtx(NULL);
	//event_free(evtimer);
}

void EventDriver::del(TCPClient *pClient) {
	struct bufferevent *ev = (struct bufferevent *)pClient->GetCtx();
	if (NULL != ev) {
		bufferevent_free(ev);
	}

	pClient->SetCtx(NULL);

	pClient->DoDisconnect();
}

bool EventDriver::send(TCPClient *pClient, const char *buffer, size_t size) {
	struct bufferevent *ev = (struct bufferevent *)pClient->GetCtx();
	if (NULL == ev) {
		return false;
	}

	int ret = bufferevent_write(ev, buffer, size);

	return ret == 0;
}


bool EventDriver::addEvent(TCPClient *pClient) {

	struct sockaddr_in sin;
	memset(&sin, 0x00, sizeof(sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(pClient->GetAddr());
	sin.sin_port = htons(pClient->GetPort());

	struct bufferevent *bev = bufferevent_socket_new(m_base, -1, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, read_cb, NULL, event_cb, (void *)pClient);
	bufferevent_enable(bev, EV_READ|EV_WRITE);

	if (bufferevent_socket_connect(bev, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		MYLOG_ERROR("Error connect");
		bufferevent_free(bev);
		return false;
	}

	pClient->SetCtx((void *)bev);

	return true;	
}

bool EventDriver::addEvent(Timer *pTimer) {
	U32 time_interval = pTimer->GetInterval();
	struct timeval timeout;
	evutil_timerclear(&timeout);
	timeout.tv_sec = time_interval;
	timeout.tv_usec = 0;
	struct event *evtimer = evtimer_new(m_base, timeout_cb, (void *)pTimer);
	evtimer_add(evtimer, &timeout);

	pTimer->SetCtx((void *)evtimer);

	return true;
}
