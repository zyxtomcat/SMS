#include "Datetime.h"
#include "PublicFunction.h"

Datetime::Datetime() : u16Year(0), u8Month(0), u8Day(0), u8Hour(0), u8Min(0), u8Second(0) {
    
}

Datetime::Datetime(const std::string &str) {
    sscanf(str.c_str(), "%04d-%02d-%02d %02d:%02d:%02d", &u16Year, &u8Month, &u8Day, &u8Hour, &u8Min, &u8Second);
}

Datetime::~Datetime() {
}

void Datetime::operator=(const Datetime& dt) {
    u16Year = dt.u16Year;
    u8Month = dt.u8Month;
    u8Day = dt.u8Day;
    u8Hour = dt.u8Hour;
    u8Min = dt.u8Min;
    u8Second = dt.u8Second;
}

void Datetime::operator=(const std::string &str) {
    sscanf(str.c_str(), "%04d-%02d-%02d %02d:%02d:%02d", &u16Year, &u8Month, &u8Day, &u8Hour, &u8Min, &u8Second);
}

void Datetime::parse(const std::string &str) {
    sscanf(str.c_str(), "%02d%02d%02d%02d%02d", &u16Year, &u8Month, &u8Day, &u8Hour, &u8Min);
    u16Year += 2000;
    u8Second = 0;  
}

std::string Datetime::toString() {
    std::string str;
    if (u16Year ==0 && u8Month == 0 && u8Day == 0 && u8Hour == 0 && u8Min == 0 && u8Second == 0) {
        str = "1900-01-01 00:00:00";
    } else {
        str = format("%04d-%02d-%02d %02d:%02d:%02d", u16Year, u8Month, u8Day, u8Hour, u8Min, u8Second);
    }

    return str;
}


