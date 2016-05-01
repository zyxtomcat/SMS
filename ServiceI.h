#ifndef _SERVICEI_H
#define _SERVICEI_H

#include <IceBox/IceBox.h>
#include "EventEngine.h"

class ServiceI : public ::IceBox::Service {
public:
    ServiceI();
    virtual ~ServiceI();
    
    virtual void start(const std::string&, const ::Ice::CommunicatorPtr&, const ::Ice::StringSeq&);
    virtual void stop();  
    
private:
    ::Ice::ObjectAdapterPtr m_adapter;

    IceUtil::Handle<EventEngine> m_eventEngine;
};

#endif
