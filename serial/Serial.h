#ifndef _SERIAL_
#define _SERIAL_

#include <string.h>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <assert.h>
#include "DataTypeDef.h"

using namespace std;


#ifdef XML_ENCD_DECD
#include "KXML.h"
#include "ToStrFunc.h"
#endif

#define TYPE_NAME(T) (T::GetClassName())
#define GET_HOST(GetHostClassFunc) ((unsigned char*)this - GetHostClassFunc())
#define COMBINE_MAP(a, b) a, b

const int endian = 1;

#define is_bigendian() ( (*(char*) &endian) == 0 )
#define is_littlendbian() ( (*(char*) &endian) == 1 )
template<typename T>
T HTON(T VALUE);
template<>
unsigned short HTON(unsigned short VALUE);
template<>
unsigned long HTON(unsigned long VALUE);
template<>
unsigned int HTON(unsigned int VALUE);
template<>
unsigned long long HTON(unsigned long long VALUE);

template<typename T>
T NTOH(T VALUE);
template<>
unsigned short NTOH(unsigned short VALUE);
template<>
unsigned long NTOH(unsigned long VALUE);
template<>
unsigned int NTOH(unsigned int VALUE);
template<>
unsigned long long NTOH(unsigned long long VALUE);

#ifndef XML_ENCD_DECD

#define BEGIN_SERIAL(ClassName, ParentClassName, Key, MemoNote) \
    typedef ClassName zzz__Serial__Class; \
    typedef ParentClassName zzz__Serial__Parent__Class;\
    static const unsigned int ClassKey = Key; \
    bool zzz__bInited; \
    static const char* GetClassName() \
{ \
    return #ClassName; \
} \
    virtual unsigned int DoGetKey() \
{ \
    if (Key == 0) \
{ \
    return zzz__Serial__Parent__Class::DoGetKey();\
} \
        else \
{ \
    return Key; \
} \
} \
    static int zzz__Offset__Init() \
{	\
    return offsetof(ClassName, zzz__initstud); \
} \
    SerialInitStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__Init> zzz__initstud


#define SERIAL_ITEM(VarType, VarName, MemoNote) \
    VarType VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, char>::Encode(((zzz__Serial__Class*)p)->VarName, pData);\
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, char>::Decode(((zzz__Serial__Class*)p)->VarName, pData);\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    return SerialItem<VarType, char>::Size(((zzz__Serial__Class*)p)->VarName);\
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName> zzz__##VarName \

