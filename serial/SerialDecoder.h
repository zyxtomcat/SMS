#ifndef _SERIAL_DECODER_
#define _SERIAL_DECODER_

#include "SerialClassManager.h"

//返回值 0表示数据不完全，或者不对
//        sintUsed=0 表示数据不对
//        sintUsed=-1 表示数据不完全
//返回值 >0表示数据对，sintUsed表示该数据长度
//unsigned short TerminalProtocol::CheckData(const char* pData, unsigned long ulLen, SINT& sintUsed)

enum DecodeResult
{
    DR_SUCCESS,
    DR_BAD_DATA,
    DR_UNCOMPLETE,
    DR_KEY_NOT_REGISTER,
};

template<typename T>
struct DecoderInfo
{
    DecodeResult drCode;
    const char* pData;
    unsigned long ulLen;
    T* pT;
};

struct PreDecoderInfo
{
    DecodeResult drCode;
    const char* pData;
    unsigned long ulLen;
    unsigned int usKey;
};

template<typename T>
class SerialDecoder
{
public:
    static void Decode(const char* szBuf, unsigned long ulLen, list<DecoderInfo<T> >& lstDecoderInfo)
    {
        DecoderInfo<T> di;
        ClearDecoderInfo(di);
        const char* pCurrent = szBuf;
        unsigned long ulLeaveLen = ulLen;
        while (ulLeaveLen >= T::MIN_SERIAL_LENGTH)
        {
            unsigned long ulUsedLen = 0;
            T* pT = Decode(pCurrent, ulLeaveLen, ulUsedLen);
            //success
            if (pT != NULL)
            {
                //first is bad data 
                if (di.ulLen != 0)
                {
                    di.drCode = DR_BAD_DATA;
                    lstDecoderInfo.push_back(di);
                    ClearDecoderInfo(di);
                }
                di.drCode = DR_SUCCESS;
                di.pData = pCurrent;
                di.pT = pT;
                di.ulLen = ulUsedLen;
                lstDecoderInfo.push_back(di);
                ClearDecoderInfo(di);
                ulLeaveLen -= ulUsedLen;
                pCurrent += ulUsedLen;
            }
            else if (ulUsedLen >= T::MIN_SERIAL_LENGTH)  //class not register,包头尾检查都无问题
            {
                di.drCode = DR_KEY_NOT_REGISTER;
                di.pData = pCurrent;
                di.pT = NULL;
                di.ulLen = ulUsedLen;
                lstDecoderInfo.push_back(di);
                ClearDecoderInfo(di);
                ulLeaveLen -= ulUsedLen;
                pCurrent += ulUsedLen;
            }
            else if (ulUsedLen > 0)   //Data not complete
            {
                //first is bad data 
                if (di.ulLen != 0)
                {
                    di.drCode = DR_BAD_DATA;
                    lstDecoderInfo.push_back(di);
                    ClearDecoderInfo(di);
                }
                di.drCode = DR_UNCOMPLETE;
                di.pData = pCurrent;
                di.pT = pT;
                di.ulLen = ulLeaveLen;
                ulLeaveLen = 0;
                lstDecoderInfo.push_back(di);
                ClearDecoderInfo(di);

                break;
            }
            else//坏数据，向前移动一个字节继续解析
            {
                if (di.ulLen > 0)
                {
                    ++di.ulLen;
                }
                else
                {
                    di.drCode = DR_BAD_DATA;
                    di.pData = pCurrent;
                    di.pT = NULL;
                    di.ulLen = 1;
                }

                --ulLeaveLen;
                ++pCurrent;
            }
        }

        if (di.ulLen != 0)
        {
            di.drCode = DR_BAD_DATA;
            lstDecoderInfo.push_back(di);
            ClearDecoderInfo(di);
        }

        if (ulLeaveLen > 0)
        {
            di.drCode = DR_UNCOMPLETE;
            di.pData = pCurrent;
            di.pT = NULL;
            di.ulLen = ulLeaveLen;
            lstDecoderInfo.push_back(di);
        }
    }

    static void PreDecode(const char* szBuf, unsigned long ulLen, list<PreDecoderInfo>& lstPreDecoderInfo)
    {
        PreDecoderInfo pdi;
        memset(&pdi, 0, sizeof(PreDecoderInfo));

        const char* pCurrent = szBuf;
        unsigned long ulLeaveLen = ulLen;
        while (ulLeaveLen >= T::MIN_SERIAL_LENGTH)
        {
            int nUsedLen = 0;
            unsigned int usType = T::CheckData(pCurrent, ulLeaveLen, nUsedLen);
            if (usType > 0)
            {
                //first is bad data 
                if (pdi.ulLen != 0)
                {
                    pdi.drCode = DR_BAD_DATA;
                    lstPreDecoderInfo.push_back(pdi);
                    memset(&pdi, 0, sizeof(PreDecoderInfo));
                }
                pdi.drCode = DR_SUCCESS;
                pdi.pData = pCurrent;
                pdi.ulLen = nUsedLen;
                pdi.usKey = usType;
                lstPreDecoderInfo.push_back(pdi);
                memset(&pdi, 0, sizeof(PreDecoderInfo));
                ulLeaveLen -= nUsedLen;
                pCurrent += nUsedLen;
            }
            else if (nUsedLen == 0)   //坏数据
            {
                if (pdi.ulLen > 0)
                {
                    ++pdi.ulLen;
                }
                else
                {
                    pdi.drCode = DR_BAD_DATA;
                    pdi.pData = pCurrent;
                    pdi.ulLen = 1;
                    pdi.usKey = 0;
                }

                --ulLeaveLen;
                ++pCurrent;
            }
            else  //数据不完整，等下一包
            {
                if (pdi.ulLen != 0)
                {
                    pdi.drCode = DR_BAD_DATA;
                    lstPreDecoderInfo.push_back(pdi);
                    memset(&pdi, 0, sizeof(PreDecoderInfo));
                }
                pdi.drCode = DR_UNCOMPLETE;
                pdi.pData = pCurrent;
                pdi.ulLen = ulLeaveLen;
                pdi.usKey = 0;
                lstPreDecoderInfo.push_back(pdi);
                memset(&pdi, 0, sizeof(PreDecoderInfo));

                break;
            }
        }

        if (pdi.ulLen != 0)
        {
            pdi.drCode = DR_BAD_DATA;
            lstPreDecoderInfo.push_back(pdi);
            memset(&pdi, 0, sizeof(PreDecoderInfo));
        }

        if (ulLeaveLen > 0)
        {
            pdi.drCode = DR_UNCOMPLETE;
            pdi.pData = pCurrent;
            pdi.ulLen = ulLeaveLen;
            lstPreDecoderInfo.push_back(pdi);
        }
    }

