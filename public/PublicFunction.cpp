//#include "stdafx.h"
#include "PublicFunction.h"
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <stdarg.h>
#include <algorithm>


#define ISDIGIT(c)      ( ((c) >= '0') && ((c) <= '9') )

string ExtractFileName(const char* szFileName)
{
    string str = szFileName;
    size_t nIndex = str.find_last_of('\\');
    if (nIndex != str.npos)
    {
        return str.substr(nIndex + 1, str.size() - nIndex - 1);
    }
    else
    {
        return "";
    }
}

string ExtractFileExt(const char* szFileName)
{
    string str = szFileName;
    string strFileName = ExtractFileName(str.c_str());
    size_t nIndex = strFileName.find_last_of('.');
    if (nIndex != strFileName.npos)
    {
        return strFileName.substr(nIndex + 1, str.size() - nIndex);
    }
    else
    {
        return "";
    }
}

string ExtractFileNameRemoveExt(const char* szFileName)
{
    string str = szFileName;
    string strFileName = ExtractFileName(str.c_str());
    size_t nIndex = strFileName.find_last_of('.');
    if (nIndex != strFileName.npos)
    {
        return strFileName.substr(0, nIndex);
    }
    else
    {
        return "";
    }
}

string ExtractFileDir(const char* szFileName)
{
    string str = szFileName;
    size_t nIndex = str.find_last_of('\\');
    if (nIndex != str.npos)
    {
        return str.substr(0, nIndex + 1);
    }
    else
    {
        return "";
    }
}

char* RemoveLR(char* szBuf)
{
    char* pTemp = szBuf;
    pTemp += strlen(szBuf) - 1;
    while ((*pTemp =='\n' || *pTemp =='\r') && pTemp >= szBuf)
    {
        *pTemp-- ='\0';
    }
    return szBuf;
}

