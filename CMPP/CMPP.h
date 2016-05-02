#ifndef _CMPP_H
#define _CMPP_H

#include "Serial.h"

const U32 CMPP_RESP_MASK = 0x80000000;

const U32 CMPP_CONNECT = 0x00000001;
const U32 CMPP_CONNECT_RESP = CMPP_CONNECT + CMPP_RESP_MASK;
const U32 CMPP_TERMINATE = 0x00000002;
const U32 CMPP_TERMINATE_RESP = CMPP_TERMINATE + CMPP_RESP_MASK;
const U32 CMPP_SUBMIT = 0x00000004;
const U32 CMPP_SUBMIT_RESP = CMPP_SUBMIT + CMPP_RESP_MASK;
const U32 CMPP_DELIVER = 0x00000005;
const U32 CMPP_DELIVER_RESP = CMPP_DELIVER + CMPP_RESP_MASK;
const U32 CMPP_QUERY = 0x00000006;
const U32 CMPP_QUERY_RESP = CMPP_QUERY + CMPP_RESP_MASK;
const U32 CMPP_CANCEL = 0x00000007;
const U32 CMPP_CANCEL_RESP = CMPP_CANCEL + CMPP_RESP_MASK;
const U32 CMPP_ACTIVE_TEST = 0x00000008;
const U32 CMPP_ACTIVE_TEST_RESP = CMPP_ACTIVE_TEST + CMPP_RESP_MASK;



const U8 MSG_FMT_ASCII = 0;
const U8 MSG_FMT_WRITE_CARD = 3;
const U8 MSG_FMT_BIN = 4;
const U8 MSG_FMT_UCS2 = 8;
const U8 MSG_FMT_GB = 15;

const U8 MAX_MSG_LEN_ASCII_FMT = 160;
const U8 MAX_MSG_LEN_OTHER_FMT = 140;


struct CMPPHeader {
	U32 total_length;
	U32 command_id;
	U32 sequence_id;
};

union Msg_id {
	struct _msg_id_st
	{
		U64 serial 		: 16; 
		U64 SMG_code 	: 22;
		U64 sec 		: 6;
		U64 min 		: 6;
		U64 hour 		: 5;
		U64 day 		: 5;
		U64 month 		: 4;
	} st;
	U64 msg_id;	
};

struct Version {
	U8 minVer : 4;
	U8 maxVer : 4;
};

typedef char ADDR[6];
typedef U8 MD5[16];
typedef char SERVICE_ID[10];
//typedef char TERMINAL_ID[32];
struct TERMINAL_ID {
    char id[32];
};


class CMPP : public Serial {
public:
	CMPP();
	virtual ~CMPP();
	CMPP(const CMPP& src);
	CMPP& operator=(const CMPP& src);

	static unsigned int CheckData(const char* pData, unsigned int ulLen, int& nUsed);
	static const unsigned int MIN_SERIAL_LENGTH = sizeof(CMPPHeader);

	void setSeq(U32 seq);
	U32 getSeq();

	void setCtx(void *ctx);
	void* getCtx();
private:
	U32 seq;
protected:
    virtual char* BeforeSerial(char* pData);
    virtual char* AfterSerial(char* pData);
    virtual char* BeforeUnserial(char* pData);
    virtual char* AfterUnserial(char* pData);
    virtual unsigned int DoSerialSize();

private:
    char* m_pDecodeContent;
    unsigned int m_ulDecodeSize;
    void * m_context;
};

class CMPPConnect : public CMPP {
public:
	BEGIN_SERIAL(CMPPConnect, CMPP, CMPP_CONNECT, "SP connect request");
	SERIAL_ARRAY(char, source_addr, 6, "SP_Id");
	SERIAL_ARRAY(char, authenticatorSource, 16, "MD5(SP_Id+0*9+shard_secret_timestamp)");
	SERIAL_ITEM(Version, version, "Version");
	SERIAL_ITEM(U32, timestamp, "timestamp");
	END_SERIAL();
};

