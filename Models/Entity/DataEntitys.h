#ifndef _DATAENTITYS_H
#define _DATAENTITYS_H

#include "DataTypeDef.h"
#include "PublicFunction.h"

class ISMGParam {
public:
	ISMGParam();
	~ISMGParam();

	std::string SP_Id;
	std::string param_key;
	std::string param_value;
};

class ISMGInfo {
public:
	ISMGInfo();
	~ISMGInfo();

	void Clear();
	void UpdateParam(ISMGParam *pParam);
	std::string getISMGParamValue(const std::string &parak_key);

	U32 id;
	std::string SP_Id;
	std::string server_host;
	U16 server_port;
	std::string protocol;

	std::map<std::string, ISMGParam*> m_mapParam;
};

class CustomerNumSeg {
public:
	U32 id;
	std::string Src_id;
	std::string SP_Id;
	std::string begin_num;
	std::string end_num;
	U32 sum;
	U32 customer_id;
	Datetime create_time;
	Datetime update_time;
};

class SMSLog {
public:
	SMSLog();
	U32 id;
	U64 Msg_Id;
	std::string SP_Id;
	std::string Src_Id;
	std::string Dst_Id;
	std::string sms_content;
	U8 pk_total;
	U8 sms_fmt;
	bool sms_type;
	std::string report_state;
    Datetime done_time;
	Datetime report_time;
	Datetime create_time;
	Datetime update_time;
};

#endif
