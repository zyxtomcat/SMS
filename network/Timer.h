#ifndef _TIMER_H
#define _TIMER_H

#include "Object.h"
#include "DataTypeDef.h"
#include "Event.h"

class Timer : public Object
{
public:
    Timer();
    virtual ~Timer();

    bool Start();
    void Stop();
    void Restart();
    void SetInterval(U32 u32Second);
    U32 GetInterval() const;
    void SetCtx(void *ctx);
    void *GetCtx();

    EventNotify OnTimer;

    void DoTimer();
private:   
    bool m_bEnabled;
    U32 m_u32Interval;
    void *m_context;
};

#endif