    static T* DecodeClass(const char* szBuf, unsigned long ulLen, unsigned int usKey)
    {
        T* pT = SerialClassManager<T>::GetClassInstance(usKey);
        //pT == NULL 表示类型未注册
        if (pT != NULL)
        {
            unsigned long ulPackageLen = ulLen;
            if (!(pT->Decode(const_cast<char*>(szBuf), ulPackageLen) && ulPackageLen == ulLen)) //解析数据不对
            {
                delete pT;
                pT = NULL;
            }
        }
        return pT;
    }

    static T* DecodeClass(const char* szBuf, unsigned long ulLen)
    {
        int nUsed = ulLen;
        unsigned int usType = T::CheckData(szBuf, ulLen, nUsed);
        if (usType > 0 && nUsed == ulLen)
        {
            return DecodeClass(szBuf, ulLen, usType);
        }
        else
        {
            return NULL;
        }
    }

    template<typename U>
    static U* DecodeClassSpecial(const char* szBuf, unsigned long ulLen, unsigned long& ulUsedLen)
    {
        U* pU = NULL;
        const char* pCurrent = szBuf;
        unsigned long ulLeaveLen = ulLen;
        while (ulLeaveLen >= T::MIN_SERIAL_LENGTH)
        {
            int nUsedLen = 0;
            unsigned int usType = T::CheckData(pCurrent, ulLeaveLen, nUsedLen);
            //指定的才解析
            if (usType == U::ClassKey)
            {
                pU = new U;
                unsigned long ulPackageLen = nUsedLen;
                if (!(pU->Decode(const_cast<char*>(pCurrent), ulPackageLen) && ulPackageLen == nUsedLen)) //解析数据不对
                {
                    delete pU;
                    pU = NULL;
                }
                ulLeaveLen -= nUsedLen;
                pCurrent += nUsedLen;

                if (pU != NULL)
                {
                    break;
                }
            }
            else if (nUsedLen == 0)   //坏数据
            {
                --ulLeaveLen;
                ++pCurrent;
            }
            else  //数据不完整，等下一包
            {
                break;
            }
        }

        ulUsedLen = ulLen - ulLeaveLen;
        return pU;
    }

#ifdef XML_ENCD_DECD
    static T* DecodeClassFromXML(XMLNodeInfo& nodeInfo)
    {
        if (nodeInfo.strName == "data" || 
			nodeInfo.strName == "poisearch" )
        {
            XMLNodeInfo* pKey = nodeInfo.FindNode("key");
            U32 u32 = atoi(pKey->strVal.c_str());
            if (u32 > 0)
            {
                T* pT = SerialClassManager<T>::GetClassInstance(u32);
                //pT == NULL 表示类型未注册
                if (pT != NULL && pT->DecodeFromXML(nodeInfo))
                {
                    return pT;
                }
                else
                {
                    delete pT;
                    return NULL;
                }
            }
            else
            {
                return NULL;
            }
        }
        else
        {
            return NULL;
        }
    }
#endif

private:
    static void ClearDecoderInfo(DecoderInfo<T>& di)
    {
        memset(&di, 0, sizeof(DecoderInfo<T>));
    }
    //返回值NULL表示无合理数据
    //       ulUsefulLen>MIN_LEN 表示未注册
    //       >0 表示数据头正确，但是数据不完全
    //       =0 表示数据头都不对
    //返回值<>NULL表示数据正确
    //       ulUsefulLen正确数据的长度
    static T* Decode(const char* szBuf, unsigned long ulLen, unsigned long& ulUseLen)
    {
        T* pT = NULL;
        int nUsedLen = 0;
        unsigned int usType = T::CheckData(szBuf, ulLen, nUsedLen);
        if (usType > 0)
        {
            ulUseLen = (unsigned long)nUsedLen;
            pT = SerialClassManager<T>::GetClassInstance(usType);
            //pT == NULL 表示类型未注册
            if (pT != NULL)
            {
                unsigned long ulPackageLen = ulUseLen;
                if (!(pT->Decode(const_cast<char*>(szBuf), ulPackageLen) && ulPackageLen == ulUseLen)) //解析数据不对
                {
                    delete pT;
                    pT = NULL;
                    ulUseLen = 0;
                }
            }
            return pT;
        }
        else if (nUsedLen == 0)   //坏数据
        {
            return NULL;
        }
        else  //数据不完整，等下一包
        {
            ulUseLen = 1;
            return NULL;
        }
    }
};

#endif