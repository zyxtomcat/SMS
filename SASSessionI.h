#ifndef _SASSESSIONI_H
#define _SASSESSIONI_H

#include "SAS.h"
#include <IceUtil/IceUtil.h>
#include <string>
#include <map>
#include "Object.h"

class DatabaseInfo;
class DBService;
class ISMGManager;
class ISMGAgent;
class SMSLog;

class SASSessionI : public SAS::SASSession, public Object {
public:
	SASSessionI();
	~SASSessionI();

	bool init(DatabaseInfo &dbInfo, int db_maxconcurrency);
	void release();

	virtual void SendSMS(const ::std::string&, ::std::string&, const ::Ice::Current&);
	virtual void QuerySMS(const ::std::string&, ::std::string&, const ::Ice::Current&);
private:
	bool initAgent();
	ISMGAgent* getAgent(const std::string &SP_Id);

	void HandleSMSSubmitResp(ISMGAgent* pAgent, SMSLog *pSMSLog, int error_code);
	void HandleSMSStatusReport(ISMGAgent* pAgent, SMSLog &smsLog);
	void HandleSMSDeliver(ISMGAgent* pAgent, SMSLog &smsLog);
	void HandleAgentReady(ISMGAgent* pAgent);

	void AddSendSMSWaitQueue(SMSLog *pSMSLog);
private:
	DBService *m_dbService;
	ISMGManager *m_pIM;

	std::map<std::string, ISMGAgent *> m_mapAgent;

	Locker m_lockerSMSWaitQueue;
	std::map<U32, SMSLog*> m_mapSMSWaitQueue;
};

#endif
