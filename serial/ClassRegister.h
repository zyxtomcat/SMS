#ifndef _CLASS_REGISTER_
#define _CLASS_REGISTER_

#include "SerialClassManager.h"
#include "MacroRepeat.h"

#define __DEC(order) order
#define _DEC(order) __DEC(DEC_##order)
#define DEC(order) _DEC(order) 
#define DEC_LINE DEC(__LINE__)

#define _Concat(a, b) a##b
#define Concat(a, b) _Concat(a, b)

#define RUN_REG_CLASS(HostClass, ClassList) RegistClass<HostClass, ClassList>::Do() 
#define REG_CLASS_BEGIN(ClassListName) typedef Append<NullType, NullType>::NewList Concat(ClassListName, __LINE__)
#define REG_CLASS(ClassListName, NewType) typedef Append<Concat(ClassListName, DEC_LINE), NewType>::NewList Concat(ClassListName, __LINE__)
#define REG_CLASS_END(ClassListName) typedef Concat(ClassListName, DEC_LINE) ClassListName

template<typename T, typename U>
struct ClassList
{
    typedef T Head;
    typedef U Tail;
};

struct NullType;

template<typename List, typename T>
struct Append;

template<>
struct Append<NullType, NullType>
{
    typedef NullType NewList;
};

template<typename T>
struct Append<NullType, T>
{
    typedef ClassList<T, NullType> NewList;
};

template<typename T, typename U>
struct Append<NullType, ClassList<T, U> >
{
    typedef ClassList<T, U> NewList;
};

template<typename T, typename U, typename V>
struct Append<ClassList<T, U>, V>
{
    typedef ClassList<T, typename Append<U, V>::NewList> NewList;
};


template<typename T, typename TypeList>
struct RegistClass
{
    static void Do()
    {
        T::template RegistClassFunc<typename TypeList::Head>();
        RegistClass<T, typename TypeList::Tail>::Do();//迭代，元编程
    }
};

template<typename T>
struct RegistClass<T, NullType>
{
    static void Do()		//迭代结束
    {
    }
};
 
#endif
