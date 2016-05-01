#ifndef _CMPPAGENT_H
#define _CMPPAGENT_H

#include "CMPP.h"
#include "TCPClient.h"
#include "Timer.h"
#include "ISMGAgent.h"
#include "locker.h"

class DBService;
class PreDecoderInfo;
class CMPPAgent;

class RespTimeoutTimer : public Timer {
public:
	RespTimeoutTimer(U32 u32Seq) : m_u32Seq(u32Seq) {}

	U32 getSeq() { return m_u32Seq; }

	U32 m_u32Seq;
};

class RespCheckItem {
public:
	RespCheckItem(CMPPAgent *pAgent, CMPP *pPkg, U32 seq);
	~RespCheckItem();

	U32 u32Seq;
	U32 u32RestransTimes;
    CMPP *pCMPP;
	RespTimeoutTimer respTimeoutTimer;
};

class CMPPAgent : public ISMGAgent {
public:
	CMPPAgent(const ISMGInfo& info);
	virtual ~CMPPAgent();

	int SendSMS(SMSLog& smslog);

	bool init();

	void OnRespTimeout(RespTimeoutTimer *pTimer);
protected:
	void OnRecvData(TCPClient *pClient, const char *pBuffer, size_t size);
	void OnTCPConnect(TCPClient *pClient);
	void OnTCPDisConnect(TCPClient *pClient);
	void OnTCPError(TCPClient *pClient, int nErrorCode);

	bool HandleNormalData(PreDecoderInfo& pdi);

private:
	template<typename TypeList>
    friend struct DeleteHandleCMPP;

	template<typename T> void Handle(T *pCMPP);
	//template<> void Handle(CMPPConnectResp *pCMPP);
	//template<> void Handle(CMPPTerminateResp *pCMPP);
	//template<> void Handle(CMPPSubmitResp *pCMPP);
	//template<> void Handle(CMPPQueryResp *pCMPP);
	//template<> void Handle(CMPPDeliver *pCMPP);
	//template<> void Handle(CMPPCancelResp *pCMPP);
	//template<> void Handle(CMPPActiveTestResp *pCMPP);

	void PostCMPPData(CMPP& sendCMPP);

	bool SendCMPPData(CMPP& sendCMPP);

	U32 GetSeq();

	void Login();

	void OnConntionActice();


	void CheckResponse(CMPP *pCMPP);

	void ClearCheckAndSendBuffer();

private:
	static bool m_isCMPPRegistr;

	TCPClient m_tcpClient;
	std::string m_strBuffer;

	Timer m_timerConnectActive;

	bool m_isLogin;
	std::string m_authSource;

	Locker m_lockerSeq;
	U32 m_seq;

	//Locker m_lockerMsgSeq;
	//U16 m_msgSeq;

	Locker m_lockerNotSend;
	std::list<CMPP*> m_NotSendQueue;

	Locker m_lockerCheckResp;
	std::map<U32, RespCheckItem*> m_mapCheckResp;
};

#endif
