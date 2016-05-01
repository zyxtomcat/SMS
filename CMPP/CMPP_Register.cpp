#include "CMPP_Register.h"

void RegisterCMPP() {
	RUN_REG_CLASS(SerialClassManager<CMPP>, _CMPP);
}
