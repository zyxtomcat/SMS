#ifndef _ADMINSESSIONI_H
#define _ADMINSESSIONI_H

#include <ServiceAdmin.h>
#include <IceUtil/IceUtil.h>

class AdminSessionI : public ServiceAdmin::AdminSession
{
public:
    virtual Ice::Int getStatusInfo(std::string &info, const ::Ice::Current&);
};

#endif
