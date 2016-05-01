#include "SASSessionI.h"
#include "DataEntitys.h"
#include "DataManager.h"
#include "DBService.h"
#include "ErrorCode.h"
#include <functions.h>
#include <json/json.h>
#include "CMPPAgent.h"

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

		result = true;
	} while(0);
	
	if (false == result) {
		if (NULL != m_pIM) {
			m_pIM->Clear();
			delete m_pIM;
		}

		if (NULL != m_dbService) {
			delete m_dbService;
		}
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
			m_mapAgent.insert(std::make_pair(pISMGInfo->SP_Id, pAgent));

			EVENT_BIND(pAgent->OnSMSSubmitResp, this, SASSessionI::HandleSMSSubmitResp);
			EVENT_BIND(pAgent->OnSMSStatusReport, this, SASSessionI::HandleSMSStatusReport);
			EVENT_BIND(pAgent->OnSMSDeliver, this, SASSessionI::HandleSMSDeliver);
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

void SASSessionI::SendSMS_async(const ::SAS::AMD_SASSession_SendSMSPtr& cb, 
	const ::std::string& request, 
	const ::Ice::Current& cur) {
	
	int error_code = SAS_SUCCESS;

	SMSLog smsLog;

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

		smsLog.Dst_Id = root["sim"].asCString();
		smsLog.sms_content = root["content"].asCString();
		smsLog.sms_fmt = MSG_FMT_UCS2;

		CustomerNumSeg seg;
		if (false == m_dbService->getCustomerNumSeg(smsLog.Dst_Id, seg)) {
			error_code = SAS_SERVER_INTERNAL_ERROR;
			MYLOG_ERROR("SASSessionI: SendSMS get num seg failed");
			break;
		}

		smsLog.SP_Id = seg.SP_Id;
		smsLog.Src_Id = seg.Src_id;


		U32 msg_id = m_dbService->addSMSLog(smsLog);
		if (msg_id == 0) {
			error_code = SAS_SERVER_INTERNAL_ERROR;
			MYLOG_ERROR("SASSessionI: Add SMSLog to Database error.");
			break;
		}

		smsLog.id = msg_id;
		smsLog.create_time = Now();
		smsLog.update_time = Now();

		ISMGAgent *pAgent = getAgent(smsLog.SP_Id);
		if (NULL == pAgent) {
			error_code = SAS_SERVER_INTERNAL_ERROR;
			MYLOG_ERROR("SASSessionI: Not support sim:[%s]", smsLog.Dst_Id.c_str());
			break;
		}

		error_code = pAgent->SendSMS(smsLog);
		
		if (error_code != SAS_SUCCESS) break;

		//
	} while(0);

	if (error_code != SAS_SUCCESS) {
		Json::Value respVal;
		respVal["result"] = error_code;
		respVal["msg"] = getErrorDesc(error_code);

		Json::FastWriter writer;
		std::string response = writer.write(respVal);

		cb->ice_response(response);
	}
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

void SASSessionI::HandleSMSSubmitResp() {

}

void SASSessionI::HandleSMSStatusReport() {

}

void SASSessionI::HandleSMSDeliver() {

}

