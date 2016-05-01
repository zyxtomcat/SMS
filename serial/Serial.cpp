#include "Serial.h"

map<string, vector<char* (*)(Serial*, char*)> > Serial::zzz_mapSerialFunc;
map<string, vector<char* (*)(Serial*, char*)> > Serial::zzz_mapUnserialFunc;
map<string, vector<unsigned long (*)(Serial*)> > Serial::zzz_mapSizeFunc;

#ifdef XML_ENCD_DECD
map<string, vector<void (*)(Serial*, XMLWriter&)> > Serial::zzz_mapSerialXMLFunc;
map<string, vector<bool (*)(Serial*, XMLNodeInfo&)> > Serial::zzz_mapUnserialXMLFunc;
map<string, vector<void (*)(XMLWriter&)> > Serial::zzz_mapMakeXMLDocFunc;
#endif

template<typename T>
T HTON(T VALUE)
{
	return VALUE;
}

template<>
unsigned short HTON(unsigned short VALUE)
{
	if (is_littlendbian())
	{
		return ((VALUE & 0xFF00)>>8)&0x00FF | ((VALUE & 0x00FF)<<8)&0xFF00;
	}
	else
	{
		return VALUE;
	}
}

template<>
unsigned long HTON(unsigned long VALUE) 
{
	if (is_littlendbian())
	{
		return ((VALUE & 0xFF000000)>>24)&0x000000FF  | ((VALUE & 0x00FF0000)>>8)&0x0000FF00 
			| ((VALUE & 0x0000FF00)<<8)&0x00FF0000 | ((VALUE & 0x000000FF)<<24)&0xFF000000;
	}
	else
	{
		return VALUE;
	}
} 

template<>
unsigned int HTON(unsigned int VALUE) 
{
	if (is_littlendbian())
	{
		return ((VALUE & 0xFF000000)>>24)&0x000000FF  | ((VALUE & 0x00FF0000)>>8)&0x0000FF00 
			| ((VALUE & 0x0000FF00)<<8)&0x00FF0000 | ((VALUE & 0x000000FF)<<24)&0xFF000000;
	}
	else
	{
		return VALUE;
	}
}

struct ullST {
	unsigned long val1;
	unsigned long val2;	
};

union ullUN {
	unsigned long long val;
	struct ullST st;
};

template<>
unsigned long long HTON(unsigned long long VALUE) {
	if (is_littlendbian()) {
		ullUN un, un1;
		un.val = VALUE;
		un1.st.val2 = HTON(un.st.val1);
		un1.st.val1 = HTON(un.st.val2);
		return un1.val;
	} else {
		return VALUE;
	}
}

template<typename T>
T NTOH(T VALUE)
{
	return VALUE;
}

template<>
unsigned short NTOH(unsigned short VALUE)
{
	if (is_littlendbian())
	{
		return HTON(VALUE);
	}
	else
	{
		return VALUE;
	}
}

template<>
unsigned long NTOH(unsigned long VALUE)
{
	if (is_littlendbian())
	{
		return NTOH(VALUE);
	}
	else
	{
		return VALUE;
	}
}

template<>
unsigned int NTOH(unsigned int VALUE)
{
	if (is_littlendbian())
	{
		return NTOH(VALUE);
	}
	else
	{
		return VALUE;
	}
}

template<>
unsigned long long NTOH(unsigned long long VALUE) {
	if (is_littlendbian())
	{
		return NTOH(VALUE);
	}
	else
	{
		return VALUE;
	}
}
