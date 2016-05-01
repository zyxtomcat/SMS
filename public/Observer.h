#ifndef _OBSERVER_
#define _OBSERVER_

#include <map>

using namespace std;

#define MemPtrToU32(pFunc) (*(unsigned long*)&pFunc)
#define U32ToMemPtr(u32, FuncPTRType) (*((FuncPTRType*)((unsigned long*)(&u32))))

template<typename T>
class Observer;

template<typename T0>
class Observer<void(T0)>
{
public:
    template<typename T>
    struct DeleHandle 
    {
    public:
        typedef void (T::*FuncPTR)(T0 t);
        static void Handle(void* pT, unsigned long ulFuncPtr, T0 t0)
        {
            FuncPTR pFunc = U32ToMemPtr(ulFuncPtr, FuncPTR);
            (((T*)(pT))->*pFunc)(t0);
        }
    };
public:
    Observer()
    {

    }

    ~Observer()
    {
        Clear();
    }

    void Update(T0 t)
    {
        for (map<unsigned long long, InternalInfo>::iterator iter = m_mapWatchList.begin(); iter != m_mapWatchList.end(); ++iter)
        {
            InternalInfo& ii = iter->second;
            ii.pHandle(ii.ptrInfo.pT, ii.ptrInfo.ulFuncPtr, t);
        }
    }

    template<typename T>
    void Register(T* pT, void (T::*pFunc)(T0))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        ii.pHandle = &DeleHandle<T>::Handle;
        m_mapWatchList.insert(make_pair(ii.ullKey, ii));
    }

    template<typename T>
    void Unregister(T* pT, void (T::*pFunc)(T0))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        m_mapWatchList.erase(ii.ullKey);
    }

    void Clear()
    {
        m_mapWatchList.clear();
    }
private:
    struct InternalInfo
    {
        union 
        {
            struct
            {
                void* pT;
                unsigned long ulFuncPtr;
            } ptrInfo;
            unsigned long long ullKey;
        };

        void (*pHandle)(void* pT, unsigned long ulFuncPtr, T0 t0);
    };

    map<unsigned long long, InternalInfo> m_mapWatchList;
};

template<typename T0, typename T1>
class Observer<void(T0, T1)>
{
public:
    template<typename T>
    struct DeleHandle 
    {
    public:
        typedef void (T::*FuncPTR)(T0 t0, T1 t1);
        static void Handle(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1)
        {
            FuncPTR pFunc = U32ToMemPtr(ulFuncPtr, FuncPTR);
            (((T*)(pT))->*pFunc)(t0, t1);
        }
    };
public:
    Observer()
    {

    }

    ~Observer()
    {
        Clear();
    }

    void Update(T0 t0, T1 t1)
    {
        for (map<unsigned long long, InternalInfo>::iterator iter = m_mapWatchList.begin(); iter != m_mapWatchList.end(); ++iter)
        {
            InternalInfo& ii = iter->second;
            ii.pHandle(ii.ptrInfo.pT, ii.ptrInfo.ulFuncPtr, t0, t1);
        }
    }

    template<typename T>
    void Register(T* pT, void (T::*pFunc)(T0, T1))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        ii.pHandle = &DeleHandle<T>::Handle;
        m_mapWatchList.insert(make_pair(ii.ullKey, ii));
    }

    template<typename T>
    void Unregister(T* pT, void (T::*pFunc)(T0, T1))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        m_mapWatchList.erase(ii.ullKey);
    }

    void Clear()
    {
        m_mapWatchList.clear();
    }
private:
    struct InternalInfo
    {
        union 
        {
            struct
            {
                void* pT;
                unsigned long ulFuncPtr;
            } ptrInfo;
            unsigned long long ullKey;
        };

        void (*pHandle)(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1);
    };

    map<unsigned long long, InternalInfo> m_mapWatchList;
};

template<typename T0, typename T1, typename T2>
class Observer<void(T0, T1, T2)>
{
public:
    template<typename T>
    struct DeleHandle 
    {
    public:
        typedef void (T::*FuncPTR)(T0 t0, T1 t1, T2 t2);
        static void Handle(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1, T2 t2)
        {
            FuncPTR pFunc = U32ToMemPtr(ulFuncPtr, FuncPTR);
            (((T*)(pT))->*pFunc)(t0, t1, t2);
        }
    };
public:
    Observer()
    {

    }

    ~Observer()
    {
        Clear();
    }

    void Update(T0 t0, T1 t1, T2 t2)
    {
        for (map<unsigned long long, InternalInfo>::iterator iter = m_mapWatchList.begin(); iter != m_mapWatchList.end(); ++iter)
        {
            InternalInfo& ii = iter->second;
            ii.pHandle(ii.ptrInfo.pT, ii.ptrInfo.ulFuncPtr, t0, t1, t2);
        }
    }

