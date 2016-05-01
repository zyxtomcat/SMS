#ifndef _DBMANAGER_H
#define _DBMANAGER_H

#include "DBAccess.h"
#include <list>
#include <memory>
#include "functions.h"
#include "locker.h"


class DBServiceBase {
public:
	DBServiceBase(const DatabaseInfo& dbInfo, int maxconcurrency);
	virtual ~DBServiceBase();

protected:
	template<typename P, typename R>
	bool query(const std::string& sql,                          //sql
                void (*set)(ParamSet&, void*), const P& param,  //param and param set function
                void (*get)(QueryResult *, R&),                 //result assign function
                std::list<R*>& lstInfo,
                DBAccess *dbAccess = NULL) {                       //result list
		bool success = false;
        bool isExistAccess = true;
        if (NULL == dbAccess) {
            isExistAccess = false;
            dbAccess = getDBAccess();
            if (NULL == dbAccess) return false;
        }
        
        try {
            MYLOG_DEBUG("sql query: %s", sql.c_str());
            
            std::auto_ptr<QueryResult> pResult(dbAccess->query(sql, set, (void*)&param));
		    if (NULL != pResult.get()) {
			    while (pResult->fetch()) {
				    std::auto_ptr<R> pR(new R);
				    if (NULL != pR.get()) {
                        get(pResult.get(), *pR);
                        lstInfo.push_back(pR.release());
                    }
                }
			    success = true;
		    } else {
			    success = false;
		    }
        } catch (const DBException &e) {
            MYLOG_ERROR("Query results DBException:%s", e.what());
            if (false == isExistAccess) releaseDBAccess(dbAccess);
        }		
		
        if (false == isExistAccess) releaseDBAccess(dbAccess);	
		return success;
	}
    
    template<typename P>
    bool update(const std::string& sql, void (*set)(ParamSet&, void*), const P& param, DBAccess *dbAccess = NULL) {
        bool success = false;
        bool isExistAccess = true;
        if (NULL == dbAccess) {
            isExistAccess = false;
            dbAccess = getDBAccess();
            if (NULL == dbAccess) return false;
        }
        
        try {
            MYLOG_DEBUG("sql update: %s", sql.c_str());
           
            int affect_rows = dbAccess->update(sql, set, (void *)(&param));  
            MYLOG_DEBUG("sql update: %s. affect_rows=%d", sql.c_str(), affect_rows);
            success = true;
        } catch (const DBException &e) {
            MYLOG_ERROR("Update DBException:%s", e.what());
            if (false == isExistAccess) releaseDBAccess(dbAccess);
        }
        
        if (false == isExistAccess) releaseDBAccess(dbAccess);
        return success;
    }
    
    template<typename P> 
    bool execute(const std::string& sql, void (*set)(ParamSet&, void*), const P& param, DBAccess *dbAccess = NULL) {
        bool success = false;
        bool isExistAccess = true;
        if (NULL == dbAccess ) {
            isExistAccess = false;
            dbAccess = getDBAccess();
            if (NULL == dbAccess) return false;
        }
        
        try {
            MYLOG_DEBUG("sql execute: %s", sql.c_str());

            success = dbAccess->execute(sql, set, (void *)(&param));
        } catch (const DBException &e) {
            MYLOG_ERROR("Execute DBException:%s", e.what());
            if (false == isExistAccess) releaseDBAccess(dbAccess);
        }
        
        MYLOG_DEBUG("execute result %d", success);
        if (false == isExistAccess) releaseDBAccess(dbAccess);
        return success;
    }
    
protected:
    virtual DBAccess* getDBAccess();
    void releaseDBAccess(DBAccess *dbAccess);


    Locker m_lock;
	std::list<DBAccess *> m_lstDBAccess;
    int m_maxconcurrency;
    DatabaseInfo m_dbInfo;
};

#endif