#define SERIAL_ITEM_D(VarType, VarName, DependExpr, MemoNote) \
    VarType VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    if (DependExpr) return SerialItem<VarType, char>::Encode(((zzz__Serial__Class*)p)->##VarName, pData); else return pData;\
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    if (DependExpr) return SerialItem<VarType, char>::Decode(((zzz__Serial__Class*)p)->##VarName, pData); else return pData;\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    if (DependExpr) return SerialItem<VarType, char>::Size(((zzz__Serial__Class*)p)->##VarName); else return pData; \
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName> zzz__##VarName \

#define SERIAL_ITEM_EX(VarType, VarName, SizeType, MemoNote) \
    VarType VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, SizeType>::Encode(((zzz__Serial__Class*)p)->VarName, pData); \
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, SizeType>::Decode(((zzz__Serial__Class*)p)->VarName, pData);\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    return SerialItem<VarType, SizeType>::Size(((zzz__Serial__Class*)p)->VarName); \
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName> zzz__##VarName \

#define SERIAL_ITEM_EX_D(VarType, VarName, SizeType, DependExpr, MemoNote) \
    VarType VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    if (DependExpr) return SerialItem<VarType, SizeType>::Encode(((zzz__Serial__Class*)p)->##VarName, pData); else return pData; \
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    if (DependExpr) return SerialItem<VarType, SizeType>::Decode(((zzz__Serial__Class*)p)->##VarName, pData);  else return pData; \
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    if (DependExpr) return SerialItem<VarType, SizeType>::Size(((zzz__Serial__Class*)p)->##VarName);  else return pData; \
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName> zzz__##VarName \

#define SERIAL_ARRAY(VarType, VarName, VarLen, MemoNote) \
    VarType VarName[VarLen]; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    return SerialArray<VarType, VarLen>::Encode(((zzz__Serial__Class*)p)->VarName, pData); \
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    return SerialArray<VarType, VarLen>::Decode(((zzz__Serial__Class*)p)->VarName, pData);\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    return SerialArray<VarType, VarLen>::Size(((zzz__Serial__Class*)p)->VarName); \
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName> zzz__##VarName \

#define SERIAL_SIZE_ARRAY(VarType, VarName, VarLen, SizeType, MemoNote) \
    vector<VarType> VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    for (unsigned int u32 = 0; u32 < ((zzz__Serial__Class*)p)->VarLen; ++u32)  \
    { \
        pData = SerialItem<VarType, SizeType>::Encode(((zzz__Serial__Class*)p)->##VarName[u32], pData); \
    } \
    return pData; \
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    for (unsigned int u32 = 0; u32 < ((zzz__Serial__Class*)p)->VarLen; ++u32)  \
    { \
        pData = SerialItem<VarType, SizeType>::Decode(((zzz__Serial__Class*)p)->##VarName[u32], pData); \
    } \
    return pData;\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    unsigned int uSize = 0; \
    for (unsigned int u32 = 0; u32 < ((zzz__Serial__Class*)p)->VarLen; ++u32)  \
    { \
        uSize += SerialItem<VarType, SizeType>::Size(((zzz__Serial__Class*)p)->##VarName[u32]); \
    } \
    return uSize;\
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName> zzz__##VarName \


#define END_SERIAL() \
    virtual char* DoSerial(char* pData) \
{\
    return zzz__Serial(TYPE_NAME(zzz__Serial__Class), zzz__Serial__Parent__Class::DoSerial(pData));\
}\
    virtual char* DoUnserial(char* pData)\
{\
    return zzz__Unserial(TYPE_NAME(zzz__Serial__Class), zzz__Serial__Parent__Class::DoUnserial(pData));\
}\
    virtual unsigned int DoSerialSize()\
{\
    return zzz__Size(TYPE_NAME(zzz__Serial__Class)) + zzz__Serial__Parent__Class::DoSerialSize();\
}\

#else

static const char* ARRAY_ITEM_NAME = "item";
static const char* XML_DOC_ATTR_NAME = "array_desc";

template<typename T>
void SaveXMLDoc(const char* szDir)
{
    XMLWriter xmlWriter;
    T::MakeXMLDoc(xmlWriter);
    string strFileName = szDir;
    strFileName += T::GetClassDesc();
    strFileName += "_doc.xml";
    xmlWriter.SaveAsUTF8File(strFileName.c_str());
}

template<typename T>
void SaveXMLDocSample(const char* szDir)
{
    XMLWriter xmlWriter;
    T t;
    t.EncodeToXML(xmlWriter);
    string strFileName = szDir;
    strFileName += T::GetClassDesc();
    strFileName += "_sample.xml";
    xmlWriter.SaveAsUTF8File(strFileName.c_str());
}

#define BEGIN_SERIAL(ClassName, ParentClassName, Key, MemoNote) \
    typedef ClassName zzz__Serial__Class; \
    typedef ParentClassName zzz__Serial__Parent__Class;\
    bool zzz__bInited; \
    static const unsigned int ClassKey = Key; \
    static const char* GetClassName() \
{ \
    return #ClassName; \
} \
    static const char* GetClassDesc() \
{\
    return MemoNote;\
}\
    virtual unsigned int DoGetKey() \
{ \
    if (Key == 0) \
{ \
    return zzz__Serial__Parent__Class::DoGetKey();\
} \
        else \
{ \
    return Key; \
} \
} \
    static int zzz__Offset__Init() \
{	\
    return offsetof(ClassName, zzz__initstud); \
} \
    SerialInitStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__Init> zzz__initstud


#define SERIAL_ITEM(VarType, VarName, MemoNote) \
    VarType VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, char>::Encode(((zzz__Serial__Class*)p)->##VarName, pData);\
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, char>::Decode(((zzz__Serial__Class*)p)->##VarName, pData);\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    return SerialItem<VarType, char>::Size(((zzz__Serial__Class*)p)->##VarName);\
} \
    static void zzz__SerialXML__##VarName(Serial* p, XMLWriter& xmlWriter) \
{ \
    return SerialItem<VarType, char>::EncodeXML(((zzz__Serial__Class*)p)->##VarName, xmlWriter, #VarName);\
} \
    static bool zzz__UnserialXML__##VarName(Serial* p, XMLNodeInfo& nodeInfo) \
{ \
    XMLNodeInfo* pNodeInfo = nodeInfo.FindNode(#VarName); \
    if (pNodeInfo != NULL) \
    { \
        SerialItem<VarType, char>::DecodeXML(((zzz__Serial__Class*)p)->##VarName, *pNodeInfo);\
        return true; \
    } \
    else \
    { \
        return false; \
    } \
} \
    static void zzz__MakeXMLDoc__##VarName(XMLWriter& xmlWriter) \
{ \
    SerialItem<VarType, char>::MakeXMLDoc(xmlWriter, #VarName, MemoNote);\
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName, zzz__Serial__Class::zzz__SerialXML__##VarName, zzz__Serial__Class::zzz__UnserialXML__##VarName, zzz__Serial__Class::zzz__MakeXMLDoc__##VarName> zzz__##VarName \

#define SERIAL_ITEM_EX(VarType, VarName, SizeType, MemoNote) \
    VarType VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, SizeType>::Encode(((zzz__Serial__Class*)p)->VarName, pData); \
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    return SerialItem<VarType, SizeType>::Decode(((zzz__Serial__Class*)p)->VarName, pData);\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    return SerialItem<VarType, SizeType>::Size(((zzz__Serial__Class*)p)->VarName); \
} \
    static void zzz__SerialXML__##VarName(Serial* p, XMLWriter& xmlWriter) \
{ \
    return SerialItem<VarType, SizeType>::EncodeXML(((zzz__Serial__Class*)p)->VarName, xmlWriter, #VarName);\
} \
    static bool zzz__UnserialXML__##VarName(Serial* p, XMLNodeInfo& nodeInfo) \
{ \
    XMLNodeInfo* pNodeInfo = nodeInfo.FindNode(#VarName); \
    if (pNodeInfo != NULL) \
    { \
    SerialItem<VarType, SizeType>::DecodeXML(((zzz__Serial__Class*)p)->VarName, *pNodeInfo);\
    return true; \
    } \
    else \
    { \
    return false; \
    } \
} \
    static void zzz__MakeXMLDoc__##VarName(XMLWriter& xmlWriter) \
{ \
    SerialItem<VarType, SizeType>::MakeXMLDoc(xmlWriter, #VarName, MemoNote);\
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName, zzz__Serial__Class::zzz__SerialXML__##VarName, zzz__Serial__Class::zzz__UnserialXML__##VarName, zzz__Serial__Class::zzz__MakeXMLDoc__##VarName> zzz__##VarName \

#define SERIAL_ARRAY(VarType, VarName, VarLen, MemoNote) \
    VarType VarName[VarLen]; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    return SerialArray<VarType, VarLen>::Encode(((zzz__Serial__Class*)p)->VarName, pData); \
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    return SerialArray<VarType, VarLen>::Decode(((zzz__Serial__Class*)p)->VarName, pData);\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    return SerialArray<VarType, VarLen>::Size(((zzz__Serial__Class*)p)->VarName); \
} \
    static void zzz__SerialXML__##VarName(Serial* p, XMLWriter& xmlWriter) \
{ \
    return SerialArray<VarType, VarLen>::EncodeXML(((zzz__Serial__Class*)p)->VarName, xmlWriter, #VarName);\
} \
    static bool zzz__UnserialXML__##VarName(Serial* p, XMLNodeInfo& nodeInfo) \
{ \
    XMLNodeInfo* pNodeInfo = nodeInfo.FindNode(#VarName); \
    if (pNodeInfo != NULL) \
    { \
    SerialArray<VarType, VarLen>::DecodeXML(((zzz__Serial__Class*)p)->VarName, *pNodeInfo);\
    return true; \
    } \
    else \
    { \
    return false; \
    } \
} \
    static void zzz__MakeXMLDoc__##VarName(XMLWriter& xmlWriter) \
{ \
    SerialArray<VarType, VarLen>::MakeXMLDoc(xmlWriter, #VarName, MemoNote);\
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName, zzz__Serial__Class::zzz__SerialXML__##VarName, zzz__Serial__Class::zzz__UnserialXML__##VarName, zzz__Serial__Class::zzz__MakeXMLDoc__##VarName> zzz__##VarName \

#define SERIAL_SIZE_ARRAY(VarType, VarName, VarLen, SizeType, MemoNote) \
    vector<VarType> VarName; \
    static int zzz__Offset__##VarName() \
{\
    return offsetof(zzz__Serial__Class, zzz__##VarName); \
} \
    static char* zzz__Serial__##VarName(Serial* p, char* pData) \
{ \
    for (unsigned int u32 = 0; u32 < ((zzz__Serial__Class*)p)->VarLen; ++u32)  \
    { \
    pData = SerialItem<VarType, SizeType>::Encode(((zzz__Serial__Class*)p)->##VarName[u32], pData); \
    } \
    return pData; \
} \
    static char* zzz__Unserial__##VarName(Serial* p, char* pData) \
{ \
    for (unsigned int u32 = 0; u32 < ((zzz__Serial__Class*)p)->VarLen; ++u32)  \
    { \
    pData = SerialItem<VarType, SizeType>::Decode(((zzz__Serial__Class*)p)->##VarName[u32], pData); \
    } \
    return pData;\
} \
    static unsigned int zzz__Size__##VarName(Serial* p) \
{ \
    unsigned int uSize = 0; \
    for (unsigned int u32 = 0; u32 < ((zzz__Serial__Class*)p)->VarLen; ++u32)  \
    { \
    uSize += SerialItem<VarType, SizeType>::Size(((zzz__Serial__Class*)p)->##VarName[u32]); \
    } \
    return uSize;\
} \
    static void zzz__SerialXML__##VarName(Serial* p, XMLWriter& xmlWriter) \
{ \
    return SerialItem<VarType, SizeType>::EncodeXML(((zzz__Serial__Class*)p)->##VarName, xmlWriter, #VarName);\
} \
    static bool zzz__UnserialXML__##VarName(Serial* p, XMLNodeInfo& nodeInfo) \
{ \
    XMLNodeInfo* pNodeInfo = nodeInfo.FindNode(#VarName); \
    if (pNodeInfo != NULL) \
    { \
    SerialItem<VarType, SizeType>::DecodeXML(((zzz__Serial__Class*)p)->##VarName, *pNodeInfo);\
    return true; \
    } \
    else \
    { \
    return false; \
    } \
} \
    static void zzz__MakeXMLDoc__##VarName(XMLWriter& xmlWriter) \
{ \
    SerialItem<VarType, SizeType>::MakeXMLDoc(xmlWriter, #VarName, MemoNote);\
} \
    SerialStud<zzz__Serial__Class, zzz__Serial__Class::zzz__Offset__##VarName, zzz__Serial__Class::zzz__Serial__##VarName, zzz__Serial__Class::zzz__Unserial__##VarName, zzz__Serial__Class::zzz__Size__##VarName, zzz__Serial__Class::zzz__SerialXML__##VarName, zzz__Serial__Class::zzz__UnserialXML__##VarName, zzz__Serial__Class::zzz__MakeXMLDoc__##VarName> zzz__##VarName \

#define END_SERIAL() \
    virtual char* DoSerial(char* pData) \
{\
    return zzz__Serial(TYPE_NAME(zzz__Serial__Class), zzz__Serial__Parent__Class::DoSerial(pData));\
}\
    virtual char* DoUnserial(char* pData)\
{\
    return zzz__Unserial(TYPE_NAME(zzz__Serial__Class), zzz__Serial__Parent__Class::DoUnserial(pData));\
}\
    virtual unsigned int DoSerialSize()\
{\
    return zzz__Size(TYPE_NAME(zzz__Serial__Class)) + zzz__Serial__Parent__Class::DoSerialSize();\
}\
    virtual void DoEncodeString(XMLWriter& xmlWriter) \
{\
    zzz__Serial__Parent__Class::DoEncodeString(xmlWriter);\
    zzz__SerialXML(TYPE_NAME(zzz__Serial__Class), xmlWriter); \
} \
    virtual bool DoDecodeString(XMLNodeInfo& xmlNodeInfo) \
{\
    if (zzz__Serial__Parent__Class::DoDecodeString(xmlNodeInfo)) \
    { \
        return zzz__UnserialXML(TYPE_NAME(zzz__Serial__Class), xmlNodeInfo); \
    } \
    else \
    { \
        return false; \
    } \
} \
    virtual void DoMakeXMLDoc(XMLWriter& xmlWriter) \
{ \
    zzz__Serial__Parent__Class::DoMakeXMLDoc(xmlWriter); \
    zzz__MakeXMLDoc(TYPE_NAME(zzz__Serial__Class), xmlWriter); \
} \
static void MakeXMLDoc(string& str)\
{\
    XMLWriter xmlWriter; \
    zzz__Serial__Class::MakeXMLDoc(xmlWriter); \
    str += xmlWriter.GetXML(); \
}\
static void MakeXMLDoc(XMLWriter& xmlWriter)\
{\
    zzz__Serial__Class t; \
    xmlWriter.BeginWriteNode(format("data desc=\"%s\"", zzz__Serial__Class::GetClassDesc()).c_str());\
    t.DoBeforeMakeXMLDoc(xmlWriter); \
    t.DoMakeXMLDoc(xmlWriter); \
    t.DoAfterMakeXMLDoc(xmlWriter); \
    xmlWriter.EndWriteNode("data");\
} \

#endif

template<typename T, typename U>
class IsSame
{
public:
    static const bool value = false;
};

template<typename T>
class IsSame<T, T>
{
public:
    static const bool value = true;
};

template<typename T>
class IsClass
{
private:
    template<typename U>
    static char Test(int U::*);

    template<typename U>
    static int Test(...);
public:
    static const bool value = sizeof(Test<T>(0)) == 1;
};

template <typename Base, typename Derived, bool = (IsClass<Base>::value && IsClass<Derived>::value)>
class IsBaseOf
{
    template <typename T>
    static char Test(Derived, T);
    static int Test(Base, int);

    struct Conv
    {
        operator Derived();
        operator Base() const;
    };
public:
    static const bool value = sizeof(Test(Conv(), 0)) == 1;
};

template <typename Base, typename Derived>
class IsBaseOf<Base, Derived, false>
{
public:
    static const bool value = IsSame<Base, Derived>::value;
};

class Serial
{
public:
    static map<string, vector<char* (*)(Serial*, char*)> > zzz_mapSerialFunc;
    static map<string, vector<char* (*)(Serial*, char*)> > zzz_mapUnserialFunc;
    static map<string, vector<unsigned int (*)(Serial*)> > zzz_mapSizeFunc;
#ifdef XML_ENCD_DECD
    static map<string, vector<void (*)(Serial*, XMLWriter&)> > zzz_mapSerialXMLFunc;
    static map<string, vector<bool (*)(Serial*, XMLNodeInfo&)> > zzz_mapUnserialXMLFunc;
    static map<string, vector<void (*)(XMLWriter&)>> zzz_mapMakeXMLDocFunc;
#endif

    static bool zzz__Inited(const char* szClassName)
    {
        return Serial::zzz_mapSerialFunc.find(szClassName) != Serial::zzz_mapSerialFunc.end();
    }

    template<typename T>
    static void zzz__AddSerialFunc(char* (*SerialFunc)(Serial*, char*))
    {
        map<string, vector<char* (*)(Serial*, char*)> >::iterator iter = zzz_mapSerialFunc.find(TYPE_NAME(T));
        if (iter != zzz_mapSerialFunc.end())
        {
            iter->second.push_back(SerialFunc);
        }
    }

    template<typename T>
    static void zzz__AddUnserialFunc(char* (*UnserialFunc)(Serial*, char*))
    {
        map<string, vector<char* (*)(Serial*, char*)> >::iterator iter = zzz_mapUnserialFunc.find(TYPE_NAME(T));
        if (iter != zzz_mapUnserialFunc.end())
        {
            iter->second.push_back(UnserialFunc);
        }
    }

    template<typename T>
    static void zzz__AddSizeFunc(unsigned int (*SizeFunc)(Serial*))
    {
        map<string, vector<unsigned int (*)(Serial*)> >::iterator iter = zzz_mapSizeFunc.find(TYPE_NAME(T));
        if (iter != zzz_mapSizeFunc.end())
        {
            iter->second.push_back(SizeFunc);
        }
    }

    char* zzz__Serial(const char* szClassName, char* pData)
    {
        map<string, vector<char* (*)(Serial*, char*)> >::iterator iter = Serial::zzz_mapSerialFunc.find(szClassName);
        if (iter != Serial::zzz_mapSerialFunc.end())
        {
            for (vector<char* (*)(Serial*, char*)>::iterator iterLoop = iter->second.begin(); iterLoop != iter->second.end(); ++iterLoop)
            {
                pData = (*iterLoop)(this, pData);
            }
        }
        return pData;
    }

    char* zzz__Unserial(const char* szClassName, char* pData)
    {
        map<string, vector<char* (*)(Serial*, char*)> >::iterator iter = Serial::zzz_mapUnserialFunc.find(szClassName);
        if (iter != Serial::zzz_mapUnserialFunc.end())
        {
            for (vector<char* (*)(Serial*, char*)>::iterator iterLoop = iter->second.begin(); iterLoop != iter->second.end(); ++iterLoop)
            {
                pData = (*iterLoop)(this, pData);
            }
        }

        return pData;
    }

    unsigned int zzz__Size(const char* szClassName)
    {
        unsigned int ulSize = 0;
        map<string, vector<unsigned int (*)(Serial*)> >::iterator iter = Serial::zzz_mapSizeFunc.find(szClassName);
        if (iter != Serial::zzz_mapSizeFunc.end())
        {
            for (vector<unsigned int (*)(Serial*)>::iterator iterLoop = iter->second.begin(); iterLoop != iter->second.end(); ++iterLoop)
            {
                ulSize += (*iterLoop)(this);
            }
        }
        return ulSize;
    }

    virtual char* DoSerial(char* pData)
    {
        return pData;
    }

    virtual char* DoAttachSerial(char* pData)
    {
        return pData;
    }

    virtual char* BeforeSerial(char* pData)
    {
        return pData;
    }

    virtual char* AfterSerial(char* pData)
    {
        return pData;
    }

    virtual char* DoUnserial(char* pData)
    {
        return pData;
    }

    virtual char* DoAttachUnserial(char* pData)
    {
        return pData;
    }

    virtual char* BeforeUnserial(char* pData)
    {
        return pData;
    }

    virtual char* AfterUnserial(char* pData)
    {
        return pData;
    }

    virtual unsigned int DoSerialSize()
    {
        return 0;
    }

    virtual unsigned int DoAttachSerialSize()
    {
        return 0;
    }

    virtual unsigned int DoGetKey()
    {
        return 0;
    }

#ifdef XML_ENCD_DECD
    template<typename T>
    static void zzz__AddSerialXMLFunc(void (*SerialXML)(Serial*, XMLWriter&))
    {
        map<string, vector<void (*)(Serial*, XMLWriter&)> >::iterator iter = zzz_mapSerialXMLFunc.find(TYPE_NAME(T));
        if (iter != zzz_mapSerialXMLFunc.end())
        {
            iter->second.push_back(SerialXML);
        }
    }

    template<typename T>
    static void zzz__AddUnserialXMLFunc(bool (*UnserialXML)(Serial*, XMLNodeInfo&))
    {
        map<string, vector<bool (*)(Serial*, XMLNodeInfo&)> >::iterator iter = zzz_mapUnserialXMLFunc.find(TYPE_NAME(T));
        if (iter != zzz_mapUnserialXMLFunc.end())
        {
            iter->second.push_back(UnserialXML);
        }
    }

    template<typename T>
    static void zzz__AddMakeXMLDocFunc(void (*MakeXMLDoc)(XMLWriter&))
    {
        map<string, vector<void (*)(XMLWriter&)> >::iterator iter = zzz_mapMakeXMLDocFunc.find(TYPE_NAME(T));
        if (iter != zzz_mapMakeXMLDocFunc.end())
        {
            iter->second.push_back(MakeXMLDoc);
        }
    }

    void zzz__SerialXML(const char* szClassName, XMLWriter& xmlWrite)
    {
        map<string, vector<void (*)(Serial*, XMLWriter&)>>::iterator iter = Serial::zzz_mapSerialXMLFunc.find(szClassName);
        if (iter != Serial::zzz_mapSerialXMLFunc.end())
        {
            for (vector<void (*)(Serial*, XMLWriter&)>::iterator iterLoop = iter->second.begin(); iterLoop != iter->second.end(); ++iterLoop)
            {
                (*iterLoop)(this, xmlWrite);
            }
        }
    }

    bool zzz__UnserialXML(const char* szClassName, XMLNodeInfo& nodeInfo)
    {
        bool bSuccess = false;
        map<string, vector<bool (*)(Serial*, XMLNodeInfo&)>>::iterator iter = Serial::zzz_mapUnserialXMLFunc.find(szClassName);
        if (iter != Serial::zzz_mapUnserialXMLFunc.end())
        {
            vector<bool (*)(Serial*, XMLNodeInfo&)>& mapLoop = iter->second;
            bSuccess = true;
            for (vector<bool (*)(Serial*, XMLNodeInfo&)>::iterator iterLoop = mapLoop.begin(); iterLoop != mapLoop.end(); ++iterLoop)
            {
                if (!(*iterLoop)(this, nodeInfo))
                {
                    bSuccess = false;
                    break;
                }
            }
        }

        return bSuccess;
    }

    void zzz__MakeXMLDoc(const char* szClassName, XMLWriter& xmlWrite)
    {
        map<string, vector<void (*)(XMLWriter&)> >::iterator iter = zzz_mapMakeXMLDocFunc.find(szClassName);
        if (iter != Serial::zzz_mapMakeXMLDocFunc.end())
        {
            for (vector<void (*)(XMLWriter&)>::iterator iterLoop = iter->second.begin(); iterLoop != iter->second.end(); ++iterLoop)
            {
                (*iterLoop)(xmlWrite);
            }
        }
    }

    virtual void DoEncodeString(XMLWriter& xmlWriter)
    {
        (xmlWriter);
    }

    virtual void DoEncodeAttachString(XMLWriter& xmlWriter)
    {
        (xmlWriter);
    }

    virtual void BeforeEncodeString(XMLWriter& xmlWriter)
    {
        (xmlWriter);
    }

    virtual void AfterEncodeString(XMLWriter& xmlWriter)
    {
        (xmlWriter);
    }

    virtual bool DoDecodeString(XMLNodeInfo& xmlNodeInfo)
    {
        (xmlNodeInfo);
        return true;
    }

    virtual bool DoDecodeAttachString(XMLNodeInfo& xmlNodeInfo)
    {
        (xmlNodeInfo);
        return true;
    }

    virtual bool CheckNodeInfo(XMLNodeInfo& xmlNodeInfo)
    {
        (xmlNodeInfo);
        return false;
    }

    virtual void DoAfterMakeXMLDoc(XMLWriter& xmlWriter)
    {
        (xmlWriter);
    }

    virtual void DoBeforeMakeXMLDoc(XMLWriter& xmlWriter)
    {
        (xmlWriter);
    }

    virtual void DoMakeXMLDoc(XMLWriter& xmlWriter)
    {
        (xmlWriter);
    }
#endif

    char* m_pHeader;
    unsigned int m_ulSerialSize;
public:
    Serial()
        :m_pBuf(NULL), m_ulBufLen(0)
    {

    }

    virtual ~Serial()
    {
        if (m_pBuf != NULL)
        {
            delete []m_pBuf;
        }
    }

    Serial(const Serial& src)
        :m_pBuf(NULL), m_ulBufLen(0)
    {
        *this = src;
    }

    Serial& operator=(const Serial& src)
    {
        if (this != &src)
        {
            if (m_pBuf != NULL)
            {
                delete m_pBuf;
                m_pBuf = NULL;
            }

            m_ulBufLen = src.m_ulBufLen;
            if (m_ulBufLen > 0)
            {
                m_pBuf = new char[m_ulBufLen];
                memcpy(m_pBuf, src.m_pBuf, m_ulBufLen);
            }
        }
        return *this;
    }

    bool Encode(char* pData, unsigned int& ulSize)
    {
        assert(pData);
        m_ulSerialSize = GetSerialSize();
        //缓冲区是不是不够
        if (ulSize >= m_ulSerialSize)
        {
            m_pHeader = pData;
            try
            {
                //中间任何过程都有可能抛出异常，直接失败了
                char* pNewData = BeforeSerial(m_pHeader);
                pNewData = DoSerial(pNewData);
                pNewData = DoAttachSerial(pNewData);
                pNewData = AfterSerial(pNewData);
                unsigned int ulNewSize = (unsigned int)(pNewData - m_pHeader);
                if (ulSize >= ulNewSize)
                {
                    ulSize = ulNewSize;
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (...)  //暂时不细分异常
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    char* EncodeWithoutBuf(unsigned int& ulSize)
    {
        m_ulSerialSize = GetSerialSize();
        if (m_ulSerialSize > m_ulBufLen)
        {
            delete []m_pBuf;
            m_pBuf = new char[m_ulSerialSize];
            m_ulBufLen = m_ulSerialSize;
        }
        m_pHeader = m_pBuf;

        try
        {
            char* pNewData = BeforeSerial(m_pHeader);
            pNewData = DoSerial(pNewData);
            pNewData = DoAttachSerial(pNewData);
            pNewData = AfterSerial(pNewData);
            ulSize = (unsigned int)(pNewData - m_pHeader);
            return m_pHeader;
        }
        catch (...)
        {
            return NULL;
        }
    }

    bool Decode(const char* pData, unsigned int& ulSize)
    {
        assert(pData);
        assert(ulSize > 0);

        try
        {
            m_pHeader = const_cast<char*>(pData);
            m_ulSerialSize = ulSize;
            char* pNewData = BeforeUnserial(m_pHeader);
            pNewData = DoUnserial(pNewData);
            pNewData = DoAttachUnserial(pNewData);
            pNewData = AfterUnserial(pNewData);
            unsigned int ulNewSize = (unsigned int)(pNewData - m_pHeader);
            return ulSize == ulNewSize;
        }
        catch (...)
        {
            return false;
        }
    }

    bool Decode(const string& strData)
    {
        unsigned int ulSize = strData.size();
        return Decode(strData.c_str(), ulSize);
    }

    unsigned int GetSerialSize()
    {
        return DoSerialSize() + DoAttachSerialSize();
    }

    unsigned int GetKey()
    {
        return DoGetKey();
    }

#ifdef XML_ENCD_DECD
    void EncodeToXML(string& str)
    {
        XMLWriter xmlWriter;
        EncodeToXML(xmlWriter);
        str += xmlWriter.GetXML();
    }

    void EncodeToXML(XMLWriter& xmlWriter)
    {
        xmlWriter.Clear();
        BeforeEncodeString(xmlWriter);
        DoEncodeString(xmlWriter);
        DoEncodeAttachString(xmlWriter);
        AfterEncodeString(xmlWriter);
    }

    string EncodeToXMLClip()
    {
        XMLWriter xmlWriter;
        EncodeToXML(xmlWriter);
        return xmlWriter.GetXMLNoHead();
    }

    bool DecodeFromXML(const string& str)
    {
        XMLNodeInfo nodeInfo;
        ParseXML(str, nodeInfo);
        return DecodeFromXML(nodeInfo);
    }

    bool DecodeFromXML(XMLNodeInfo& nodeInfo)
    {
        if (CheckNodeInfo(nodeInfo))
        {
            return DoDecodeString(nodeInfo) && DoDecodeAttachString(nodeInfo);
        }
        else
        {
            return false;
        }
    }

    static void MakeXMLDoc(string& str)
    {
        XMLWriter xmlWriter;
        Serial::MakeXMLDoc(xmlWriter);
        str += xmlWriter.GetXML();
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter)
    {
        Serial t;
        xmlWriter.BeginWriteNode("data name=\"Serial\"");
        t.DoBeforeMakeXMLDoc(xmlWriter);
        t.DoMakeXMLDoc(xmlWriter);
        t.DoAfterMakeXMLDoc(xmlWriter);
        xmlWriter.EndWriteNode("data");
    }
#endif

private:
    char* m_pBuf;
    unsigned int m_ulBufLen;
};

template<typename T, typename SizeType, bool = IsBaseOf<Serial, T>::value>
class SerialItem
{
public:
    static char* Encode(Serial& t, char* pData)
    {
        return t.DoSerial(pData);           
    }

    static char* Decode(Serial& t, char* pData)
    {
        return t.DoUnserial(pData);
    }

    static unsigned int Size(Serial& t)
    {
        return t.DoSerialSize();
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(Serial& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.BeginWriteNode(szNodeName);
        t.DoEncodeString(xmlWriter);
        xmlWriter.EndWriteNode(szNodeName);
    }

    static void DecodeXML(Serial& t, XMLNodeInfo& nodeInfo)
    {
        t.DoDecodeString(nodeInfo);
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        xmlWriter.BeginWriteNode(szNodeName, XML_DOC_ATTR_NAME, szMemo);
        T::MakeXMLDoc(xmlWriter);
        xmlWriter.EndWriteNode(szNodeName);
    }
#endif
};

template<typename T, typename SizeType>
class SerialItem<T, SizeType, false>
{
public:
    static char* Encode(const T& t, char* pData)
    {
        *((T*)pData) = t;
        return pData + sizeof(T);
    }

    static char* Decode(T& t, char* pData)
    {
        t = *((T*)pData);
        return pData + sizeof(T);
    }

    static unsigned int Size(const T& t)
    {
        //(t);
        return sizeof(T);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(T& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        ToXML(t, xmlWriter, szNodeName);
    }

    static void DecodeXML(T& t, XMLNodeInfo& nodeInfo)
    {
        FromXML(t, nodeInfo);
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        MakeItemXMLDoc<T>(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename T, typename SizeType>
class SerialItem<T*, SizeType, false>
{
public:
    static char* Encode(T*& t, char* pData)
    {
        return SerialItem<T, SizeType>::Encode(*t, pData);
    }

    static char* Decode(T*& t, char* pData)
    {
        t = new T;
        return SerialItem<T, SizeType>::Decode(*t, pData);
    }

    static unsigned int Size(T*& t)
    {
        return SerialItem<T, SizeType>::Size(*t);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(T* t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        SerialItem<T, SizeType>::EncodeXML(*t, xmlWriter, szNodeName);
    }

    static void DecodeXML(T*& t, XMLNodeInfo& nodeInfo)
    {
        T* pt = new T;
        SerialItem<T, SizeType>::DecodeXML(*pt, nodeInfo);
        *t = *pt;
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        SerialItem<T, SizeType>::MakeXMLDoc(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename SizeType>
class SerialItem<unsigned short, SizeType, false>
{
public:
    static char* Encode(const unsigned short& t, char* pData)
    {
        *((unsigned short*)pData) = HTON(t);
        return pData + sizeof(unsigned short);
    }

    static char* Decode(unsigned short& t, char* pData)
    {
        t = NTOH(*((unsigned short*)pData));
        return pData + sizeof(unsigned short);
    }

    static unsigned int Size(const unsigned short& t)
    {
        (t);
        return sizeof(unsigned short);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(unsigned short& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        ToXML(t, xmlWriter, szNodeName);
    }

    static void DecodeXML(unsigned short& t, XMLNodeInfo& nodeInfo)
    {
        FromXML(t, nodeInfo);
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        MakeItemXMLDoc<unsigned short>(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename SizeType>
class SerialItem<unsigned int, SizeType, false>
{
public:
    static char* Encode(const unsigned int& t, char* pData)
    {
        *((unsigned int*)pData) = HTON(t);
        return pData + sizeof(unsigned int);
    }

    static char* Decode(unsigned int& t, char* pData)
    {
        t = NTOH(*((unsigned int*)pData));
        return pData + sizeof(unsigned int);
    }

    static unsigned int Size(const unsigned int& t)
    {
        //(t);
        return sizeof(unsigned int);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(unsigned int& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        ToXML(t, xmlWriter, szNodeName);
    }

    static void DecodeXML(unsigned int& t, XMLNodeInfo& nodeInfo)
    {
        FromXML(t, nodeInfo);
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        MakeItemXMLDoc<unsigned int>(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename SizeType>
class SerialItem<unsigned long long, SizeType, false>
{
public:
    static char* Encode(const unsigned long long& t, char* pData)
    {
        *((unsigned long long*)pData) = HTON(t);
        return pData + sizeof(unsigned long long);
    }

    static char* Decode(unsigned long long& t, char* pData)
    {
        t = NTOH(*((unsigned long long*)pData));
        return pData + sizeof(unsigned long long);
    }

    static unsigned int Size(const unsigned long long& t)
    {
        //(t);
        return sizeof(unsigned long long);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(unsigned long long& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        ToXML(t, xmlWriter, szNodeName);
    }

    static void DecodeXML(unsigned long long& t, XMLNodeInfo& nodeInfo)
    {
        FromXML(t, nodeInfo);
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        MakeItemXMLDoc<unsigned long long>(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename SizeType>
class SerialItem<unsigned short*, SizeType, false>
{
public:
    static char* Encode(unsigned short*& t, char* pData)
    {
        return SerialItem<unsigned short, SizeType>::Encode(*t, pData);
    }

    static char* Decode(unsigned short*& t, char* pData)
    {
        t = new unsigned short;
        return SerialItem<unsigned short, SizeType>::Decode(*t, pData);
    }

    static unsigned int Size(unsigned short*& t)
    {
        return SerialItem<unsigned short, SizeType>::Size(*t);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(unsigned short* t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        SerialItem<unsigned short, SizeType>::EncodeXML(*t, xmlWriter, szNodeName);
    }

    static void DecodeXML(unsigned short*& t, XMLNodeInfo& nodeInfo)
    {
        unsigned short* pt = new unsigned short;
        SerialItem<unsigned short, SizeType>::DecodeXML(*pt, nodeInfo);
        *t = *pt;
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        SerialItem<unsigned short, SizeType>::MakeXMLDoc(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename SizeType>
class SerialItem<unsigned int*, SizeType, false>
{
public:
    static char* Encode(unsigned int*& t, char* pData)
    {
        return SerialItem<unsigned int, SizeType>::Encode(*t, pData);
    }

    static char* Decode(unsigned int*& t, char* pData)
    {
        t = new unsigned int;
        return SerialItem<unsigned int, SizeType>::Decode(*t, pData);
    }

    static unsigned int Size(unsigned int*& t)
    {
        return SerialItem<unsigned int, SizeType>::Size(*t);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(unsigned int* t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        SerialItem<unsigned int, SizeType>::EncodeXML(*t, xmlWriter, szNodeName);
    }

    static void DecodeXML(unsigned int*& t, XMLNodeInfo& nodeInfo)
    {
        unsigned int* pt = new unsigned int;
        SerialItem<unsigned int, SizeType>::DecodeXML(*pt, nodeInfo);
        *t = *pt;
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        SerialItem<unsigned int, SizeType>::MakeXMLDoc(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename SizeType>
class SerialItem<unsigned long long*, SizeType, false>
{
public:
    static char* Encode(unsigned long long*& t, char* pData)
    {
        return SerialItem<unsigned long long, SizeType>::Encode(*t, pData);
    }

    static char* Decode(unsigned long long*& t, char* pData)
    {
        t = new unsigned long long;
        return SerialItem<unsigned long long, SizeType>::Decode(*t, pData);
    }

    static unsigned int Size(unsigned long long*& t)
    {
        return SerialItem<unsigned long long, SizeType>::Size(*t);
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(unsigned long long* t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        SerialItem<unsigned long long, SizeType>::EncodeXML(*t, xmlWriter, szNodeName);
    }

    static void DecodeXML(unsigned long long*& t, XMLNodeInfo& nodeInfo)
    {
        unsigned long long* pt = new unsigned long long;
        SerialItem<unsigned long long, SizeType>::DecodeXML(*pt, nodeInfo);
        *t = *pt;
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        SerialItem<unsigned long long, SizeType>::MakeXMLDoc(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename SizeType>
class SerialItem<string, SizeType, false>
{
public:
    static char* Encode(string& t, char* pData)
    {
        pData = SerialItem<SizeType, U8>::Encode((SizeType)t.size(), pData);
        t.copy(pData, t.size());
        return pData + t.size();
    }

    static char* Decode(string& t, char* pData)
    {
        SizeType usSize;
        pData = SerialItem<SizeType, U8>::Decode(usSize, pData);
        t.assign(pData, usSize);
        return pData + usSize;
    }

    static unsigned int Size(string& t)
    {
        return (unsigned int )(t.size() + sizeof(SizeType));
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(string& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.WriteNode(szNodeName, t.c_str());
    }

    static void DecodeXML(string& t, XMLNodeInfo& nodeInfo)
    {
        t = nodeInfo.strVal;
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        MakeItemXMLDoc<string>(xmlWriter, szNodeName, szMemo);
    }
#endif
};

template<typename T, typename SizeType>
class SerialItem<vector<T>, SizeType, false>
{
public:
    static char* Encode(vector<T>& t, char* pData)
    {
        pData = SerialItem<SizeType, U8>::Encode((SizeType)t.size(), pData);
        for (typename vector<T>::size_type i = 0; i < t.size(); ++i)
        {
            pData = SerialItem<T, SizeType>::Encode(t[i], pData);
        }
        return pData;
    }

    static char* Decode(vector<T>& t, char* pData)
    {
        SizeType usSize;
        pData = SerialItem<SizeType, U8>::Decode(usSize, pData);
        for (int i = 0; i < usSize; ++i)
        {
            T temp;
            pData = SerialItem<T, SizeType>::Decode(temp, pData);
            t.push_back(temp);
        }
        return pData;
    }

    static unsigned int Size(vector<T>& t)
    {
        unsigned int ulSize = sizeof(SizeType);
		for (typename::vector<T>::size_type i = 0; i < t.size(); ++i)
        {
            ulSize += SerialItem<T, SizeType>::Size(t[i]);
        }
        return ulSize;
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(vector<T>& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.BeginWriteNode(szNodeName);
        for (U32 u32 = 0; u32 < t.size(); ++u32)
        {
            SerialItem<T, SizeType>::EncodeXML(t[u32], xmlWriter, ARRAY_ITEM_NAME);
        }
        xmlWriter.EndWriteNode(szNodeName);
    }

    static void DecodeXML(vector<T>& t, XMLNodeInfo& nodeInfo)
    {
        for (list<XMLNodeInfo*>::iterator iter = nodeInfo.lstChildNode.begin(); iter != nodeInfo.lstChildNode.end(); ++iter)
        {
            T temp;
            SerialItem<T, SizeType>::DecodeXML(temp, *(*iter));
            t.push_back(temp);
        }
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        string str_1 = format("%s_1", szMemo);
        string str_n = format("%s_n", szMemo);

        xmlWriter.BeginWriteNode(szNodeName, XML_DOC_ATTR_NAME, szMemo);
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_1.c_str());
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_n.c_str());
        xmlWriter.EndWriteNode(szNodeName);
    }
#endif
};

template<typename T, typename SizeType>
class SerialItem<list<T>, SizeType, false>
{
public:
    static char* Encode(list<T>& t, char* pData)
    {
        pData = SerialItem<SizeType, U8>::Encode((SizeType)t.size(), pData);
        for (typename list<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            pData = SerialItem<T, SizeType>::Serial(*iter, pData);
        }
        return pData;
    }

    static char* Decode(list<T>& t, char* pData)
    {
        SizeType usSize;
        pData = SerialItem<SizeType, U8>::Decode(usSize, pData);
        for (int i = 0; i < usSize; ++i)
        {
            T temp;
            pData = SerialItem<T, SizeType>::UnSerial(temp, pData);
            t.push_back(temp);
        }
        return pData;
    }

    static unsigned int Size(list<T>& t)
    {
        unsigned int ulSize = sizeof(SizeType);
        for (typename list<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            ulSize += SerialItem<T, SizeType>::Size(*iter);
        }
        return ulSize;
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(list<T>& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.BeginWriteNode(szNodeName);
        for (list<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            SerialItem<T, SizeType>::EncodeXML(*iter, xmlWriter, ARRAY_ITEM_NAME);
        }
        xmlWriter.EndWriteNode(szNodeName);
    }

    static void DecodeXML(list<T>& t, XMLNodeInfo& nodeInfo)
    {
        for (list<XMLNodeInfo*>::iterator iter = nodeInfo.lstChildNode.begin(); iter != nodeInfo.lstChildNode.end(); ++iter)
        {
            t temp;
            SerialItem<t, SizeType>::DecodeXML(t, *(*iter));
            t.push_back(temp);
        }
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        string str_1 = format("%s_1", szMemo);
        string str_n = format("%s_n", szMemo);

        xmlWriter.BeginWriteNode(szNodeName, XML_DOC_ATTR_NAME, szMemo);
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_1);
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_n);
        xmlWriter.EndWriteNode(szNodeName);
    }
#endif
};

template<typename T, typename SizeType>
class SerialItem<set<T>, SizeType, false>
{
public:
    static char* Encode(set<T>& t, char* pData)
    {                  
        pData = SerialItem<SizeType, U8>::Encode((SizeType)t.size(), pData);
        for (typename set<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            pData = SerialItem<T, SizeType>::Encode(*iter, pData);
        }
        return pData;
    }

    static char* Decode(set<T>& t, char* pData)
    {
        SizeType usSize;
        pData = SerialItem<SizeType, U8>::Decode(usSize, pData);
        for (int i = 0; i < usSize; ++i)
        {
            T temp;
            pData = SerialItem<T, SizeType>::Decode(temp, pData);
            t.insert(temp);
        }
        return pData;
    }

    static unsigned int Size(set<T>& t)
    {
        unsigned int ulSize = sizeof(SizeType);
        for (typename set<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            ulSize += SerialItem<T, SizeType>::Size(*iter);
        }
        return ulSize;
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(set<T>& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.BeginWriteNode(szNodeName);
        for (set<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            SerialItem<T, SizeType>::EncodeXML(*iter, xmlWriter, "list");
        }
        xmlWriter.EndWriteNode(szNodeName);
    }

    static void DecodeXML(set<T>& t, XMLNodeInfo& nodeInfo)
    {
        for (list<XMLNodeInfo*>::iterator iter = nodeInfo.lstChildNode.begin(); iter != nodeInfo.lstChildNode.end(); ++iter)
        {
            T temp;
            SerialItem<T, SizeType>::DecodeXML(temp, *(*iter));
            t.insert(temp);
        }
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        string str_1 = format("%s_1", szMemo);
        string str_n = format("%s_n", szMemo);

        xmlWriter.BeginWriteNode(szNodeName, XML_DOC_ATTR_NAME, szMemo);
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_1.c_str());
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_n.c_str());
        xmlWriter.EndWriteNode(szNodeName);
    }
#endif
};

template<typename T, typename U, typename SizeType>
class SerialItem<map<T, U>, SizeType, false>
{
public:
    static char* Encode(map<T, U>& t, char* pData)
    {                  
        pData = SerialItem<SizeType, U8>::Encode((SizeType)t.size(), pData);
        for (typename map<T, U>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            pData = SerialItem<T, SizeType>::Encode(iter->first, pData);
            pData = SerialItem<U, SizeType>::Encode(iter->second, pData);
        }
        return pData;
    }

    static char* Decode(map<T, U>& t, char* pData)
    {
        SizeType usSize;
        pData = SerialItem<SizeType, U8>::Decode(usSize, pData);
        for (int i = 0; i < usSize; ++i)
        {
            T tempT;
            U tempU;
            pData = SerialItem<T, SizeType>::Decode(tempT, pData);
            pData = SerialItem<U, SizeType>::Decode(tempU, pData);
            t.insert(make_pair(tempT, tempU));
        }
        return pData;
    }

    static unsigned int Size(map<T, U>& t)
    {
        unsigned int ulSize = sizeof(SizeType);
        for (typename map<T, U>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            ulSize += SerialItem<T, SizeType>::Size(iter->first);
            ulSize += SerialItem<U, SizeType>::Size(iter->second);
        }
        return ulSize;
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(map<T, U>& t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.BeginWriteNode(szNodeName);
        for (map<T, U>::iterator iter = t.begin(); iter != t.end(); ++iter)
        {
            xmlWriter.BeginWriteNode("pair");
            T* pF = const_cast<T*>(&iter->first);
            SerialItem<T, SizeType>::EncodeXML(*pF, xmlWriter, "first");
            SerialItem<U, SizeType>::EncodeXML(iter->second, xmlWriter, "second");
            xmlWriter.EndWriteNode("pair");
        }
        xmlWriter.EndWriteNode(szNodeName);
    }

    static void DecodeXML(map<T, U>& t, XMLNodeInfo& nodeInfo)
    {
        for (list<XMLNodeInfo*>::iterator iter = nodeInfo.lstChildNode.begin(); iter != nodeInfo.lstChildNode.end(); ++iter)
        {
            XMLNodeInfo* pNode = *iter;
            if (pNode->lstChildNode.size() == 2)
            {
                XMLNodeInfo* pNodeFirst = *(pNode->lstChildNode.begin());
                XMLNodeInfo* pNodeSecond = *(pNode->lstChildNode.begin()++);
                T ttemp;
                U utemp;
                SerialItem<T, SizeType>::DecodeXML(ttemp, *pNodeFirst);
                SerialItem<U, SizeType>::DecodeXML(utemp, *pNodeSecond);
                t.insert(make_pair(ttemp, utemp));
            }
        }
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        string str_1 = format("%s_1", szMemo);
        string str_n = format("%s_n", szMemo);
        string str_first = format("%s_first", szMemo);
        string str_second = format("%s_second", szMemo);

        xmlWriter.BeginWriteNode(szNodeName, XML_DOC_ATTR_NAME, szMemo);

        xmlWriter.BeginWriteNode(ARRAY_ITEM_NAME, szNodeName, str_1.c_str());
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, "first", str_first.c_str());
        SerialItem<U, U8>::MakeXMLDoc(xmlWriter, "second", str_second.c_str());
        xmlWriter.EndWriteNode(ARRAY_ITEM_NAME);
        xmlWriter.BeginWriteNode(ARRAY_ITEM_NAME, szNodeName, str_n.c_str());
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, "first", str_first.c_str());
        SerialItem<U, U8>::MakeXMLDoc(xmlWriter, "second", str_second.c_str());
        xmlWriter.EndWriteNode(ARRAY_ITEM_NAME);

        xmlWriter.EndWriteNode(szNodeName);
    }
#endif
};

//array
template<typename T, int SIZE>
class SerialArray
{
public:
    static char* Encode(T* t, char* pData)
    {
        for (int ul = 0; ul < SIZE; ++ul)
        {
            pData = SerialItem<T, unsigned char>::Encode(t[ul], pData);
        }
        return pData;
    }

    static char* Decode(T* t, char* pData)
    {
        for (int ul = 0; ul < SIZE; ++ul)
        {
            pData = SerialItem<T, unsigned char>::Decode(t[ul], pData);
        }
        return pData;
    }

    static unsigned int Size(T* t)
    {
        unsigned int ulSize = 0;
        for (int ul = 0; ul < SIZE; ++ul)
        {
            ulSize += SerialItem<T, unsigned char>::Size(t[ul]);
        }
        return ulSize;
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(T* t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.BeginWriteNode(szNodeName);
        for (U32 u32 = 0; u32 < SIZE; ++u32)
        {
            SerialItem<T, unsigned char>::EncodeXML(t[u32], xmlWriter, "array");
        }
        xmlWriter.EndWriteNode(szNodeName);
    }

    static void DecodeXML(T* t, XMLNodeInfo& nodeInfo)
    {
        if (nodeInfo.lstChildNode.size() == SIZE)
        {
            U32 u32 = 0;
            for (list<XMLNodeInfo*>::iterator iter = nodeInfo.lstChildNode.begin(); iter != nodeInfo.lstChildNode.end(); ++iter)
            {
                XMLNodeInfo* pNode = *iter;
                SerialItem<T, unsigned char>::DecodeXML(t[u32], *pNode);
                ++u32;
            }
        }
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        string str_1 = format("%s_1", szMemo);
        string str_n = format("%s_n", szMemo);

        xmlWriter.BeginWriteNode(szNodeName, XML_DOC_ATTR_NAME, szMemo);
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_1);
        SerialItem<T, U8>::MakeXMLDoc(xmlWriter, ARRAY_ITEM_NAME, str_n);
        xmlWriter.EndWriteNode(szNodeName);
    }
#endif
};

template<int SIZE>
class SerialArray<char, SIZE>
{
public:
    static char* Encode(char* t, char* pData)
    {
        memcpy(pData, t, SIZE);
        return pData + SIZE;
    }

    static char* Decode(char* t, char* pData)
    {
        memcpy(t, pData, SIZE);
        return pData + SIZE;
    }

    static unsigned int Size(char* t)
    {
        //(t);
        return SIZE;
    }

#ifdef XML_ENCD_DECD
    static void EncodeXML(char* t, XMLWriter& xmlWriter, const char* szNodeName)
    {
        xmlWriter.BeginWriteNode(szNodeName);
        for (U32 u32 = 0; u32 < SIZE; ++u32)
        {
            SerialItem<char, unsigned char>::EncodeXML(t[u32], xmlWriter, "array");
        }
        xmlWriter.EndWriteNode(szNodeName);
    }

    static void DecodeXML(char* t, XMLNodeInfo& nodeInfo)
    {
        if (nodeInfo.lstChildNode.size() == SIZE)
        {
            U32 u32 = 0;
            for (list<XMLNodeInfo*>::iterator iter = nodeInfo.lstChildNode.begin(); iter != nodeInfo.lstChildNode.end(); ++iter)
            {
                XMLNodeInfo* pNode = *iter;
                SerialItem<char, unsigned char>::DecodeXML(t[u32], *pNode);
                ++u32;
            }
        }
    }

    static void MakeXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
    {
        MakeItemXMLDoc<char>(xmlWriter, szNodeName, szMemo);
    }
#endif
};

#ifndef XML_ENCD_DECD

template<typename T, int (*GetHostClassFunc)()>
class SerialInitStud
{
public:
    SerialInitStud()
    {
        if (Serial::zzz_mapSerialFunc.find(TYPE_NAME(T)) == Serial::zzz_mapSerialFunc.end())
        {
            Serial::zzz_mapSerialFunc.insert(make_pair(TYPE_NAME(T), vector<char* (*)(Serial*, char*)>()));
            Serial::zzz_mapUnserialFunc.insert(make_pair(TYPE_NAME(T), vector<char* (*)(Serial*, char*)>()));
            Serial::zzz_mapSizeFunc.insert(make_pair(TYPE_NAME(T), vector<unsigned int (*)(Serial*)>()));
            ((T*)GET_HOST(GetHostClassFunc))->zzz__bInited = false;
        }
        else
        {
            ((T*)GET_HOST(GetHostClassFunc))->zzz__bInited = true;
        }
    }
};

template<typename T, int (*GetHostClassFunc)(), char* (*SerialFunc)(Serial*, char*), 
  char* (*UnserialFunc)(Serial*, char*), unsigned int (*SizeFunc)(Serial*)>
class SerialStud
{
public:
    SerialStud()
    {
        if (!((T*)GET_HOST(GetHostClassFunc))->zzz__bInited)
        {
            Serial::zzz__AddSerialFunc<T>(SerialFunc);
            Serial::zzz__AddUnserialFunc<T>(UnserialFunc);
            Serial::zzz__AddSizeFunc<T>(SizeFunc);
        }
    }
};

#else

template<typename T, int (*GetHostClassFunc)()>
class SerialInitStud
{
public:
    SerialInitStud()
    {
        if (Serial::zzz_mapSerialFunc.find(TYPE_NAME(T)) == Serial::zzz_mapSerialFunc.end())
        {
            Serial::zzz_mapSerialFunc.insert(make_pair(TYPE_NAME(T), vector<char* (*)(Serial*, char*)>()));
            Serial::zzz_mapUnserialFunc.insert(make_pair(TYPE_NAME(T), vector<char* (*)(Serial*, char*)>()));
            Serial::zzz_mapSizeFunc.insert(make_pair(TYPE_NAME(T), vector<unsigned int (*)(Serial*)>()));
            Serial::zzz_mapSerialXMLFunc.insert(make_pair(TYPE_NAME(T), vector<void (*)(Serial*, XMLWriter&)>()));
            Serial::zzz_mapUnserialXMLFunc.insert(make_pair(TYPE_NAME(T), vector<bool (*)(Serial*, XMLNodeInfo&)>()));
            Serial::zzz_mapMakeXMLDocFunc.insert(make_pair(TYPE_NAME(T), vector<void (*)(XMLWriter&)>()));
            ((T*)GET_HOST(GetHostClassFunc))->zzz__bInited = false;
        }
        else
        {
            ((T*)GET_HOST(GetHostClassFunc))->zzz__bInited = true;
        }
    }
};

template<typename T, int (*GetHostClassFunc)(), char* (*SerialFunc)(Serial*, char*), 
char* (*UnserialFunc)(Serial*, char*), unsigned int (*SizeFunc)(Serial*), void (*SerialXMLFunc)(Serial*, XMLWriter&),
bool (*UnserialXMLFunc)(Serial*, XMLNodeInfo&), void (*MakeXMLDocFunc)(XMLWriter&)>
class SerialStud
{
public:
    SerialStud()
    {
        if (!((T*)GET_HOST(GetHostClassFunc))->zzz__bInited)
        {
            Serial::zzz__AddSerialFunc<T>(SerialFunc);
            Serial::zzz__AddUnserialFunc<T>(UnserialFunc);
            Serial::zzz__AddSizeFunc<T>(SizeFunc);
            Serial::zzz__AddSerialXMLFunc<T>(SerialXMLFunc);
            Serial::zzz__AddUnserialXMLFunc<T>(UnserialXMLFunc);
            Serial::zzz__AddMakeXMLDocFunc<T>(MakeXMLDocFunc);
        }
    }
};

#endif

#endif
