#include "DataEntitys.h"
#include "PublicFunction.h"
#include "CMPP.h"

ISMGParam::ISMGParam() {

}

ISMGParam::~ISMGParam() {

}


ISMGInfo::ISMGInfo() : server_port(0) {

}

ISMGInfo::~ISMGInfo() {
	Clear();
}

void ISMGInfo::Clear() {
	std::map<std::string, ISMGParam *>::iterator it = m_mapParam.begin();
	for (; it != m_mapParam.end(); ++it) {
		ISMGParam *pParam = it->second;
		if (NULL != pParam) {
			delete pParam;
		}
	}

	m_mapParam.clear();
}

void ISMGInfo::UpdateParam(ISMGParam *pParam) {
	m_mapParam.insert(std::make_pair(pParam->param_key, pParam));
}

std::string ISMGInfo::getISMGParamValue(const std::string &parak_key) {
	std::string str;
	std::map<std::string, ISMGParam *>::iterator it = m_mapParam.find(parak_key);
	if (it != m_mapParam.end()) {
		str = it->second->param_value;
	}

	return str;
}

SMSLog::SMSLog() 
:id(0),
Msg_Id(0),
pk_total(1),
sms_fmt(MSG_FMT_UCS2),
sms_type(false),
create_time(Now()),
update_time(Now()) {

}

void SMSLog::setSeq(U32 u32Seq) {
	vecSeq.push_back(u32Seq);
}

bool SMSLog::check(U32 u32Seq) {

	if (u32Seq > 0) {
		std::vector<U32>::iterator it = vecSeq.begin();
		for (; it != vecSeq.end(); ++it) {
			if (u32Seq == *it) {
				break;
			}
		}

		vecSeq.erase(it);
	}

	return vecSeq.size() == 0;
}