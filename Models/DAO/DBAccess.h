#ifndef _DBACCESS_H
#define _DBACCESS_H

#include <string>
#include <exception>

#define THROW_DB(what) \
	throw DBException(what, __FILE__, __FUNCTION__, __LINE__);

#define THROW_DB_CODE(error_code) \
	throw DBException((error_code, "", __FILE__, __FUNCTION__, __LINE__));

#define THROW_DB_CODE0(error_code, what) \
	throw DBException((error_code), (what), __FILE__, __FUNCTION__, __LINE__);

#define SET_CATCH_POS(comm_ex) \
	comm_ex.set_catch_file(__FILE__); \
	comm_ex.set_catch_function(__FUNCTION__); \
	comm_ex.set_catch_line(__LINE__); 

class DBException : public std::exception {
public:
	DBException(const std::string& what, const std::string& throw_file = "", const std::string& throw_function = "", int throw_line = -1) :
		m_what(what), m_throw_file(throw_file), m_throw_function(throw_function), m_throw_line(throw_line), m_catch_line(-1), m_error_code(-1) {

	}
	DBException(int code, const std::string& what = "", const std::string& throw_file = "", const std::string& throw_function = "", int throw_line = -1)
		:m_what(what), m_throw_file(throw_file),
		m_throw_function(throw_function), m_throw_line(throw_line), m_catch_line(-1),
		m_error_code(code)
	{

	}
	virtual ~DBException() throw()
	{

	}
	virtual const char *what() const throw () {
		return m_what.c_str();
	}

	inline const char *get_throw_file() const {
		return m_throw_file.c_str();
	}

	inline const char *get_throw_function() const {
		return m_throw_function.c_str();
	}

	inline int get_throw_line() const {
		return m_throw_line;
	}

	inline void set_catch_file(const char *catch_file) {
		m_catch_file = catch_file;
	}

	inline void set_catch_function(const char *catch_function) {
		m_catch_function = m_catch_function;
	}

	inline void set_catch_line(int catch_line) {
		m_catch_line = catch_line;
	}

	inline const char *get_catch_file() const {
		return m_catch_file.c_str();
	}

	inline const char *get_catch_function() const {
		return m_catch_function.c_str();
	}

	inline int get_catch_line() const {
		return m_catch_line;
	}

	inline int get_error_code() const {
		return m_error_code;
	}

protected:
	std::string m_what;
	std::string m_throw_file;
	std::string m_throw_function;
	int m_throw_line;

	std::string m_catch_file;
	std::string m_catch_function;
	int m_catch_line;
	int m_error_code;
};

class DatabaseInfo {
public:
	DatabaseInfo(const std::string& host, short port,
		const std::string& username, const std::string& password,
		const std::string& dbname, 
        const std::string& charset = "utf8");
	~DatabaseInfo();

	std::string m_host;
	short m_port;
	std::string m_username;
	std::string m_password;
	std::string m_dbname;
    std::string m_charset;
};

class QueryResult {
public:
	QueryResult() {}
	virtual ~QueryResult() {}

	virtual bool fetch() = 0;

    virtual bool getBoolean(const std::string& column) = 0;

	virtual int getInt(const std::string& column) = 0;
    
    virtual unsigned long long getU64(const std::string& column) = 0;

	virtual double getDouble(const std::string& column) = 0;

	virtual std::string getString(const std::string& column) = 0;
};

class ParamSet {
public:
    ParamSet() {}
    virtual ~ParamSet() {}
    
    virtual void setBoolean(int index, bool value) = 0;
    virtual void setInt(int index, int value) = 0;
    virtual void setU64(int index, unsigned long long value) = 0;
    virtual void setDouble(int index, double value) = 0;
    virtual void setString(int index, const std::string& value) = 0;
};

class DBAccess
{
public:
	DBAccess(const DatabaseInfo& dbInfo);

	virtual ~DBAccess();

	virtual QueryResult* query(const std::string& sql, void (*set)(ParamSet&, void*), void* param) = 0;
    virtual int update(const std::string& sql, void (*set)(ParamSet&, void*), void* param) = 0;
    virtual bool execute(const std::string& sql, void (*set)(ParamSet&, void*), void* param) = 0;
protected:
	virtual bool init() { return false;  }

protected:
	DatabaseInfo m_dbInfo;
};

#endif
