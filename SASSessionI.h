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

class SASSessionI : public SAS::SASSession, public Object {
public:
	SASSessionI();
	~SASSessionI();

	bool init(DatabaseInfo &dbInfo, int db_maxconcurrency);
	void release();

	virtual void SendSMS_async(const ::SAS::AMD_SASSession_SendSMSPtr&, const ::std::string&, const ::Ice::Current&);
	virtual void QuerySMS(const ::std::string&, ::std::string&, const ::Ice::Current&);
private:
	bool initAgent();
	ISMGAgent* getAgent(const std::string &SP_Id);

	void HandleSMSSubmitResp(ISMGAgent* pAgent);
	void HandleSMSStatusReport(ISMGAgent* pAgent);
	void HandleSMSDeliver(ISMGAgent* pAgent);
private:
	DBService *m_dbService;
	ISMGManager *m_pIM;

	std::map<std::string, ISMGAgent *> m_mapAgent;
};

#endif
