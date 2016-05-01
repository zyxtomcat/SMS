#ifndef _PUBLIC_FUNCTION_
#define _PUBLIC_FUNCTION_

#include <string>
#include <map>
#include <vector>
#include <time.h>
#include <stdarg.h>
#include <assert.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataTypeDef.h"
#include "Datetime.h"

using namespace std;

string ExtractFileName(const char* szFileName);
string ExtractFileExt(const char* szFileName);
string ExtractFileNameRemoveExt(const char* szFileName);
string ExtractFileDir(const char* szFileName);

bool WriteContentToFile(const string& strFileName, const string& strContent);
bool ReadContentFromFile(const string& strFileName, string& strContent);

char* RemoveLR(char* szBuf);
const char* NewStrpbrk(const char* str, const char* szDel);
void GetStrList(const char* str, const char* szDel, vector<string>& vecList);
string format(const char* szFmt, ...);
string format(const string& strFmt, ...);
string& StrUpCase(string& str);
string& StrLowCase(string& str);
char* StriStr(const char* szBuf, const char* szSub);

string FormatDatetimeAsNormal(const TIME& tmNow);
string FormatDatetime(const TIME& tmNow, const char* szFormat);
string FormatDatetime(const TIME& tmNow);
string FormatDatetime(const Datetime& dt);
string FormatDatetime1(const Datetime& dt);
void ToString(Datetime& t, string& str);
TIME NowTIME();
Datetime Now();
TIME TruncTime(TIME tmTime);
bool IsSpecialHour(TIME tmTime, unsigned char ucHour);
bool IsSpecialDay(TIME tmTime, unsigned char ucDay);
string ConvertToTime(unsigned long ulSecond);
string GetTimestamp();
string GetTimestampNoYear();

string BinToHexString(const char* szBuf, unsigned long ulLen, bool bUpCase = true);
string BinToHexString(const string& str, bool bUpCase = true);
string HexStringToBin(const string& str);

string MakeMD5(const string &src);
string MakeSHA1(const string &src);

void rc4_encrypt(const unsigned char *key, int keylen, unsigned char *data, int datalen);

bool IsDigit(const char* pStr, unsigned long ulLen);
bool IsDouble(const char* pStr, unsigned long ulLen);

int KeyGen(string& strKey);

int PasswordGen(string& strPassword, unsigned long len);

#endif
