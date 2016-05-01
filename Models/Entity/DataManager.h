#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include "DataEntitys.h"

class DBService;

class ISMGManager {
public:
	ISMGManager(DBService *dbService);
	~ISMGManager();

	bool Init();
	void Clear();
	bool UpdateISMGInfo();
	bool UpdateISMGParam();

	ISMGInfo *getISMGInfo(const std::string &SP_Id);
	std::string getISMGParamValue(const std::string &SP_Id, const std::string &param_key);

	void getISMGInfoByProtocol( std::list<ISMGInfo *> &lst, const std::string &protocol);

private:
	std::map<std::string, ISMGInfo*> m_mapISMG;
	DBService *m_dbService;
};

#endif
