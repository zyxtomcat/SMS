#include "EventEngine.h"
#include "Singleton.h"
#include "EventDriver.h"

void EventEngine::run() {
	SINGLETON(EventDriver)->start();
}

void EventEngine::destroy() {
	SINGLETON(EventDriver)->stop();
	SINGLETON(EventDriver)->release();
}
