#include "MysqlAccess.h"
#include "PublicFunction.h"
#include <functions.h>
#include <iostream>
#include <memory>

MysqlQueryResult::MysqlQueryResult() {

}

MysqlQueryResult::MysqlQueryResult(sql::ResultSet *res) : m_res(res)
{
	
}
MysqlQueryResult::~MysqlQueryResult() {
	if (NULL != m_res) {
		delete m_res;
	}
}

bool MysqlQueryResult::fetch() {
	if (NULL == m_res) return false;

	return m_res != NULL ? m_res->next() : false;
}

bool MysqlQueryResult::getBoolean(const std::string& column) {
    bool res = false;	
    try {
        res = m_res->getBoolean(column);
    } catch (sql::InvalidArgumentException& e) {
        THROW_DB(format("Get bool type field exception : %s , Mysql error code : %d, SQLState: %s",
         e.what(), 
         e.getErrorCode(), 
         e.getSQLState().c_str()));
    }
    return res;
}



int MysqlQueryResult::getInt(const std::string& column) {
    int res = 0;
	
    try {
        res = m_res->getInt(column);
    } catch (sql::InvalidArgumentException& e) {
        THROW_DB(format("Get int type field exception : %s , Mysql error code : %d, SQLState: %s",
         e.what(), 
         e.getErrorCode(), 
         e.getSQLState().c_str()));
    }

    return res;
}

unsigned long long MysqlQueryResult::getU64(const std::string& column) {
    unsigned long long res = 0;
	
    try {
        res = m_res->getUInt64(column);
    } catch (sql::InvalidArgumentException& e) {
        THROW_DB(format("Get int type field exception : %s , Mysql error code : %d, SQLState: %s",
         e.what(), 
         e.getErrorCode(), 
         e.getSQLState().c_str()));
    }

    return res;
}

double MysqlQueryResult::getDouble(const std::string& column) {
    double res = 0;

	try {
        return m_res->getDouble(column);
    } catch (sql::InvalidArgumentException& e) {
        THROW_DB(format("Get int type field exception : %s , Mysql error code : %d, SQLState: %s",
         e.what(), 
         e.getErrorCode(), 
         e.getSQLState().c_str()));
    }

    return res;
}

std::string MysqlQueryResult::getString(const std::string& column) {
    std::string res = "";

	try {
        return m_res->getString(column);
    } catch (sql::InvalidArgumentException& e) {
        THROW_DB(format("Get int type field exception : %s , Mysql error code : %d, SQLState: %s",
         e.what(), 
         e.getErrorCode(), 
         e.getSQLState().c_str()));
    }

    return res;
}

MysqlParamSet::MysqlParamSet() : m_preStmt(NULL) {

}

MysqlParamSet::MysqlParamSet(sql::PreparedStatement *preStmt) : m_preStmt(preStmt) {
    
}

MysqlParamSet::~MysqlParamSet() {
    
}

void MysqlParamSet::setBoolean(int index, bool value){
    if (NULL == m_preStmt) return;
    m_preStmt->setBoolean(index, value);
}
    
void MysqlParamSet::setInt(int index, int value){
    if (NULL == m_preStmt) return;
    m_preStmt->setInt(index, value);
}

void MysqlParamSet::setU64(int index, unsigned long long value) {
    if (NULL == m_preStmt) return;
    m_preStmt->setUInt64(index, value);  
}

void MysqlParamSet::setDouble(int index, double value) {
    if (NULL == m_preStmt) return;
    m_preStmt->setDouble(index, value); 
}

void MysqlParamSet::setString(int index, const std::string& value) {
    if (NULL == m_preStmt) return;
    m_preStmt->setString(index, value);
}

MysqlAccess::MysqlAccess(DatabaseInfo dbInfo) :
	DBAccess(dbInfo),
    m_isInit(false),
	m_dbDriver(NULL), m_dbConn(NULL)
{
	
}


MysqlAccess::~MysqlAccess()
{
    if (NULL != m_dbConn) delete m_dbConn;
    //if (NULL != m_dbDriver) delete m_dbDriver;
}

