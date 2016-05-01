#include "Timer.h"
#include "EventDriver.h"
#include "Singleton.h"

Timer::Timer()
:m_bEnabled(false), m_u32Interval(0), m_context(NULL) 
{

}

Timer::~Timer()
{
    Stop();
}

bool Timer::Start() {
    if (!m_bEnabled && m_u32Interval > 0) {
        if (true == SINGLETON(EventDriver)->add(this)) {
            m_bEnabled = true;
        }
    }

    return m_bEnabled;
}


void Timer::Stop() {
    if (m_bEnabled) {
        SINGLETON(EventDriver)->del(this);
        m_bEnabled = false;
    }  
}

void Timer::Restart()
{
    Stop();
    Start(); 
}

void Timer::SetInterval(U32 u32Second)
{
    if (u32Second > 0 && m_u32Interval != u32Second)
    {
        m_u32Interval = u32Second;
        Restart();
    }
}

U32 Timer::GetInterval() const
{
    return m_u32Interval;
}

void Timer::DoTimer()
{
    if (OnTimer.Assigned())
    {
        OnTimer(this);
    }
}   

void Timer::SetCtx(void *ctx) {
    m_context = ctx;
}

void *Timer::GetCtx() {
    return m_context;
}
