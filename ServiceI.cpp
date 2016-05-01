#include "ServiceI.h"
#include <Ice/Ice.h>
#include "AdminSessionI.h"
#include "SASSessionI.h"
#include <functions.h>
#include "Singleton.h"
#include "DBAccess.h"

using namespace Ice;

extern "C" {
    
IceBox::Service* create(Ice::CommunicatorPtr communicator) {
    return new ServiceI;
}

}


ServiceI::ServiceI() {
    
}

ServiceI::~ServiceI() {
    
}

void 
ServiceI::start(const std::string& name, const CommunicatorPtr& communicator, const StringSeq& args) {
    // get data file path
    PropertiesPtr properties = communicator->getProperties();
    std::string db_host = trim(properties->getPropertyWithDefault("db_host", "localhost"));
	int db_port = properties->getPropertyAsIntWithDefault("db_port", 3306);
	std::string db_user = trim(properties->getPropertyWithDefault("db_user", "streambank"));
	std::string db_passwd = trim(properties->getPropertyWithDefault("db_passwd", "streambank"));
	std::string db_name = trim(properties->getPropertyWithDefault("db_name", "db_streambank"));
	std::string db_charset = trim(properties->getPropertyWithDefault("db_charset", "utf8"));
	//int log_level = properties->getPropertyAsIntWithDefault()
    int db_maxconcurrency = properties->getPropertyAsIntWithDefault("db_maxconcurrency", 4);

    int order_query_timer_interval = properties->getPropertyAsIntWithDefault("query_interval", 10);

    std::string logpath = trim(properties->getPropertyWithDefault("logpath", "/var/log"));
    logpath += "/";
    logpath += name;
    logpath += ".log";
    if (!log_init(logpath)) {
        throw IceBox::FailureException(__FILE__, __LINE__, "Failed to init log");
    }

    MYLOG_INFO("SMS Application service starts");

	DatabaseInfo dbInfo(db_host, db_port, db_user, db_passwd, db_name, db_charset);

    m_adapter = communicator->createObjectAdapter(name);
    IceUtil::Handle<SASSessionI> sasSessionIPtr = new SASSessionI;
    if (false == sasSessionIPtr->init(dbInfo, db_maxconcurrency)) {
        MYLOG_FATAL("Init SASSessionI failed.");
        throw IceBox::FailureException(__FILE__, __LINE__, "Init SASSessionI failed.");
    }

    MYLOG_INFO("SMS init finished");

    m_adapter->add(sasSessionIPtr, communicator->stringToIdentity("SASSession"));

    IceUtil::Handle<AdminSessionI> adminSessionPtr = new AdminSessionI;
    m_adapter->add(adminSessionPtr, communicator->stringToIdentity("AdminSession"));

    m_adapter->activate();

    m_eventEngine = new EventEngine;
    m_eventEngine->start();
 }

 void 
 ServiceI::stop() {
 	MYLOG_INFO("SMS Application service stop");
    m_eventEngine->destroy();
    m_eventEngine->getThreadControl().join();
 	m_adapter->destroy();
 }