class CMPPConnectResp : public CMPP {
public:
	BEGIN_SERIAL(CMPPConnectResp, CMPP, CMPP_CONNECT_RESP, "SP connect request response");
	SERIAL_ITEM(U32, status, "status");
	SERIAL_ARRAY(char, authISMG, 16, "ISMG");
	SERIAL_ITEM(Version, version, "version");
	END_SERIAL();
};

class CMPPTerminate : public CMPP {
public:
	BEGIN_SERIAL(CMPPTerminate, CMPP, CMPP_TERMINATE, "Connect terminater request");
	END_SERIAL();
};

class CMPPTerminateResp : public CMPP {
public:
	BEGIN_SERIAL(CMPPTerminateResp, CMPP, CMPP_TERMINATE_RESP, "Connect terminater request response");
	END_SERIAL();
};

class CMPPSubmit : public CMPP {
public:
	CMPPSubmit();
	~CMPPSubmit() {}

	BEGIN_SERIAL(CMPPSubmit, CMPP, CMPP_SUBMIT, "SMS submit");
	SERIAL_ITEM(U64, msg_id, "msg id");
	SERIAL_ITEM(U8, pk_total, "total count of same msg id SMS");
	SERIAL_ITEM(U8, pk_number, "seq if same msg id SMS");
	SERIAL_ITEM(U8, registered_delivery, "Request return status confirmation report: 0-yes 1-no");
	SERIAL_ITEM(U8, msg_level, "msg level");
	SERIAL_ARRAY(char, service_id, 10, "service id");
	SERIAL_ITEM(U8, fee_usertype, "charge use type");
	SERIAL_ARRAY(char, fee_terminal_id, 32, "charge user terminal id");
	SERIAL_ITEM(U8, fee_terminal_type, "charge user num type");
	SERIAL_ITEM(U8, tp_pid, "GSM protocol type");
	SERIAL_ITEM(U8, tp_udhi, "GSM protocol type");
	SERIAL_ITEM(U8, msg_fmt, "SMS content format");
	SERIAL_ARRAY(char, msg_src, 6, "SP_Id");
	SERIAL_ARRAY(char, fee_type, 2, "fee type");
	SERIAL_ARRAY(char, fee_code, 6, "fee code");
	SERIAL_ARRAY(char, valid_time, 17, "valid time");
	SERIAL_ARRAY(char, at_time, 17, "timer send time");
	SERIAL_ARRAY(char, src_id, 21, "src id");
	SERIAL_ITEM_EX(vector<TERMINAL_ID>, vecDestTermianlId, U8, "recv SMS ids");
	SERIAL_ITEM(U8, dest_terminal_type, "type if recv terminal type");
	SERIAL_ITEM_EX(string, msg_content, U8, "content of SMS");
	SERIAL_ARRAY(char, link_id, 20, "Link id");
	END_SERIAL();
};

class CMPPSubmitResp : public CMPP {
public:
	BEGIN_SERIAL(CMPPSubmitResp, CMPP, CMPP_SUBMIT_RESP, "SMS submit response");
	SERIAL_ITEM(U64, msg_id, "msg id");
	SERIAL_ITEM(U32, result, "submit result");
	END_SERIAL();
};

class CMPPQuery : public CMPP {
public:
	BEGIN_SERIAL(CMPPQuery, CMPP, CMPP_QUERY, "SMS send status query");
	SERIAL_ARRAY(char, time, 8, "YYYYMMDD");
	SERIAL_ITEM(U8, query_type, "0-total, 2-business type");
	SERIAL_ARRAY(char, query_code, 10, "query code");
	SERIAL_ARRAY(char, reserve, 8, "reserve word");
	END_SERIAL();
};

