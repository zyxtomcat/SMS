#ifndef _SERIAL_CLASS_MANAGER_
#define _SERIAL_CLASS_MANAGER_

#include <map>

using namespace std;

template<typename T>
class SerialClassManager;

template<typename T, typename U>
class Delegating 
{
public:
    Delegating()
    {
        SerialClassManager<T>::__register(U::ClassKey, &(Delegating::Create));
    }

    static T* Create()
    {
        return static_cast<T*>(new U);
    }
};

template<typename T>
class SerialClassManager
{
public:
    typedef T* (*PCreateInstance)();

    template<typename U>
    static void RegistClassFunc()
    {
        Delegating<T, U> x;
    }

    static T* GetClassInstance(unsigned int type)
    {
        typename map<unsigned int, PCreateInstance>::iterator iter = ms_mapList.find(type);
        if (iter != ms_mapList.end())        
        {
            return (iter->second)();
        }
        else
        {
            return NULL;
        }
    }
private:
    static void __register(unsigned int type, PCreateInstance p)
    {
        if (CheckRegisted(type))
        {
            throw "class registed";
        }
        else
        {
            ms_mapList.insert(make_pair(type, p));
        }
    }

    static bool CheckRegisted(unsigned int type)
    {
        if (type > 0)
        {
            return ms_mapList.find(type) != ms_mapList.end();
        }
        else
        {
            return true;
        }
    }

    static map<unsigned int, PCreateInstance> ms_mapList;

    template<typename T1, typename U> 
    friend class Delegating;
};

template<typename T>
map<unsigned int, typename SerialClassManager<T>::PCreateInstance> SerialClassManager<T>::ms_mapList;

#endif
