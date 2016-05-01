#ifndef _EVENT_
#define _EVENT_

#include "Object.h"

#define EVENT_BIND(eventname, instance, eventhandle) eventname.Assign(instance, PENotify(&eventhandle))
#define EVENT_UNBIND(eventname) eventname.Assign(NULL, NULL)
#define EventPtr(p) ((PENotify)&p)

//类事件指针转换宏
typedef void (Object::*PENotify)(Object* pSender);

template <typename R>
struct EventDef;

template <typename R>
struct EventDef<R()>
{
public: 
    typedef R (Object::*FuncPtr)(); 
    R operator()()
    {
        return (m_pObj->*m_ptr)();
    } 

    R Execute()
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)();
        }
        else
        {
        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {
    } 

    ~EventDef()
    {
    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:											
    EventDef(const EventDef&); 
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1>
struct EventDef<R(P1)>
{
public: 
    typedef R (Object::*FuncPtr)(P1); 
    R operator()(P1 p1)
    {
        return (m_pObj->*m_ptr)(p1);
    }

    R Execute(P1 p1)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1);
        }
        else
        {
        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:  												
    EventDef(const EventDef&); 
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

typedef EventDef<void(Object* pSender)> EventNotify;

template <typename R, typename P1, typename P2>
struct EventDef<R(P1, P2)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2); 
    R operator()(P1 p1, P2 p2)
    {
        return (m_pObj->*m_ptr)(p1, p2);
    } 

    R Execute(P1 p1, P2 p2)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:  											
    EventDef(const EventDef&); 
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3>
struct EventDef<R(P1, P2, P3)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3); 
    R operator()(P1 p1, P2 p2, P3 p3)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3);
    } 

    R Execute(P1 p1, P2 p2, P3 p3)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:  												
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4>
struct EventDef<R(P1, P2, P3, P4)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4);
    } 
    R Execute(P1 p1, P2 p2, P3 p3, P4 p4)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4);
        }
        else
        {

        }
    }

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:  											
    EventDef(const EventDef&); 
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5>
struct EventDef<R(P1, P2, P3, P4, P5)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5);
    } 
    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:  												
    EventDef(const EventDef&); 
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
struct EventDef<R(P1, P2, P3, P4, P5, P6)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6);
    }

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:  											
    EventDef(const EventDef&); 
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7);
    } 
    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&); 
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8);
    } 
    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 
    ~EventDef()
    {

    } 

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:  
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8, typename P9>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8, P9); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
    } 

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {
    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8, typename P9,typename P10>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10);
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    } 

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8, typename P9,typename P10, 
typename P11>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,P11); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
    } 

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
        }
        else
        {

        }
    } 

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8, typename P9,typename P10, 
typename P11, typename P12>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,P11, P12); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
    } 

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
        }
        else
        {

        }
    }

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8, typename P9,typename P10, 
typename P11, typename P12, typename P13>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,P11, P12, P13); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
    } 

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
        }
        else
        {

        }
    }

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8, typename P9,typename P10, 
typename P11, typename P12, typename P13, typename P14>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,P11, P12, P13, P14);
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
    } 

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
        }
        else
        {

        }
    }

    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};

template <typename R, typename P1, typename P2, typename P3, typename P4,typename P5, 
typename P6, typename P7, typename P8, typename P9,typename P10, 
typename P11, typename P12, typename P13, typename P14,typename P15>
struct EventDef<R(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)>
{
public: 
    typedef R (Object::*FuncPtr)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10,P11, P12, P13, P14, P15); 
    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15)
    {
        return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
    } 

    R Execute(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12, P13 p13, P14 p14, P15 p15)
    {
        if (Assigned())
        {
            return (m_pObj->*m_ptr)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
        }
        else
        {

        }
    }
    EventDef() : m_pObj(0), m_ptr(0)
    {

    } 

    ~EventDef()
    {

    }

    void Assign(Object* pObj, PENotify ptr)
    {
        m_pObj = pObj; 
        m_ptr = (FuncPtr)ptr;
    } 

    bool Assigned()
    {
        return m_pObj != 0;
    } 
private:
    EventDef(const EventDef&);
    EventDef& operator=(const EventDef&); 
    Object* m_pObj; 
    FuncPtr m_ptr;
};



//#include "MacroDef.h"

