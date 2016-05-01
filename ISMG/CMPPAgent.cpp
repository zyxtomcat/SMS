#include "CMPPAgent.h"
#include "DataEntitys.h"
#include "DataManager.h"
#include "DBService.h"
#include "CMPP_Register.h"
#include "ErrorCode.h"
#include "SerialDecoder.h"

static bool CMPPAgent::m_isCMPPRegistr = false;

const U8 HEARTBEAT_ACTIVED_CHECK_INTERVAL = 3 * 60; 	//Heartbeat active check interval
const U8 RESPONSE_TIMEOUT = 60;							//Response timeout
const U8 MAX_RETRANS_TIMES = 3;								//Retransmission times
const U8 CMPP_SLIP_WINDOW_SIZE = 16;					//CMPP slip window size


RespCheckItem::RespCheckItem(CMPPAgent *pAgent, CMPP *pPkg, U32 seq) 
:u32Seq(seq),
u32RestransTimes(0), 
pCMPP(pPkg), 
respTimeoutTimer(seq) 
{
    //response
	EVENT_BIND(respTimeoutTimer.OnTimer, pAgent, CMPPAgent::OnRespTimeout);
	respTimeoutTimer.Start();
}

RespCheckItem::~RespCheckItem() {
	respTimeoutTimer.Stop();
}

template<typename TypeList>
struct DeleteHandleCMPP {
	static void Do(CMPPAgent *pAgent, U32 u32Key, CMPP *pCMPP) {
		if (TypeList::Head::ClassKey == u32Key) {
			pAgent->Handle<typename TypeList::Head>((typename TypeList::Head *)pCMPP);
		} else {
			DeleteHandleCMPP<typename TypeList::Tail>::Do(pAgent, u32Key, pCMPP);
		}
	}
};

template<>
struct DeleteHandleCMPP<NullType> {
	static void Do(CMPPAgent *pAgent, U32 u32Key, CMPP *pCMPP) {
		pAgent->Handle<CMPP>(pCMPP);
	}
};

CMPPAgent::CMPPAgent(const ISMGInfo& info) : ISMGAgent(info), m_isLogin(false), m_seq(1) {

}

CMPPAgent::~CMPPAgent() {

}

int CMPPAgent::SendSMS(SMSLog& smslog) {
	if (false == m_isLogin) {
		return SAS_CMPP_NOT_LOGIN;
	}

	std::string sms_content = smslog.sms_content;
	U32 max_msg_len = smslog.sms_fmt == MSG_FMT_ASCII ? MAX_MSG_LEN_ASCII_FMT : MAX_MSG_LEN_OTHER_FMT;
	U32 pk_total = sms_content.size()/max_msg_len + sms_content.size()%max_msg_len ? 1 : 0;

	smslog.pk_total = pk_total;

	for (U32 i = 0; i < pk_total; ++i) {
		CMPPSubmit *submit = new CMPPSubmit;

		submit->setSeq(GetSeq());
		submit->pk_total = pk_total;
		submit->pk_number = i + 1;
		submit->registered_delivery = 1;
		submit->msg_fmt = smslog.sms_fmt;
		memcpy(submit->msg_src, smslog.SP_Id.c_str(), sizeof(submit->msg_src));
		memcpy(submit->src_id, smslog.Src_Id.c_str(), sizeof(submit->src_id));
		TERMINAL_ID dst_id;
        memset(&dst_id, 0x00, sizeof(dst_id));
		memcpy((void *)dst_id.id, smslog.Dst_Id.c_str(), sizeof(dst_id));
		submit->vecDestTermianlId.push_back(dst_id);
		submit->msg_content.assign(smslog.sms_content, i*max_msg_len, ((i == pk_total -1) ? (sms_content.size() - i*max_msg_len) : max_msg_len));

		PostCMPPData(*submit);
	}

	return SAS_SUCCESS;
}

bool CMPPAgent::init() {
	if (false == m_isCMPPRegistr) {
		RegisterCMPP();
		m_isCMPPRegistr = true;
	}
	

	EVENT_BIND(m_tcpClient.OnTCPRecvData, this, CMPPAgent::OnRecvData);
	EVENT_BIND(m_tcpClient.OnTCPConnect, this, CMPPAgent::OnTCPConnect);
	EVENT_BIND(m_tcpClient.OnTCPDisconnect, this, CMPPAgent::OnTCPDisConnect);
	EVENT_BIND(m_tcpClient.OnTCPError, this, CMPPAgent::OnTCPError);

	m_tcpClient.SetAddrPort(m_ISMGInfo.server_host.c_str(), m_ISMGInfo.server_port);
	if (false == m_tcpClient.Open()) {
		MYLOG_ERROR("Init CMPPAgent failed. server_port:%s server_port:%d, SP_Id:%s", m_ISMGInfo.server_host.c_str(), m_ISMGInfo.server_port, m_ISMGInfo.SP_Id.c_str());
		return false;
	}

	EVENT_BIND(m_timerConnectActive.OnTimer, this, CMPPAgent::OnConntionActice);

	return true;
}

