#include "ErrorCode.h"

static const std::string error_desc[] = {
	"Success",
	"Server internal error",
	"Bad request content",
	"SMS wait response timeout",
	"SMS response error",
	"",
	"",
	"",
	"",
	"",
	"CMPP not login"
};


std::string getErrorDesc(int error_code) {
	return error_desc[error_code];
}
