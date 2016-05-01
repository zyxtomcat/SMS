#include "DataManager.h"
#include <functions.h>
#include "DBService.h"

ISMGManager::ISMGManager(DBService *dbService) : m_dbService(dbService) {

}

ISMGManager::~ISMGManager() {

}

bool ISMGManager::Init() {
	return UpdateISMGInfo() && UpdateISMGParam();
}

void ISMGManager::Clear() {
	std::map<std::string, ISMGInfo*>::iterator it = m_mapISMG.begin();
	for (; it != m_mapISMG.end(); ++it) {
		ISMGInfo *pInfo = it->second;
		if (NULL != pInfo) {
			pInfo->Clear();
		}

		delete pInfo;
	}

	m_mapISMG.clear();
}

bool ISMGManager::UpdateISMGInfo() {
	std::list<ISMGInfo *> lst;
	if (true == m_dbService->getAllISMGInfo(lst)) {
		for (std::list<ISMGInfo *>::iterator it = lst.begin(); 
			it != lst.end(); 
			++it) {
			ISMGInfo *pInfo = *it;
			if (NULL != pInfo) {
				m_mapISMG.insert(std::make_pair(pInfo->SP_Id, pInfo));
			}
		}
		
		MYLOG_INFO("Update ISMGInfo success");
		return true;
	} else {
		MYLOG_ERROR("Update ISMGParam failed");
		return false;
	}
}

bool ISMGManager::UpdateISMGParam() {
	std::list<ISMGParam *> lst;
	if (true == m_dbService->getAllISMGParam(lst)) {
		for (std::list<ISMGParam *>::iterator it = lst.begin();
			it != lst.end();
			++it) {
			ISMGParam *pParam = *it;
			if (NULL != pParam) {
				ISMGInfo *pInfo = getISMGInfo(pParam->SP_Id);
				if (NULL != pInfo) {
					pInfo->UpdateParam(pParam);
				} else {
					delete pParam;
				}
			}
		}

		MYLOG_INFO("Update ISMGParam success");
		return true;
	} else {
		MYLOG_ERROR("Update ISMGParam failed");
		return false;
	}
}

ISMGInfo *ISMGManager::getISMGInfo(const std::string &SP_Id) {
	std::map<std::string, ISMGInfo *>::iterator it = m_mapISMG.find(SP_Id);
	if (it != m_mapISMG.end()) {
		return it->second;
	}

	return NULL;
}

std::string ISMGManager::getISMGParamValue(const std::string &SP_Id, const std::string &param_key) {
	std::string str;
	ISMGInfo *pInfo = getISMGInfo(SP_Id);
	if (NULL != pInfo) {
		str = pInfo->getISMGParamValue(param_key);
	}

	return str;
}

void ISMGManager::getISMGInfoByProtocol( std::list<ISMGInfo*> &lst, const std::string &protocol) {
	std::map<std::string, ISMGInfo *>::iterator it = m_mapISMG.begin();
	for (; it != m_mapISMG.end(); ++it) {
		ISMGInfo *pInfo = it->second;
		if (NULL != pInfo && pInfo->protocol.compare(protocol) == 0) {
			lst.push_back(pInfo);
		}
	}	
}