void CMPPAgent::OnRecvData(TCPClient *pClient, const char *pBuffer, size_t size) {
	if (pClient != &m_tcpClient || size <= 0) return;

	m_strBuffer.append(pBuffer, size);

	std::string strTempData;
	std::list<PreDecoderInfo> lst;

	SerialDecoder<CMPP>::PreDecode(m_strBuffer.c_str(), m_strBuffer.size(), lst);
	for (std::list<PreDecoderInfo>::iterator it = lst.begin(); it != lst.end(); ++it) {
		PreDecoderInfo& decoderInfo = *it;
		switch (decoderInfo.drCode) {
		case DR_SUCCESS:
			if (HandleNormalData(decoderInfo)) {

			}
			break;
		case DR_KEY_NOT_REGISTER:
			MYLOG_ERROR("CMPP protocol class not register");
			break;
		case DR_BAD_DATA:
			MYLOG_ERROR("Error CMPP data");
			break;
		case DR_UNCOMPLETE:
			strTempData.assign(decoderInfo.pData, decoderInfo.ulLen);
			break;
		default:
			break;
		}
	}

	m_strBuffer = strTempData;
}

void CMPPAgent::OnTCPConnect(TCPClient *pClient) {
	if (pClient != &m_tcpClient) return;

	MYLOG_INFO("CMPPAgent connect to server. server_host:%s, server_port:%d, SP_Id:%s", m_ISMGInfo.server_host.c_str(), m_ISMGInfo.server_port, m_ISMGInfo.SP_Id.c_str());

	if (false == m_isLogin) Login();
}

void CMPPAgent::OnTCPDisConnect(TCPClient *pClient) {
	if (pClient != &m_tcpClient) return;

	MYLOG_INFO("CMPPAgent disconnect to server. server_host:%s, server_port:%d, SP_Id:%s", m_ISMGInfo.server_host.c_str(), m_ISMGInfo.server_port, m_ISMGInfo.SP_Id.c_str());
	m_timerConnectActive.Stop();
	m_isLogin = false;
	m_tcpClient.Open();
}

void CMPPAgent::OnTCPError(TCPClient *pClient, int nErrorCode) {
	if (pClient != &m_tcpClient) return;
}

bool CMPPAgent::HandleNormalData(PreDecoderInfo& pdi) {
	CMPP *pCMPP = SerialDecoder<CMPP>::DecodeClass(pdi.pData, pdi.ulLen, pdi.usKey);
	if (NULL != pCMPP) {
		DeleteHandleCMPP<_CMPP>::Do(this, pCMPP->GetKey(), pCMPP);
		CheckResponse(pCMPP);
	}
}

U32 CMPPAgent::GetSeq() {
	U32 seq = 0;
	LockerGuard lockGuard(m_lockerSeq);
	seq = m_seq;
	++m_seq;
	return seq;
}


void CMPPAgent::Login() {
	CMPPConnect *login = new CMPPConnect;

	login->setSeq(GetSeq());
	std::string src_addr = m_ISMGInfo.getISMGParamValue("SP_Id");
	strncpy(login->source_addr, src_addr.c_str(), sizeof(login->source_addr));

	std::string authSource = src_addr;
	authSource += "000000000";
	authSource += m_ISMGInfo.getISMGParamValue("shared_secret");
	authSource += GetTimestampNoYear();
	std::string md5 = MakeMD5(authSource);
	strncpy(login->authenticatorSource, md5.c_str(), sizeof(login->authenticatorSource));
	m_authSource = md5;

	//login->version = m_ISMGInfo.getISMGParamValue("Version");

	PostCMPPData(*login);
}


void CMPPAgent::OnConntionActice() {
	CMPPActiveTest *aciveTest = new CMPPActiveTest;

	aciveTest->setSeq(GetSeq());
	PostCMPPData(*aciveTest);
}

void CMPPAgent::CheckResponse(CMPP *pCMPPResponse) {
	U32 u32Seq = pCMPPResponse->getSeq();
	{
		std::map<U32, RespCheckItem*>::iterator it;
		LockerGuard lockGuard(m_lockerCheckResp);
		it = m_mapCheckResp.find(u32Seq);
		if (it != m_mapCheckResp.end()) {
			CMPP *pCMPP = it->second->pCMPP;
			if (pCMPP) {
				m_mapCheckResp.erase(it);
				delete pCMPP;
				delete it->second;
			}
		}
	}
}

