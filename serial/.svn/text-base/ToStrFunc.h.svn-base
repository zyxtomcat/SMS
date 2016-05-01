#ifndef _TOSTR_FUNC_
#define _TOSTR_FUNC_

#include "DataTypeDef.h"
#include "PublicFunction.h"
#include "KXML.h"

using namespace std;

template<typename T>
inline void ToXML(const T& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    (t);
    xmlWriter.WriteNode(szNodeName, "没有实现的数据");
}

template<typename T>
inline void FromXML(T& t, XMLNodeInfo& xmlNodeInfo)
{
    (t);
    (xmlNodeInfo);
    //t = xmlNodeInfo.GetAttri("val");
}

template<typename T>
inline void MakeItemXMLDoc(XMLWriter& xmlWriter, const char* szNodeName, const char* szMemo)
{
    xmlWriter.WriteNode(szNodeName, szMemo);
}

template<typename T>
inline bool FromXMLByName(T& t, XMLNodeInfo& xmlNodeInfo, const char* szNodeName)
{
    XMLNodeInfo* pNode = xmlNodeInfo.FindNode(szNodeName);
    if (pNode != NULL)
    {
        FromXML(t, *pNode);
        return true;
    }
    else
    {
        return false;
    }
}

template<>
inline void ToXML(const string& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    xmlWriter.WriteNode(szNodeName, t.c_str());
}

template<>
inline void ToXML(const bool& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    xmlWriter.WriteNode(szNodeName, t ? "1" : "0");
}

template<>
inline void ToXML(const unsigned long long& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, _ui64toa(t, szBuf, 10));
}

template<>
inline void ToXML(const long long& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, _i64toa(t, szBuf, 10));
}

template<>
inline void ToXML(const unsigned long& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, _ui64toa(t, szBuf, 10));
}

template<>
inline void ToXML(const long& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, _i64toa(t, szBuf, 10));
}

template<>
inline void ToXML(const unsigned int& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, _ui64toa(t, szBuf, 10));
}

template<>
inline void ToXML(const int& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, _i64toa(t, szBuf, 10));
}

template<>
inline void ToXML(const unsigned short& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, itoa(t, szBuf, 10));
}

template<>
inline void ToXML(const short& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, itoa(t, szBuf, 10));
}

template<>
inline void ToXML(const unsigned char& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, itoa(t, szBuf, 10));
}

template<>
inline void ToXML(const char& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    char szBuf[32];
    xmlWriter.WriteNode(szNodeName, itoa(t, szBuf, 10));
}

template<>
inline void ToXML(const Datetime& t, XMLWriter& xmlWriter, const char* szNodeName)
{
    xmlWriter.WriteNode(szNodeName, FormatDatetime(t).c_str());
}

template<>
inline void ToXML(const double& t, XMLWriter& xmlWriter, const char* szNodeName)
{
	char szBuf[32];
	sprintf(szBuf, "%012.8f", t);
	xmlWriter.WriteNode(szNodeName, szBuf);
}

template<>
inline void FromXML(char& t, XMLNodeInfo& xmlNodeInfo)
{
    t = (char)atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(unsigned char& t, XMLNodeInfo& xmlNodeInfo)
{
    t = (unsigned char)atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(short& t, XMLNodeInfo& xmlNodeInfo)
{
    t = (short)atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(unsigned short& t, XMLNodeInfo& xmlNodeInfo)
{
    t = (unsigned short)atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(int& t, XMLNodeInfo& xmlNodeInfo)
{
    t = atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(unsigned int& t, XMLNodeInfo& xmlNodeInfo)
{
    t = atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(long& t, XMLNodeInfo& xmlNodeInfo)
{
    t = atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(unsigned long& t, XMLNodeInfo& xmlNodeInfo)
{
    t = atoi(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(unsigned long long& t, XMLNodeInfo& xmlNodeInfo)
{
    t = _atoi64(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(long long& t, XMLNodeInfo& xmlNodeInfo)
{
    t = _atoi64(xmlNodeInfo.strVal.c_str());
}

template<>
inline void FromXML(bool& t, XMLNodeInfo& xmlNodeInfo)
{
    t = _atoi64(xmlNodeInfo.strVal.c_str()) != 0;
}

template<>
inline void FromXML(string& t, XMLNodeInfo& xmlNodeInfo)
{
    t = xmlNodeInfo.strVal;
}


#endif