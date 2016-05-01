#ifndef _MYSQLACCESS_H
#define _MYSQLACCESS_H

#include "DBAccess.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <mysql_driver.h>
#include <mysql_connection.h>


class MysqlQueryResult : public QueryResult {
public:
	MysqlQueryResult();
	MysqlQueryResult(sql::ResultSet *res);
	~MysqlQueryResult();

	bool fetch();

    bool getBoolean(const std::string& column);

	int getInt(const std::string& column);

    unsigned long long getU64(const std::string & column);

	double getDouble(const std::string& column);

	std::string getString(const std::string& column);

private:
	sql::ResultSet *m_res;
};

class MysqlParamSet : public ParamSet {
public:
    MysqlParamSet();
    MysqlParamSet(sql::PreparedStatement *preStmt);
    ~MysqlParamSet();
    
    void setBoolean(int index, bool value);
    void setInt(int index, int value);
    void setU64(int index, unsigned long long value);
    void setDouble(int index, double value);
    void setString(int index, const std::string& value);

private:
   sql::PreparedStatement* m_preStmt;      
};

class MysqlAccess : public DBAccess
{
public:
	MysqlAccess(DatabaseInfo dbInfo);

	~MysqlAccess();

	virtual QueryResult* query(const std::string& sql, void (*set)(ParamSet&, void*), void* param);
    virtual int update(const std::string& sql, void (*set)(ParamSet&, void*), void* param);
    virtual bool execute(const std::string& sql, void (*set)(ParamSet&, void*), void* param);
protected:
	bool init();

private:
	bool m_isInit;
	
	sql::Driver *m_dbDriver;
    sql::Connection *m_dbConn;
};

#endif