void CMPPAgent::OnRespTimeout(RespTimeoutTimer *pTimer) {
	U32 u32Seq = pTimer->getSeq();
	{
		std::map<U32, RespCheckItem*>::iterator it;
		LockerGuard lockGuard(m_lockerCheckResp);
		it = m_mapCheckResp.find(u32Seq);
		if (it != m_mapCheckResp.end()) {
			CMPP *pCMPP = it->second->pCMPP;
			if (pCMPP) {
				if (it->second->u32RestransTimes >= MAX_RETRANS_TIMES -1 ) {
					MYLOG_ERROR("CMPP: key=%d seq=%d package response timeout and restrans failed", pCMPP->GetKey(), pCMPP->getSeq());
					m_mapCheckResp.erase(it);
					delete pCMPP;
					delete it->second;
				} else {
					SendCMPPData(*pCMPP);
					++it->second->u32RestransTimes;
					MYLOG_INFO("CMPP: key=%d seq=%d package restrans in %d times", pCMPP->GetKey(), pCMPP->getSeq(), it->second->u32RestransTimes);
				}
			}
			
		}
	}
}

void CMPPAgent::PostCMPPData(CMPP& sendCMPP) {
	{
		LockerGuard lockGuard(m_lockerCheckResp);
		if (m_mapCheckResp.size() < CMPP_SLIP_WINDOW_SIZE) {
			if (true == SendCMPPData(sendCMPP)) {
				RespCheckItem *pItem = new RespCheckItem(this, &sendCMPP, sendCMPP.getSeq());
				m_mapCheckResp.insert(std::make_pair(sendCMPP.getSeq(), pItem));
				return;
			}
		}
	}

	{
		LockerGuard lockGuard(m_lockerNotSend);
		m_NotSendQueue.push_back(&sendCMPP);
	}
}

bool CMPPAgent::SendCMPPData(CMPP& sendCMPP) {
	U32 u32Size = 0;
	char *pBuffer = sendCMPP.EncodeWithoutBuf(u32Size);
	if (NULL != pBuffer && u32Size > 0) {
		return m_tcpClient.SendData(pBuffer, u32Size);
	}

	return false;
}

template<typename T>
void CMPPAgent::Handle(T *pCMPP) {
	MYLOG_ERROR("CMPP Key=%d doesn't handle", pCMPP->GetKey());
}


template<>
void CMPPAgent::Handle(CMPPConnectResp *pCMPP) {
	if (pCMPP->status == 0) {
		std::string authISMG = format("%d%s%s", pCMPP->status, m_authSource.c_str(), m_ISMGInfo.getISMGParamValue("shared_secret").c_str());
		std::string md5 = MakeMD5(authISMG);
		if (strncmp(md5.c_str(), pCMPP->authISMG, 16) == 0) {
			MYLOG_INFO("CMPP connect resp authISMG check success");
			m_isLogin = true;
		} else {
			MYLOG_ERROR("CMPP connect resp authISMG check failed");
			m_tcpClient.Close();
		}
	}
}

template<>
void CMPPAgent::Handle(CMPPTerminateResp *pCMPP) {

}

template<>
void CMPPAgent::Handle(CMPPSubmitResp *pCMPP) {

}

template<>
void CMPPAgent::Handle(CMPPQueryResp *pCMPP) {

}

template<>
void CMPPAgent::Handle(CMPPDeliver *pCMPP) {
	SMSLog smsLog;

	if (pCMPP->registered_delivery == 0) {
		smsLog.Msg_Id = pCMPP->msg_id;
		smsLog.Src_Id = pCMPP->dest_id;
		smsLog.sms_fmt = pCMPP->msg_fmt;
		smsLog.Dst_Id = pCMPP->src_terminal_id;
		smsLog.sms_content = pCMPP->msg_content;
		smsLog.create_time = Now();
		smsLog.update_time = Now();
	} else {
		CMPPStatusReport statusReport;
		unsigned long ulLen = pCMPP->msg_content.size();
		if (true == statusReport.Decode(pCMPP->msg_content.c_str(), ulLen) 
			&& ulLen < pCMPP->msg_content.size()) {
			smsLog.Msg_Id= statusReport.msg_id;
			smsLog.report_state = statusReport.stat;
			smsLog.report_time = Now();
			smsLog.done_time.parse(statusReport.done_time);
			smsLog.Dst_Id = statusReport.dest_terminal_id;
			smsLog.update_time = Now();
		}

	}
}

template<>
void CMPPAgent::Handle(CMPPCancelResp *pCMPP) {

}

template<>
void CMPPAgent::Handle(CMPPActiveTestResp *pCMPP) {

}

