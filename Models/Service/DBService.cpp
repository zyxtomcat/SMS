#include "DBService.h"
#include "DataEntitys.h"
#include "MysqlAccess.h"

struct SMSLogQueryParam {
	std::string num;
	std::string begin_time;
	std::string end_time;
};

/*-----------------------------------------------------------------*/

static void AssignAutoincrementId(QueryResult *pRes, U32 &Id) {
	Id = pRes->getInt("LAST_INSERT_ID()");
}

static void AssignISMGInfo(QueryResult *pRes, ISMGInfo &entity) {
	entity.id = pRes->getInt("id");
	entity.SP_Id = pRes->getString("SP_Id");
	entity.server_host = pRes->getString("server_host");
	entity.server_port = pRes->getInt("server_port");
	entity.protocol = pRes->getString("protocol");
}

static void AssignISMGParam(QueryResult *pRes, ISMGParam &entity) {
	entity.SP_Id = pRes->getString("SP_Id");
	entity.param_key = pRes->getString("param_key");
	entity.param_value = pRes->getString("param_value");
}

static void AssignCustomNumSeg(QueryResult *pRes, CustomerNumSeg &entity) {
	entity.Src_id = pRes->getString("Src_id");
	entity.SP_Id = pRes->getString("SP_Id");
}

static void AssignSMSLog(QueryResult *pRes, SMSLog &entity) {
	entity.id = pRes->getInt("id");
	entity.Msg_Id = pRes->getU64("Msg_Id");
	entity.SP_Id = pRes->getString("SP_Id");
	entity.Src_Id = pRes->getString("Src_Id");
	entity.Dst_Id = pRes->getString("Dst_Id");
	entity.sms_content = pRes->getString("sms_content");
	entity.sms_fmt = pRes->getInt("sms_fmt");
	entity.sms_type = pRes->getBoolean("sms_type");
    entity.done_time = pRes->getString("done_time");
	entity.create_time = pRes->getString("create_time");
	entity.update_time = pRes->getString("update_time");
}
/*-----------------------------------------------------------------*/

static void setCustomerNumSegParam(ParamSet &paramSet, void *param) {
	std::string *num = (std::string *)param;
	paramSet.setString(1, *num);
	paramSet.setString(2, *num);
}

static void setSMSLogInsertParam(ParamSet &paramSet, void *param) {
	SMSLog *smsLog = (SMSLog *)param;
	paramSet.setU64(1, smsLog->Msg_Id);
	paramSet.setString(2, smsLog->SP_Id);
	paramSet.setString(3, smsLog->Src_Id);
	paramSet.setString(4, smsLog->Dst_Id);
	paramSet.setString(5, smsLog->sms_content);
	paramSet.setInt(6, smsLog->sms_fmt);
	paramSet.setBoolean(7, smsLog->sms_type);
    paramSet.setString(8, smsLog->done_time.toString());
	paramSet.setString(9, smsLog->create_time.toString());
	paramSet.setString(10, smsLog->update_time.toString());
}

static void setUpdateSMSLogAfterSendParam(ParamSet &paramSet, void *param) {
	SMSLog *smsLog = (SMSLog *)param;
	paramSet.setU64(1, smsLog->Msg_Id);
	paramSet.setInt(2, smsLog->pk_total);
}

static void setSMSLogQueryParam(ParamSet &paramSet, void *param) {
	SMSLogQueryParam *queryParam = (SMSLogQueryParam *)param;
	paramSet.setString(1, queryParam->num);
	paramSet.setString(2, queryParam->begin_time);
	paramSet.setString(3, queryParam->end_time);
}
/*-----------------------------------------------------------------*/

DBService::DBService(const DatabaseInfo& dbInfo, int maxconcurrency) : DBServiceBase(dbInfo, maxconcurrency) {
	LockerGuard lockerGuard(m_lock);
	for (int i = 0; i < m_maxconcurrency; ++i)
	{
		DBAccess *dbAccess = new MysqlAccess(m_dbInfo);
		if (NULL != dbAccess) {
			m_lstDBAccess.push_back(dbAccess);
		}
	}
}