const char* NewStrpbrk(const char* str, const char* szDel)
{
    const char* szResult = str;
    while (true)
    {
        szResult = strpbrk(szResult, szDel);
        if (szResult != NULL)
        {
            const char* szCurr = str;
            unsigned long ulCount = 0;
            while (szCurr < szResult)
            {
                if (*szCurr == '\"')
                {
                    ++ulCount;
                }
                ++szCurr;
            }

            if ((ulCount & 1) == 1)
            {
                ++szResult;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return szResult;
}	

void GetStrList(const char* str, const char* szDel, vector<string>& vecList)
{
    vecList.clear();
    const char* szOldHead = str;
    const char* szTemp = NewStrpbrk(str, szDel);
    char token[256];
    while (szTemp != NULL)
    {
        memcpy(token, szOldHead, szTemp - szOldHead);
        token[szTemp - szOldHead] = '\0';
        vecList.push_back(token);

        ++szTemp;
        szOldHead = szTemp;
        szTemp = NewStrpbrk(szTemp, szDel);
    }
    vecList.push_back(szOldHead);
}	

string format(const char* szFmt, ...)
{
    char szOut[1024 * 100];
    va_list body;
    va_start(body, szFmt);
    vsprintf(szOut, szFmt, body); 
    va_end(body); 
    return szOut;
}

string format(const string& strFmt, ...)
{
    char szOut[1024 * 100];
    va_list body;
    const char* p = strFmt.c_str();
    va_start(body, p);
    vsprintf(szOut, p, body); 
    va_end(body); 
    return szOut;
}

string FormatDatetime(const TIME& tmNow, const char* szFormat)
{
    char szTemp[256];
    tm* pTemp = localtime(&tmNow);
    strftime(szTemp, 256, szFormat, pTemp);
    return szTemp;
}

string FormatDatetime(const TIME& tmNow)
{
    tm* pTemp = localtime(&tmNow);
    return format("%.4d%.2d%.2d%.2d%.2d%.2d", pTemp->tm_year + 1900, pTemp->tm_mon + 1, pTemp->tm_mday,
        pTemp->tm_hour, pTemp->tm_min, pTemp->tm_sec);
}

string FormatDatetimeAsNormal(const TIME& tmNow)
{
    tm* pTemp = localtime(&tmNow);
    return format("%.4d-%.2d-%.2d %.2d:%.2d:%.2d", pTemp->tm_year + 1900, pTemp->tm_mon + 1, pTemp->tm_mday,
        pTemp->tm_hour, pTemp->tm_min, pTemp->tm_sec);
}


TIME NowTIME()
{
    return time(NULL);
}

string ConvertToTime(unsigned long ulSecond)
{
    U32 u32Day = ulSecond / 86400;
    ulSecond -= u32Day * 86400;

    U8 u8Hour = ulSecond / 3600;
    ulSecond -= u8Hour * 3600;
    
    U8 u8Min = ulSecond / 60;
    ulSecond -= u8Min * 60;

    U8 u8Second = ulSecond;

    if (u32Day == 0)
    {
        return format("%.2d:%.2d:%.2d", u8Hour, u8Min, u8Second);
    }
    else
    {
        return format("%d %.2d:%.2d:%.2d", u32Day, u8Hour, u8Min, u8Second);
    }
}

string GetTimestamp() {
    time_t tmNow = time(NULL);
    struct tm *stTime = localtime(&tmNow);
    return format("%04d%02d%02d%02d%02d%02d", stTime->tm_year+1900, stTime->tm_mon+1, stTime->tm_mday, stTime->tm_hour, stTime->tm_min, stTime->tm_sec);
}

string GetTimestampNoYear() {
   time_t tmNow = time(NULL);
    struct tm *stTime = localtime(&tmNow);
    return format("%02d%02d%02d%02d%02d", stTime->tm_mon+1, stTime->tm_mday, stTime->tm_hour, stTime->tm_min, stTime->tm_sec); 
}

Datetime Now()
{
    time_t tmNow = time(NULL);
    tm *p = localtime(&tmNow);
    Datetime dt;
    dt.u16Year = p->tm_year + 1900;
    dt.u8Month = p->tm_mon + 1;
    dt.u8Day = p->tm_mday;
    dt.u8Hour = p->tm_hour;
    dt.u8Min = p->tm_min;
    dt.u8Second = p->tm_sec;
    return dt;
}

string BinToHexString(const char* szBuf, unsigned long ulLen, bool bUpCase)
{
    assert(szBuf);
    assert(ulLen > 0);
    static bool bInit = false;
    static char aacUpCaseMapKey[256][2];
    static char aacLowCaseMapKey[256][2];
    if (!bInit)
    {
        static char UpCaseCharMapping[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
        static char LowCaseCharMapping[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        for (int i = 0; i < 256; ++i)
        {
            aacUpCaseMapKey[i][0] = UpCaseCharMapping[i >> 4];
            aacUpCaseMapKey[i][1] = UpCaseCharMapping[i & 0xf];
            aacLowCaseMapKey[i][0] = LowCaseCharMapping[i >> 4];
            aacLowCaseMapKey[i][1] = LowCaseCharMapping[i & 0xf];
        }
        bInit = true;
    }

    string strResult;
    strResult.resize(ulLen * 2 );
    
    if (bUpCase)
    {
        for (unsigned long ul = 0; ul < ulLen; ++ul, ++szBuf)
        {
            unsigned char ucIndex = (unsigned char)(*szBuf);
            strResult[ul * 2] = aacUpCaseMapKey[ucIndex][0];
            strResult[ul * 2 + 1] = aacUpCaseMapKey[ucIndex][1];
        }
    }
    else
    {
        for (unsigned long ul = 0; ul < ulLen; ++ul, ++szBuf)
        {
            unsigned char ucIndex = (unsigned char)(*szBuf);
            strResult[ul * 2] = aacLowCaseMapKey[ucIndex][0];
            strResult[ul * 2 + 1] = aacLowCaseMapKey[ucIndex][1];
        }
    }
    //strResult[ulLen * 2] = '\0';

    return strResult;
}

string BinToHexString(const string& str, bool bUpCase)
{
    return BinToHexString(str.c_str(), str.size(), bUpCase);
}

string HexStringToBin(const string& str)
{
    bool bInit = false;
    static unsigned char CharMap[256] = {0};
    if (!bInit)
    {
        CharMap['1'] = 1;
        CharMap['2'] = 2;
        CharMap['3'] = 3;
        CharMap['4'] = 4;
        CharMap['5'] = 5;
        CharMap['6'] = 6;
        CharMap['7'] = 7;
        CharMap['8'] = 8;
        CharMap['9'] = 9;
        CharMap['A'] = 10;
        CharMap['B'] = 11;
        CharMap['C'] = 12;
        CharMap['D'] = 13;
        CharMap['E'] = 14;
        CharMap['F'] = 15;
        CharMap['a'] = 10;
        CharMap['b'] = 11;
        CharMap['c'] = 12;
        CharMap['d'] = 13;
        CharMap['e'] = 14;
        CharMap['f'] = 15;
        bInit = true;
    }

    string strResult;
    if ((str.size() % 2) == 0)
    {
        int nLen = str.size() / 2;
        strResult.resize(nLen);
        for (int i = 0; i < nLen; ++i)
        {
            unsigned char uc = (CharMap[str[i * 2]] << 4) + CharMap[str[i * 2 + 1]];
            strResult[i] = (char)uc;
        }
    }
    return strResult;
}


string MakeMD5(const string &src)
{
    unsigned char md[MD5_DIGEST_LENGTH];
    MD5((const unsigned char *)src.c_str(), src.size(), md);
    string md5;
    md5.append((const char *)md, MD5_DIGEST_LENGTH);
    return BinToHexString(md5);
}

string MakeSHA1(const string &src) {

    unsigned char md[SHA_DIGEST_LENGTH];  
    SHA1((const unsigned char *)src.c_str(), src.size(), md);
    string sha1;
    sha1.append((const char *)md, SHA_DIGEST_LENGTH);
    return BinToHexString(sha1);
}

TIME TruncTime(TIME tmTime)
{
    tm tmTemp = *localtime(&tmTime);
    tmTemp.tm_hour = 0;
    tmTemp.tm_min = 0;
    tmTemp.tm_sec = 0;
    return mktime(&tmTemp);
}

bool IsSpecialHour(TIME tmTime, unsigned char ucHour)
{
    tm tmTemp = *localtime(&tmTime);
    return tmTemp.tm_hour == ucHour;
}

bool IsSpecialDay(TIME tmTime, unsigned char ucDay)
{
    tm tmTemp = *localtime(&tmTime);
    return tmTemp.tm_mday == ucDay;
}

string& StrUpCase(string& str)
{
    transform(str.begin(),str.end(),str.begin(),::tolower);
    return str;
}

string& StrLowCase(string& str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

#define ToLow(A) (((A) >= 'A' && (A) <= 'Z') ? ((A) + ('a' - 'A')) : (A))

char* StriStr(const char* szBuf, const char* szSub)
{
    assert(szBuf);
    assert(szSub);

    if (*szSub == '\0')
    {
        return((char*)szBuf);
    }

    char* cp = (char*)szBuf;
    while (*cp != '\0')
    {
        char* s1 = cp;
        char* s2 = (char*)szSub;

        while (*s1 != '\0' && *s2 != '\0' && (ToLow(*s1) == ToLow(*s2)))
        {
            s1++, s2++;
        }

        if (*s2 == '\0')
        {
            return(cp);
        }

        cp++;
    }

    return(NULL);
}

bool WriteContentToFile(const string& strFileName, const string& strContent)
{
    FILE* pFile = fopen(strFileName.c_str(), "w+t");
    if (pFile != NULL)
    {
        size_t size = fwrite(strContent.c_str(), 1, strContent.size(), pFile);
        fclose(pFile);
        return size == strContent.size();
    }
    else
    {
        return false;
    }
}

bool ReadContentFromFile(const string& strFileName, string& strContent)
{
    strContent.clear();
    FILE* pFile = fopen(strFileName.c_str(), "rt");
    if (pFile != NULL)
    {
        while (!feof(pFile))
        {
            char szBuf[1024];
            size_t size = fread(szBuf, 1, 1024, pFile);
            if (size > 0)
            {
                strContent.append(szBuf, size);
            }
        }
        fclose(pFile);
        return true;
    }
    else
    {
        return false;
    }
}

bool IsDigit(const char* pStr, unsigned long ulLen)
{
	bool bIsTure = true;
	while (ulLen -- )
	{
		if (!ISDIGIT(*pStr))
		{
			bIsTure = false;
			break;
		}
		++pStr;
	}

	return bIsTure;
}

bool IsDouble(const char* pStr, unsigned long ulLen)
{
	bool bIsTure = true;
	int dotcnt = 0;
	while (ulLen -- )
	{
		if (!ISDIGIT(*pStr))
		{
			if (*pStr == '.') {
				++dotcnt;
			} else {
				bIsTure = false;
				break;
			}
		}
		++pStr;
	}

	if (bIsTure && dotcnt > 1) bIsTure = false;

	return bIsTure;
}

int KeyGen(string& strKey)
{
	strKey.clear();
	srand(time(NULL));
	int len = rand() % 15;
	if (len < 8) len += 8;
	char *key = new char[len + 1];
	for (int i =0; i<len; ++i)
	{
		key[i] = rand() % 126;
		if (key[i] < 33)
		{
			key[i] += 33;
		}
	}
	key[len] = '\0';
	strKey.assign(key, len);
	delete[] key;
	return len;
}

int PasswordGen(string& strPassword, unsigned long len)
{
	strPassword.clear();
	srand(time(NULL));
	char *key = new char[len + 1];
	int i = 0;
	while (i < len)
	{
		key[i] = rand() % 126;
		if ((key[i] > 47 && key[i] < 58) ||
			(key[i] > 96 && key[i] < 123))
		{
			++i;
		}
	}
	key[len] = '\0';
	strPassword.assign(key, len);
	delete[] key;
	return len;
}

#define FFSWAP(type,a,b) do{type SWAP_tmp= b; b= a; a= SWAP_tmp;}while(0)
void rc4_encrypt(const unsigned char *key, int keylen, unsigned char *data, int datalen)
{
	int i, j;
	unsigned char x, y;
	unsigned char state[256];
	for (i = 0;i< 256;i++)
		state[i] = i;
	y = 0;
	for(j = 0,i = 0;i< 256;i++,j++)
	{
		if (j == keylen)
			j = 0;
		y +=state[i]+key[j];
		FFSWAP(unsigned char,state[i],state[y]);
	}
	// state initialized, now do the real encryption
	x = 1;
	y = state[1];
	while (datalen-- > 0)
	{
		unsigned char sum = state[x] + state[y];
		FFSWAP(unsigned char, state[x], state[y]);
		*data++ ^= state[sum];
		x++;
		y += state[x];
	}
}
