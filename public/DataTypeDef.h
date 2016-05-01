#ifndef _DATA_TYPE_
#define _DATA_TYPE_

#ifndef _AF_SERVICE_
#define _AF_SERVICE_

#include <time.h>

typedef char S8;
typedef short S16;
typedef long S32;
typedef long long S64;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;
typedef unsigned long long U64;
typedef time_t TIME;
typedef unsigned char BYTE;

#endif

/*
struct Datetime
{
    U16 u16Year;
    U8 u8Month;
    U8 u8Day;
    U8 u8Hour;
    U8 u8Min;
    U8 u8Second;
};
*/

#ifndef WIN32
typedef unsigned int UINT;
typedef int INT;
#endif

typedef int SINT;


#endif
