#ifndef _DBSERVICE_H
#define _DBSERVICE_H

#include "DBServiceBase.h"
#include "DataTypeDef.h"

class ISMGInfo;
class ISMGParam;
class CustomerNumSeg;
class SMSLog;

class DBService : public DBServiceBase {
public:
	DBService(const DatabaseInfo& dbInfo, int maxconcurrency);
	virtual ~DBService();

	bool getAllISMGInfo(std::list<ISMGInfo *>& lst);
	bool getAllISMGParam(std::list<ISMGParam *> lst);
	bool getCustomerNumSeg(const std::string &num, CustomerNumSeg& seg);
	U32 addSMSLog(const SMSLog & smsLog);
	bool updateSMSLog(const SMSLog &smsLog);
    bool updateSMSLogAfterSend(const SMSLog &smsLog);
	bool getSMSLog(const std::string &num, const std::string &beginTime, const std::string &endTime, std::list<SMSLog *> lst);

protected:
	DBAccess* getDBAccess();
};
#endif
