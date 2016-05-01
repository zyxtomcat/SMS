#include "DBAccess.h"

DatabaseInfo::DatabaseInfo(const std::string& host, short port,
		const std::string& username, const std::string& password,
		const std::string& dbname, 
        const std::string& charset) :
m_host(host), m_port(port),
m_username(username), m_password(password),
m_dbname(dbname), m_charset(charset)
{

}
DatabaseInfo::~DatabaseInfo() {

}

DBAccess::DBAccess(const DatabaseInfo& dbInfo) : m_dbInfo(dbInfo)
{
}


DBAccess::~DBAccess()
{
}


