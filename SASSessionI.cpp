#include "SASSessionI.h"
#include "DataEntitys.h"
#include "DataManager.h"
#include "DBService.h"
#include "ErrorCode.h"
#include <functions.h>
#include <json/json.h>
#include "CMPPAgent.h"
#include "PublicFunction.h"

SASSessionI::SASSessionI() : m_dbService(NULL), m_pIM(NULL) {

}

SASSessionI::~SASSessionI() {

}

bool SASSessionI::init(DatabaseInfo &dbInfo, int db_maxconcurrency) {
	bool result = false;

	do {
		m_dbService = new DBService(dbInfo, db_maxconcurrency);
		if (NULL == m_dbService) break;

		m_pIM = new ISMGManager(m_dbService);
		if (NULL == m_pIM) break;

		if (false == m_pIM->Init()) break;
		
		if (false == initAgent()) break;

		MYLOG_INFO("Init SASSession success");

		result = true;
	} while(0);
	
	if (false == result) {
		if (NULL != m_pIM) {
			m_pIM->Clear();
			delete m_pIM;
			m_pIM = NULL;
		}

		if (NULL != m_dbService) {
			delete m_dbService;
			m_dbService = NULL;
		}

		MYLOG_ERROR("Init SASSession failed");
	}

	return result;
}

bool SASSessionI::initAgent() {
	if (NULL == m_pIM) return false;
	std::list<ISMGInfo *> lst;
	m_pIM->getISMGInfoByProtocol(lst, "CMPP");
	for (std::list<ISMGInfo *>::iterator it = lst.begin(); it != lst.end(); ++it) {
        ISMGInfo *pISMGInfo = *it;
		ISMGAgent *pAgent = new CMPPAgent(*pISMGInfo);
		if (true == pAgent->init()) {
			MYLOG_INFO("init ISMGAgent success.Protocol:%s server_host:%s server_port:%d", pISMGInfo->protocol.c_str(), pISMGInfo->server_host.c_str(), pISMGInfo->server_port);
			m_mapAgent.insert(std::make_pair(pISMGInfo->SP_Id, pAgent));

			EVENT_BIND(pAgent->OnSMSSubmitResp, this, SASSessionI::HandleSMSSubmitResp);
			EVENT_BIND(pAgent->OnSMSStatusReport, this, SASSessionI::HandleSMSStatusReport);
			EVENT_BIND(pAgent->OnSMSDeliver, this, SASSessionI::HandleSMSDeliver);
			EVENT_BIND(pAgent->OnAgentReady, this, SASSessionI::HandleAgentReady);
		} else {
			MYLOG_ERROR("Init ISMGAgent failed. Protocol:%s server_host:%s server_port:%d", pISMGInfo->protocol.c_str(), pISMGInfo->server_host.c_str(), pISMGInfo->server_port);
		}
	}

	return true;
}

ISMGAgent* SASSessionI::getAgent(const std::string &SP_Id) {
	std::map<std::string, ISMGAgent *>::iterator it = m_mapAgent.find(SP_Id);
	if (it != m_mapAgent.end()) {
		return it->second;
	}
}

void SASSessionI::SendSMS( const ::std::string& request, ::std::string& response, const ::Ice::Current& cur) {
	
	int error_code = SAS_SUCCESS;

	SMSLog *pSMSLog = new SMSLog;

	Json::Value root; 
	Json::Reader reader;
	do {
		if (!reader.parse(request, root)) {
			error_code = SAS_BAD_REQUEST_CONTENT;
			MYLOG_ERROR("SASSessionI: SendSMS parse request error. Request[%s]", request.c_str());
			break;
		}

		if (root.empty() 
			|| root["sim"].empty()
			|| root["content"].empty()) {
			error_code = SAS_BAD_REQUEST_CONTENT;
			MYLOG_ERROR("SASSessionI: SendSMS request wrong content. Request[%s]", request.c_str());
			break;
		}

		pSMSLog->Dst_Id = root["sim"].asCString();
		pSMSLog->sms_content = root["content"].asCString();
		pSMSLog->sms_content_hex = BinToHexString(pSMSLog->sms_content);
		pSMSLog->sms_fmt = MSG_FMT_UCS2;
		pSMSLog->sms_type = false;

		CustomerNumSeg seg;
		if (false == m_dbService->getCustomerNumSeg(pSMSLog->Dst_Id, seg)) {
			error_code = SAS_SERVER_INTERNAL_ERROR;
			MYLOG_ERROR("SASSessionI: SendSMS get num seg failed");
			break;
		}

		pSMSLog->SP_Id = seg.SP_Id;
		pSMSLog->Src_Id = seg.Src_id;
		pSMSLog->service_id = seg.service_id;
		pSMSLog->create_time = Now();
		pSMSLog->update_time = Now();

		U32 msg_id = m_dbService->addSMSLog(*pSMSLog);
		if (msg_id == 0) {
			error_code = SAS_SERVER_INTERNAL_ERROR;
			MYLOG_ERROR("SASSessionI: Add SMSLog to Database error.");
			break;
		}

		pSMSLog->id = msg_id;	

		ISMGAgent *pAgent = getAgent(pSMSLog->SP_Id);
		if (NULL == pAgent) {
			error_code = SAS_SERVER_INTERNAL_ERROR;
			MYLOG_ERROR("SASSessionI: Not support sim:[%s]", pSMSLog->Dst_Id.c_str());
			break;
		}

		error_code = pAgent->SendSMS(*pSMSLog);
		
		if (error_code != SAS_SUCCESS) {
			break;
		} else {
			AddSendSMSWaitQueue(pSMSLog);
		}

		//
	} while(0);

	if (SAS_SUCCESS != error_code) {
		delete pSMSLog;
	}

	Json::Value respVal;
	respVal["result"] = error_code;
	respVal["msg"] = getErrorDesc(error_code);

	Json::FastWriter writer;
	response = writer.write(respVal);
}

