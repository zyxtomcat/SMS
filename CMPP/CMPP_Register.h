#ifndef _CMPP_REGISTER_H
#define _CMPP_REGISTER_H

#include "ClassRegister.h"
#include "CMPP.h"

REG_CLASS_BEGIN(_CMPP);
REG_CLASS(_CMPP, CMPPConnect);
REG_CLASS(_CMPP, CMPPConnectResp);
REG_CLASS(_CMPP, CMPPTerminate);
REG_CLASS(_CMPP, CMPPTerminateResp);
REG_CLASS(_CMPP, CMPPSubmit);
REG_CLASS(_CMPP, CMPPSubmitResp);
REG_CLASS(_CMPP, CMPPQuery);
REG_CLASS(_CMPP, CMPPQueryResp);
REG_CLASS(_CMPP, CMPPDeliver);
REG_CLASS(_CMPP, CMPPDeliverResp);
REG_CLASS(_CMPP, CMPPCancel);
REG_CLASS(_CMPP, CMPPCancelResp);
REG_CLASS(_CMPP, CMPPActiveTest);
REG_CLASS(_CMPP, CMPPActiveTestResp);
REG_CLASS_END(_CMPP);

/*
template<typename TypeList>
struct RegistClass<SerialClassManager<CMPP>, TypeList > {
    static void Do() {
        SerialClassManager<CMPP>::RegistClassFunc<typename TypeList::Head>();
        RegistClass<SerialClassManager<CMPP>, typename TypeList::Tail>::Do();
    }
};

template<>
struct RegistClass<SerialClassManager<CMPP>, NullType> {
    static void Do() {
    }
};
*/

void RegisterCMPP();

#endif