DBService::~DBService() {
	LockerGuard lockerGuard(m_lock);
	for(std::list<DBAccess*>::iterator it = m_lstDBAccess.begin();
		it != m_lstDBAccess.end();
		++it) {
		delete *it;
	}
}

DBAccess* DBService::getDBAccess() {
    DBAccess *dbAccess = DBServiceBase::getDBAccess();
	if (NULL == dbAccess) {
		dbAccess =  new MysqlAccess(m_dbInfo);
	}

    return dbAccess;
}

bool DBService::getAllISMGInfo(std::list<ISMGInfo *>& lst) {
	std::string sql("SELECT * FROM t_ISMG_Info");
	return query(sql, NULL, NULL, AssignISMGInfo, lst);
}

bool DBService::getAllISMGParam(std::list<ISMGParam *> lst) {
	std::string sql("SELECT * FROM t_ISMG_param");
	return query(sql, NULL, NULL, AssignISMGParam, lst);
}

bool DBService::getCustomerNumSeg(const std::string &num, CustomerNumSeg& seg) {
	std::string sql("SELECT SP_Id, Src_Id FROM t_num_segment WHERE begin_num<=? and end_num>=?");
	std::list<CustomerNumSeg *> lst;
	bool result = false;
	if (true == query(sql, setCustomerNumSegParam, num, AssignCustomNumSeg, lst)) {
		if (lst.size() == 1) {
			CustomerNumSeg *pResult = lst.front();
			if (NULL != pResult) {
				seg.Src_id = pResult->Src_id;
				seg.SP_Id = pResult->SP_Id;
				result = true;
			}
		}

		for (std::list<CustomerNumSeg *>::iterator it = lst.begin(); it != lst.end(); ++it) {
			delete *it;
		}
	}

	return result;
}

U32 DBService::addSMSLog(const SMSLog & smsLog) {
	DBAccess *dbAccess = getDBAccess();
    if (NULL == dbAccess) return 0;
	std::string sql("INSERT INTO t_sms_log(Msg_Id,SP_Id,Src_Id,Dst_Id,sms_content,sms_fmt,sms_type,"
		"comfirm_flag,done_time, comfirm_time,create_time,update_time) VALUES(?,?,?,?,?,?,?,?,?,?,?,?)");
	int id  = 0;
    std::list<U32 *> lst;
	if (true == execute(sql, setSMSLogInsertParam, smsLog, dbAccess)) {
		sql = "SELECT LAST_INSERT_ID()";
        if (true == query(sql, NULL, NULL, AssignAutoincrementId, lst, dbAccess)) {
            if (lst.size() == 1) {
                id = *lst.front();
            } 
                
            for (std::list<U32 *>::iterator it = lst.begin(); it != lst.end(); ++it) {
                delete *it;
            }
            lst.clear(); 
        }
	}

	releaseDBAccess(dbAccess);
	return id;
}

bool DBService::updateSMSLogAfterSend(const SMSLog &smsLog) {
	std::string sql("UPDATE t_sms_log SET Msg_Id=?,pk_total=? WHERE id=?");
	return execute(sql, setUpdateSMSLogAfterSendParam, smsLog);
}

bool DBService::getSMSLog(const std::string &num, const std::string &beginTime, const std::string &endTime, std::list<SMSLog *> lst) {
	std::string sql("SELECT * FROM t_sms_log WHERE Dst_Id=? AND sms_type=1 AND create_time between ? and ?");
	SMSLogQueryParam param;
	param.num = num;
	param.begin_time = beginTime;
	param.end_time = endTime;

	return query(sql, setSMSLogQueryParam, param, AssignSMSLog, lst);
}