void SASSessionI::QuerySMS(const ::std::string& request, ::std::string& response, const ::Ice::Current& cur) {

	int error_code = SAS_SUCCESS;

	Json::Value root;
	Json::Reader reader;

	Json::Value respVal;
	do {
		if (!reader.parse(request, root)) {
			error_code = SAS_BAD_REQUEST_CONTENT;
			MYLOG_ERROR("SASSessionI: QuerySMS cannot parse request json.Request[%s]", request.c_str());
			break;
		}

		if (root.empty() 
			|| root["sim"].empty()
			|| root["begin_time"].empty()
			|| root["end_time"].empty()) {
			error_code = SAS_BAD_REQUEST_CONTENT;
			MYLOG_ERROR("SASSessionI: QuerySMS cannot parse request json.Request[%s]", request.c_str());
			break;
		}

		std::string sim = root["sim"].asCString();
		std::string begin_time = root["begin_time"].asCString();
		std::string end_time = root["end_time"].asCString();

		std::list<SMSLog *> lst;
		if (false == m_dbService->getSMSLog(sim, begin_time, end_time, lst)) {
			error_code = SAS_SERVER_INTERNAL_ERROR;
			MYLOG_ERROR("SASSessionI: QuerySMS query smslog from database failed.");
			break;
		}

		Json::Value data;
		Json::Value smsItems;
		for (std::list<SMSLog *>::iterator it = lst.begin(); it != lst.end(); ++it) {
			SMSLog *smsLog = *it;
			if (NULL != smsLog) {
				Json::Value item;
				item["content"] = smsLog->sms_content;
				item["time"] = smsLog->create_time.toString();
				smsItems.append(item);
			}
		}

		if (smsItems.size() > 0) {
			data["sim"] = sim;
			data["sms"] = smsItems;
			respVal["data"] = data;
		}
	} while(0);

	respVal["result"] = error_code;
	respVal["msg"] = getErrorDesc(error_code);
	
	Json::FastWriter writer;
	response = writer.write(respVal);

}

void SASSessionI::HandleSMSSubmitResp(ISMGAgent* pAgent, SMSLog *pSMSLog, int error_code) {
	if (pSMSLog->check()) {
		LockerGuard lockGuard(m_lockerSMSWaitQueue);
		std::map<U32, SMSLog*>::iterator it = m_mapSMSWaitQueue.find(pSMSLog->id);
		if (it != m_mapSMSWaitQueue.end()) {
			//delete pSMSLog;
			m_mapSMSWaitQueue.erase(it);
		}
	} 
}

void SASSessionI::HandleSMSStatusReport(ISMGAgent* pAgent, SMSLog &smsLog) {

}

void SASSessionI::HandleSMSDeliver(ISMGAgent* pAgent, SMSLog &smsLog) {
	U32 msg_id = m_dbService->addSMSLog(smsLog);
	if (msg_id > 0) {
		//push 
	}
}

void SASSessionI::HandleAgentReady(ISMGAgent* pAgent) {

}

void SASSessionI::AddSendSMSWaitQueue(SMSLog *pSMSLog) {
	LockerGuard lockGuard(m_lockerSMSWaitQueue);
	m_mapSMSWaitQueue.insert(std::make_pair(pSMSLog->id, pSMSLog));
}