bool MysqlAccess::init() {
	if (true == m_isInit) {
		return true;
	}

	m_dbDriver = get_driver_instance();
    if (NULL == m_dbDriver) {
        MYLOG_ERROR("Failed to get mysql driver");
        return false;
    }
    
    ::sql::ConnectOptionsMap connection_properties;
    connection_properties["hostName"] = sql::SQLString(m_dbInfo.m_host.c_str());
    connection_properties["userName"] = sql::SQLString(m_dbInfo.m_username.c_str());
    connection_properties["password"] = sql::SQLString(m_dbInfo.m_password.c_str());
    connection_properties["port"] = m_dbInfo.m_port;
    
    connection_properties.erase("OPT_RECONNECT");
    connection_properties["OPT_RECONNECT"] = true;
	connection_properties.erase("OPT_CHARSET_NAME");
	sql::SQLString charset(m_dbInfo.m_charset.c_str());
    connection_properties["OPT_CHARSET_NAME"] = charset;
    
    std::string statement = "use ";
	statement += m_dbInfo.m_dbname;
	sql::SQLString preExecute(statement);
	connection_properties.erase("preInit");
    connection_properties["preInit"] = preExecute;
	connection_properties.erase("postInit");
    connection_properties["postInit"] = preExecute;
    
    try {
        m_dbConn = m_dbDriver->connect(connection_properties);
        if (NULL == m_dbConn) {
            //MYLOG_ERROR("Connect mysql sever failed. tcp://%s:%d/%s?charset=%s", m_host.c_str(), m_port, m_dbname.c_str(), m_charset.c_str());
            //return false;
            THROW_DB(format("Connect mysql sever failed. tcp://%s:%d/%s?charset=%s", m_dbInfo.m_host.c_str(), 
                m_dbInfo.m_port, m_dbInfo.m_dbname.c_str(), m_dbInfo.m_charset.c_str()));
        }
    } catch (sql::SQLException &e) {
        //MYLOG_ERROR("Connect mysql sever failed: %s", e.what());
        //return false;
        THROW_DB(format("Connect mysql server failed. tcp://%s:%d/%s?charset=%s. DbcException: %s\nMysql error code: %d\nSQLState: %s",
                m_dbInfo.m_host.c_str(), m_dbInfo.m_port, m_dbInfo.m_dbname.c_str(), m_dbInfo.m_charset.c_str(),
                e.what(), e.getErrorCode(), e.getSQLState().c_str()));
    }
    
    //MYLOG_DEBUG("Init msyql access finished");
    
    m_isInit = true;

	return m_isInit;
}

QueryResult* MysqlAccess::query(const std::string& sql, void (*set)(ParamSet&, void*), void* param) {
	QueryResult* p_queryresult = NULL;

	try {
	    if (false == init()) return NULL;
	    
		
        std::auto_ptr<sql::PreparedStatement> pstmt(m_dbConn->prepareStatement(sql));
        if (NULL != set && NULL != param) {
            MysqlParamSet paramset(pstmt.get());
            set(paramset, param);
        } 
        
        std::auto_ptr<sql::ResultSet> resSet(pstmt->executeQuery());
        if (NULL != resSet.get()) {
            p_queryresult = new MysqlQueryResult(resSet.release());
        }       
    } catch(sql::SQLException &e) {
		THROW_DB(format("DbcException: %s\nMySQL error code: %d\nSQLState: %s",
					e.what(),
					e.getErrorCode(),
					e.getSQLState().c_str()));
	} catch (std::runtime_error &e) {
		THROW_DB(format("runtime_error: %s", e.what()));
	}
	
	return p_queryresult;
}

int MysqlAccess::update(const std::string& sql, void (*set)(ParamSet&, void*), void* param) {
    int affect_rows = 0;

    try {
        if (false == init()) return 0;
    
        std::auto_ptr<sql::PreparedStatement> pstmt(m_dbConn->prepareStatement(sql));
        if (NULL != set && NULL != param) {
            MysqlParamSet paramset(pstmt.get());
            set(paramset, param);
        } 
        
        affect_rows = pstmt->executeUpdate();
    } catch (const DBException& e) {
        throw e;
    } catch (const sql::SQLException &e) {
		THROW_DB(format("DbcException: %s\nMySQL error code: %d\nSQLState: %s",
					e.what(),
					e.getErrorCode(),
					e.getSQLState().c_str()));
	} catch (const std::runtime_error &e) {
		THROW_DB(format("runtime_error: %s", e.what()));
	}
    
    return affect_rows;
}

bool MysqlAccess::execute(const std::string& sql, void (*set)(ParamSet&, void*), void* param) {
    bool success = false;
    try {
         if (false == init()) return false;
     
         std::auto_ptr<sql::PreparedStatement> pstmt(m_dbConn->prepareStatement(sql));
         if (NULL != set && NULL != param) {
             MysqlParamSet paramset(pstmt.get());
             set(paramset, param);
         } 
        
         success = pstmt->execute();
         success = true;
    } catch (const DBException& e) {
        throw e;
    } catch(sql::SQLException &e) {
		THROW_DB(format("DbcException: %s\nMySQL error code: %d\nSQLState: %s",
					e.what(),
					e.getErrorCode(),
					e.getSQLState().c_str()));
	} catch (std::runtime_error &e) {
		THROW_DB(format("runtime_error: %s", e.what()));
	}
    
    return success; 
}