class CMPPQueryResp : public CMPP {
public:
	BEGIN_SERIAL(CMPPQueryResp, CMPP, CMPP_QUERY_RESP, "SMS send status query request response");
	SERIAL_ARRAY(char, time, 8, "YYYYMMDD");
	SERIAL_ITEM(U8, query_type, "query type");
	SERIAL_ARRAY(char, query_code, 10, "query code");
	SERIAL_ITEM(U32, mt_tlmsg, "SMS count of recv from SP");
	SERIAL_ITEM(U32, mt_tlusr, "User count of recv from SP");
	SERIAL_ITEM(U32, mt_scs, "count of transmit success");
	SERIAL_ITEM(U32, mt_wt, "count of transmit wait");
	SERIAL_ITEM(U32, mt_fl, "count of transmit failed");
	SERIAL_ITEM(U32, mo_scs, "count of send to SP success");
	SERIAL_ITEM(U32, mo_wt, "count of wait send to SP");
	SERIAL_ITEM(U32, mo_fl, "count if failed send to SP");
	END_SERIAL();
};

class CMPPDeliver : public CMPP {
public:
	BEGIN_SERIAL(CMPPDeliver, CMPP, CMPP_DELIVER, "Deliver SMS to SP");
	SERIAL_ITEM(U64, msg_id, "msg id");
	SERIAL_ARRAY(char, dest_id, 21, "SP serivce id");
	SERIAL_ARRAY(char, service_id, 10, "service id");
	SERIAL_ITEM(U8, tp_pid, "GSM protocol type");
	SERIAL_ITEM(U8, tp_udhi, "GSM protocol type");
	SERIAL_ITEM(U8, msg_fmt, "msg format");
	SERIAL_ARRAY(char, src_terminal_id, 32, "src MSISDN");
	SERIAL_ITEM(U8, src_terminal_type, "src terminal type");
	SERIAL_ITEM(U8, registered_delivery, "Whether is status report");
	SERIAL_ITEM_EX(string, msg_content, U8, "msg content");
	SERIAL_ARRAY(char, link_id, 20, "link id");
	END_SERIAL();
};

class CMPPStatusReport : public Serial {
public:
	BEGIN_SERIAL(CMPPStatusReport, Serial, 0, "CMPP status report");
	SERIAL_ITEM(U64, msg_id, "msg id");
	SERIAL_ARRAY(char, stat, 7, "stat");
	SERIAL_ARRAY(char, submit_time, 10, "submit time");
	SERIAL_ARRAY(char, done_time, 10, "Done time");
	SERIAL_ARRAY(char, dest_terminal_id, 32, "Dest terminal MSISDN");
	SERIAL_ITEM(U32, SMSC_sequence, "SMSC sequence");
	END_SERIAL();
};

class CMPPDeliverResp : public CMPP {
public:
	BEGIN_SERIAL(CMPPDeliverResp, CMPP, CMPP_DELIVER_RESP, "Deliver SMS to SP response");
	SERIAL_ITEM(U64, msg_id, "msg id");
	SERIAL_ITEM(U32, result, "deliver result");
	END_SERIAL();
};

class CMPPCancel : public CMPP {
public:
	BEGIN_SERIAL(CMPPCancel, CMPP, CMPP_CANCEL, "SP delete SMS has been send ISMG");
	SERIAL_ITEM(U64, msg_id, "msg id");
	END_SERIAL();
};

class CMPPCancelResp : public CMPP {
public:
	BEGIN_SERIAL(CMPPCancelResp, CMPP, CMPP_CANCEL_RESP, "CMPPCancel response");
	SERIAL_ITEM(U32, success_id, "0-success 1-failed");
	END_SERIAL();
};

class CMPPActiveTest : public CMPP {
public:
	BEGIN_SERIAL(CMPPActiveTest, CMPP, CMPP_ACTIVE_TEST, "Keepalive from SP to ISMG");
	END_SERIAL();
};

class CMPPActiveTestResp : public CMPP {
public:
	BEGIN_SERIAL(CMPPActiveTestResp, CMPP, CMPP_ACTIVE_TEST_RESP, "CMPPActiveTest response");
	SERIAL_ITEM(U8, reserved, "Reserved word");
	END_SERIAL();
};
#endif