//#define TypeCount_0(n) ,
//
//#define NoParam
//#define HadParam ,
//ÀàÐÍÁÐ±í
//typename P0, typename P1 ...
//#define TypeList(n) IF(n, HadParam, NoParam) REPEAT(n, TypeNameDeclare, "")
//
//²ÎÊý¶¨Òåºê£¬ pn
//#define ParamDeclare(n, x) CONCAT(p, n)
//²ÎÊýÁÐ±í
//p0, p1, p2
//#define ParamList(n) REPEAT(n, ParamDeclare, "")
//
//²ÎÊýÀàÐÍ¶¨Òåºê£¬ pn
//#define ParamTypeDeclare(n, x) CONCAT(P, n)
//²ÎÊýÀàÐÍÁÐ±í
//p0, p1, p2
//#define ParamTypeList(n) REPEAT(n, ParamTypeDeclare, "")
//
//ÀàÐÍ£¬²ÎÊý±í¶¨Òå P0 p0
//#define FuncParamDeclare(n, x) CONCAT(P, n) CONCAT(p, n)
//²ÎÊýÁÐ±í
//p0, p1, p2
//#define FuncParamList(n) REPEAT(n, FuncParamDeclare, "")
//
//#define EventDeclare(n) \
//template<typename R TypeList(n)> \
//struct EventDef<R(ParamTypeList(n))> \
//{ \
//public: \
//    typedef R (Object::*FuncPtr)(ParamTypeList(n)); \
//    R operator()(FuncParamList(n)) \
//    { \
//        return (m_pObj->*m_ptr)(ParamList(n)); \
//    } \
//    R Execute(FuncParamList(n)) \
//    { \
//        if (Assigned()) \
//        {\
//    return (m_pObj->*m_ptr)(ParamList(n)); \
//        }\
//        else\
//        {\
//\
//        }\
//    } \
//    EventDef():m_pObj(NULL), m_ptr(NULL){} \
//    ~EventDef(){} \
//    void Assign(Object* pObj, PENotify ptr) \
//    { \
//        m_pObj = pObj; \
//        m_ptr = (FuncPtr)ptr; \
//    } \
//    bool Assigned() \
//    { \
//        return m_pObj != NULL; \
//    } \
//private: \
//    EmptyClassFunc(EventDef) \
//    Object* m_pObj; \
//    FuncPtr m_ptr; \
//} \
//
//    
//template<typename T>
//struct EventDef {};
//
//EventDeclare(0);
//EventDeclare(1);
//EventDeclare(2);
//EventDeclare(3);
//EventDeclare(4);
//EventDeclare(5);
//EventDeclare(6);
//EventDeclare(7);
//EventDeclare(8);
//EventDeclare(9);
//EventDeclare(10);
//EventDeclare(11);
//EventDeclare(12);
//EventDeclare(13);
//EventDeclare(14);
//EventDeclare(15);
//EventDeclare(16);
//EventDeclare(17);
//EventDeclare(18);
//EventDeclare(19);
//EventDeclare(20);
//EventDeclare(21);
//EventDeclare(22);
//EventDeclare(23);
//EventDeclare(24);
//EventDeclare(25);
//EventDeclare(26);
//EventDeclare(27);
//EventDeclare(28);
//EventDeclare(29);
//EventDeclare(30);
//EventDeclare(31);
//EventDeclare(32);
//EventDeclare(33);
//EventDeclare(34);
//EventDeclare(35);
//EventDeclare(36);
//EventDeclare(37);
//EventDeclare(38);
//EventDeclare(39);
//EventDeclare(40);
//EventDeclare(41);
//EventDeclare(42);
//EventDeclare(43);
//EventDeclare(44);
//EventDeclare(45);
//EventDeclare(46);
//EventDeclare(47);
//EventDeclare(48);
//EventDeclare(49);
//EventDeclare(50);
//EventDeclare(51);
//EventDeclare(52);
//EventDeclare(53);
//EventDeclare(54);
//EventDeclare(55);
//EventDeclare(56);
//EventDeclare(57);
//EventDeclare(58);
//EventDeclare(59);
//EventDeclare(60);
//EventDeclare(61);
//EventDeclare(62);
//EventDeclare(63);
//EventDeclare(64);
//EventDeclare(65);
//EventDeclare(66);
//EventDeclare(67);
//EventDeclare(68);
//EventDeclare(69);
//EventDeclare(70);
//EventDeclare(71);
//EventDeclare(72);
//EventDeclare(73);
//EventDeclare(74);
//EventDeclare(75);
//EventDeclare(76);
//EventDeclare(77);
//EventDeclare(78);
//EventDeclare(79);
//EventDeclare(80);
//EventDeclare(81);
//EventDeclare(82);
//EventDeclare(83);
//EventDeclare(84);
//EventDeclare(85);
//EventDeclare(86);
//EventDeclare(87);
//EventDeclare(88);
//EventDeclare(89);
//EventDeclare(90);
//EventDeclare(91);
//EventDeclare(92);
//EventDeclare(93);
//EventDeclare(94);
//EventDeclare(95);
//EventDeclare(96);
//EventDeclare(97);
//EventDeclare(98);
//EventDeclare(99);
//EventDeclare(100);
//EventDeclare(101);
//EventDeclare(102);
//EventDeclare(103);
//EventDeclare(104);
//EventDeclare(105);
//EventDeclare(106);
//EventDeclare(107);
//EventDeclare(108);
//EventDeclare(109);
//EventDeclare(110);
//EventDeclare(111);
//EventDeclare(112);
//EventDeclare(113);
//EventDeclare(114);
//EventDeclare(115);
//EventDeclare(116);
//EventDeclare(117);
//EventDeclare(118);
//EventDeclare(119);
//EventDeclare(120);
//EventDeclare(121);
//EventDeclare(122);
//EventDeclare(123);
//EventDeclare(124);
//EventDeclare(125);
//EventDeclare(126);
//EventDeclare(127);
//EventDeclare(128);
//EventDeclare(129);
//EventDeclare(130);
//EventDeclare(131);
//EventDeclare(132);
//EventDeclare(133);
//EventDeclare(134);
//EventDeclare(135);
//EventDeclare(136);
//EventDeclare(137);
//EventDeclare(138);
//EventDeclare(139);
//EventDeclare(140);
//EventDeclare(141);
//EventDeclare(142);
//EventDeclare(143);
//EventDeclare(144);
//EventDeclare(145);
//EventDeclare(146);
//EventDeclare(147);
//EventDeclare(148);
//EventDeclare(149);
//EventDeclare(150);
//EventDeclare(151);
//EventDeclare(152);
//EventDeclare(153);
//EventDeclare(154);
//EventDeclare(155);
//EventDeclare(156);
//EventDeclare(157);
//EventDeclare(158);
//EventDeclare(159);
//EventDeclare(160);
//EventDeclare(161);
//EventDeclare(162);
//EventDeclare(163);
//EventDeclare(164);
//EventDeclare(165);
//EventDeclare(166);
//EventDeclare(167);
//EventDeclare(168);
//EventDeclare(169);
//EventDeclare(170);
//EventDeclare(171);
//EventDeclare(172);
//EventDeclare(173);
//EventDeclare(174);
//EventDeclare(175);
//EventDeclare(176);
//EventDeclare(177);
//EventDeclare(178);
//EventDeclare(179);
//EventDeclare(180);
//EventDeclare(181);
//EventDeclare(182);
//EventDeclare(183);
//EventDeclare(184);
//EventDeclare(185);
//EventDeclare(186);
//EventDeclare(187);
//EventDeclare(188);
//EventDeclare(189);
//EventDeclare(190);
//EventDeclare(191);
//EventDeclare(192);
//EventDeclare(193);
//EventDeclare(194);
//EventDeclare(195);
//EventDeclare(196);
//EventDeclare(197);
//EventDeclare(198);
//EventDeclare(199);
//EventDeclare(200);
//EventDeclare(201);
//EventDeclare(202);
//EventDeclare(203);
//EventDeclare(204);
//EventDeclare(205);
//EventDeclare(206);
//EventDeclare(207);
//EventDeclare(208);
//EventDeclare(209);
//EventDeclare(210);
//EventDeclare(211);
//EventDeclare(212);
//EventDeclare(213);
//EventDeclare(214);
//EventDeclare(215);
//EventDeclare(216);
//EventDeclare(217);
//EventDeclare(218);
//EventDeclare(219);
//EventDeclare(220);
//EventDeclare(221);
//EventDeclare(222);
//EventDeclare(223);
//EventDeclare(224);
//EventDeclare(225);
//EventDeclare(226);
//EventDeclare(227);
//EventDeclare(228);
//EventDeclare(229);
//EventDeclare(230);
//EventDeclare(231);
//EventDeclare(232);
//EventDeclare(233);
//EventDeclare(234);
//EventDeclare(235);
//EventDeclare(236);
//EventDeclare(237);
//EventDeclare(238);
//EventDeclare(239);
//EventDeclare(240);
//EventDeclare(241);
//EventDeclare(242);
//EventDeclare(243);
//EventDeclare(244);
//EventDeclare(245);
//EventDeclare(246);
//EventDeclare(247);
//EventDeclare(248);
//EventDeclare(249);
//EventDeclare(250);


#endif