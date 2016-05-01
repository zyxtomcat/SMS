#ifndef _EVENTENGINE_H
#define _EVENTENGINE_H

#include <IceUtil/IceUtil.h>

class EventEngine : public IceUtil::Thread {
public:
	virtual void run();
	void destroy();
};

#endif
