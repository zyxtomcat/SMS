#ifndef _ISMGAGENT_H
#define _ISMGAGENT_H

#include "Event.h"
#include "DataEntitys.h"

class ISMGAgent;

typedef EventDef<void(ISMGAgent* pAgent, SMSLog *pSMSLog, int error_code)> EventOnSMSSubmitResp;
typedef EventDef<void(ISMGAgent* pAgent, SMSLog &smsLog)> EventOnSMSStatusReport;
typedef EventDef<void(ISMGAgent* pAgent, SMSLog &smsLog)> EventOnSMSDeliver;
typedef EventDef<void(ISMGAgent* pAgent)> EvnetOnAgentReady;

class ISMGAgent : public Object {
public:
	ISMGAgent(const ISMGInfo& info) : m_ISMGInfo(info) {}
	virtual ~ISMGAgent() {}

	virtual bool init() = 0;
	virtual int SendSMS(SMSLog& smslog) = 0;

	EventOnSMSSubmitResp OnSMSSubmitResp;
	EventOnSMSStatusReport OnSMSStatusReport;
	EventOnSMSDeliver OnSMSDeliver;
	EvnetOnAgentReady OnAgentReady;
protected:
	ISMGInfo m_ISMGInfo;
};

#endif