    template<typename T>
    void Register(T* pT, void (T::*pFunc)(T0, T1, T2))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        ii.pHandle = &DeleHandle<T>::Handle;
        m_mapWatchList.insert(make_pair(ii.ullKey, ii));
    }

    template<typename T>
    void Unregister(T* pT, void (T::*pFunc)(T0, T1, T2))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        m_mapWatchList.erase(ii.ullKey);
    }

    void Clear()
    {
        m_mapWatchList.clear();
    }
private:
    struct InternalInfo
    {
        union 
        {
            struct
            {
                void* pT;
                unsigned long ulFuncPtr;
            } ptrInfo;
            unsigned long long ullKey;
        };

        void (*pHandle)(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1, T2);
    };

    map<unsigned long long, InternalInfo> m_mapWatchList;
};

template<typename T0, typename T1, typename T2, typename T3>
class Observer<void(T0, T1, T2, T3)>
{
public:
    template<typename T>
    struct DeleHandle 
    {
    public:
        typedef void (T::*FuncPTR)(T0 t0, T1 t1, T2 t2, T3 t3);
        static void Handle(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1, T2 t2, T3 t3)
        {
            FuncPTR pFunc = U32ToMemPtr(ulFuncPtr, FuncPTR);
            (((T*)(pT))->*pFunc)(t0, t1, t2, t3);
        }
    };
public:
    Observer()
    {

    }

    ~Observer()
    {
        Clear();
    }

    void Update(T0 t0, T1 t1, T2 t2, T3 t3)
    {
        for (map<unsigned long long, InternalInfo>::iterator iter = m_mapWatchList.begin(); iter != m_mapWatchList.end(); ++iter)
        {
            InternalInfo& ii = iter->second;
            ii.pHandle(ii.ptrInfo.pT, ii.ptrInfo.ulFuncPtr, t0, t1, t2, t3);
        }
    }

    template<typename T>
    void Register(T* pT, void (T::*pFunc)(T0, T1, T2, T3))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        ii.pHandle = &DeleHandle<T>::Handle;
        m_mapWatchList.insert(make_pair(ii.ullKey, ii));
    }

    template<typename T>
    void Unregister(T* pT, void (T::*pFunc)(T0, T1, T2, T3))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        m_mapWatchList.erase(ii.ullKey);
    }

    void Clear()
    {
        m_mapWatchList.clear();
    }
private:
    struct InternalInfo
    {
        union 
        {
            struct
            {
                void* pT;
                unsigned long ulFuncPtr;
            } ptrInfo;
            unsigned long long ullKey;
        };

        void (*pHandle)(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1, T2 t2, T3 t3);
    };

    map<unsigned long long, InternalInfo> m_mapWatchList;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
class Observer<void(T0, T1, T2, T3, T4)>
{
public:
    template<typename T>
    struct DeleHandle 
    {
    public:
        typedef void (T::*FuncPTR)(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4);
        static void Handle(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1, T2 t2, T3 t3, T4 t4)
        {
            FuncPTR pFunc = U32ToMemPtr(ulFuncPtr, FuncPTR);
            (((T*)(pT))->*pFunc)(t0, t1, t2, t3, t4);
        }
    };
public:
    Observer()
    {

    }

    ~Observer()
    {
        Clear();
    }

    void Update(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4)
    {
        for (map<unsigned long long, InternalInfo>::iterator iter = m_mapWatchList.begin(); iter != m_mapWatchList.end(); ++iter)
        {
            InternalInfo& ii = iter->second;
            ii.pHandle(ii.ptrInfo.pT, ii.ptrInfo.ulFuncPtr, t0, t1, t2, t3, t4);
        }
    }

    template<typename T>
    void Register(T* pT, void (T::*pFunc)(T0, T1, T2, T3, T4))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        ii.pHandle = &DeleHandle<T>::Handle;
        m_mapWatchList.insert(make_pair(ii.ullKey, ii));
    }

    template<typename T>
    void Unregister(T* pT, void (T::*pFunc)(T0, T1, T2, T3, T4))
    {
        InternalInfo ii = {0};
        ii.ptrInfo.pT = pT;
        ii.ptrInfo.ulFuncPtr = MemPtrToU32(pFunc);
        m_mapWatchList.erase(ii.ullKey);
    }

    void Clear()
    {
        m_mapWatchList.clear();
    }
private:
    struct InternalInfo
    {
        union 
        {
            struct
            {
                void* pT;
                unsigned long ulFuncPtr;
            } ptrInfo;
            unsigned long long ullKey;
        };

        void (*pHandle)(void* pT, unsigned long ulFuncPtr, T0 t0, T1 t1, T2 t2, T3 t3, T4 t4);
    };

    map<unsigned long long, InternalInfo> m_mapWatchList;
};

#endif