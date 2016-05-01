#ifndef _ERRORCODE_H
#define _ERRORCODE_H

#include <string>

enum SAS_ERRORCODE {
	SAS_SUCCESS = 0,
	SAS_SERVER_INTERNAL_ERROR = 1,
	SAS_BAD_REQUEST_CONTENT = 2,
	SAS_CMPP_NOT_LOGIN = 10,
};

std::string getErrorDesc(int error_code);

#endif
