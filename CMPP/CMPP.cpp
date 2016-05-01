#include "CMPP.h"

CMPP::CMPP() 
: seq(0), m_pDecodeContent(NULL), m_ulDecodeSize(0) {

}

CMPP::~CMPP() {
	if (NULL != m_pDecodeContent && m_ulDecodeSize > 0) {
		delete m_pDecodeContent;
		m_pDecodeContent = NULL;
		m_ulDecodeSize = 0;
	}
 }

CMPP::CMPP(const CMPP& src) {
	*this = src;
}

CMPP& CMPP::operator=(const CMPP& src) {
	if (this != &src) {
		if (NULL != m_pDecodeContent) {
			delete []m_pDecodeContent;
			m_pDecodeContent = NULL;
			m_ulDecodeSize = 0;
		}

		seq = src.seq;
	}	

	return *this;
}

unsigned int CMPP::CheckData(const char* pData, unsigned int ulLen, int& nUsed) {
	const CMPPHeader *pHeader = (const CMPPHeader *)pData;
	U32 u32Len = NTOH(pHeader->total_length);
	U32 command_id = NTOH(pHeader->command_id);
	//U32 sequence_id = NTOH(pHeader->sequence_id);
	if (ulLen >= (sizeof(CMPPHeader)) && command_id > 0 && u32Len > CMPP::MIN_SERIAL_LENGTH ) {
		if (u32Len <= ulLen) {
			nUsed = u32Len;
			return command_id;
		} else {
			nUsed = -1;
			return 0;
		}	
	} else {
		nUsed = 0;
		return 0;
	}
}

void CMPP::setSeq(U32 seq) {
	this->seq = seq;
}

U32 CMPP::getSeq() {
	return seq;
}

char* CMPP::BeforeSerial(char* pData) {
	CMPPHeader *pHeader = (CMPPHeader *)pData;
	pHeader->total_length = HTON(m_ulSerialSize);
	pHeader->command_id = HTON(GetKey());
	pHeader->sequence_id = HTON(seq);
	return pData + sizeof(CMPPHeader);
}

char* CMPP::AfterSerial(char* pData) {
	return pData;
}

char* CMPP::BeforeUnserial(char* pData) {
	CMPPHeader *pHeader = (CMPPHeader *)pHeader;
	seq = NTOH(pHeader->sequence_id);
	m_pDecodeContent = pData + sizeof(CMPPHeader);
	return m_pDecodeContent;
}

char* CMPP::AfterUnserial(char* pData) {
	pData = m_pHeader + m_ulSerialSize;
	return pData;
}

unsigned int CMPP::DoSerialSize() {
	return sizeof(CMPPHeader) + Serial::DoSerialSize();
}

CMPPSubmit::CMPPSubmit()
:msg_id(0),
pk_total(1),
pk_number(1),
registered_delivery(1),
msg_level(0),
fee_usertype(0),
fee_terminal_type(0),
tp_pid(0),
tp_udhi(0),
msg_fmt(MSG_FMT_UCS2),
dest_terminal_type(0) 
{
	memset(service_id, 0x00, sizeof(service_id));
	memset(fee_terminal_id, 0x00, sizeof(fee_terminal_id));
	memset(msg_src, 0x00, sizeof(msg_src));
	memset(fee_type, 0x00, sizeof(fee_type));
	memset(fee_code, 0x00, sizeof(fee_code));
	memset(valid_time, 0x00, sizeof(valid_time));
	memset(at_time, 0x00, sizeof(at_time));
	memset(src_id, 0x00, sizeof(src_id));
	memset(link_id, 0x00, sizeof(link_id));
}
