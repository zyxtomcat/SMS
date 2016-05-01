#ifndef _DATETIME_H
#define _DATETIME_H

#include "DataTypeDef.h"
#include <string>

class Datetime {
public:
    Datetime();
    Datetime(const std::string &str);
    ~Datetime();

    void operator=(const std::string &str);
    void operator=(const Datetime& dt);

    void parse(const std::string &str);

    std::string toString();

public:
    U16 u16Year;
    U8 u8Month;
    U8 u8Day;
    U8 u8Hour;
    U8 u8Min;
    U8 u8Second;
};

#endif
