#include "DBServiceBase.h"


DBServiceBase::DBServiceBase(const DatabaseInfo& dbInfo, int maxconcurrency) :
m_dbInfo(dbInfo), m_maxconcurrency(maxconcurrency)
{
	
}


DBServiceBase::~DBServiceBase()
{
	
}

DBAccess* DBServiceBase::getDBAccess() {
	DBAccess* dbAccess = NULL;

	{
		LockerGuard lockerGuard(m_lock);
		if (!m_lstDBAccess.empty()) {
			dbAccess = *m_lstDBAccess.begin();
			m_lstDBAccess.pop_front();
		} 
	}

	return dbAccess;
}

void DBServiceBase::releaseDBAccess(DBAccess* dbAccess) {
	LockerGuard lockerGuard(m_lock);
	if (m_lstDBAccess.size() >= m_maxconcurrency) {
		delete dbAccess;
	} else {
		m_lstDBAccess.push_back(dbAccess);
	}
}
