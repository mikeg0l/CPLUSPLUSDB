#pragma once

#include "../table/datatype.h"

struct Mapper {
    static DataType mapColumnType(const std::string& columnType);
};

struct DataTypeToString {
    std::string operator()(const std::string &x) const {return x;}
    std::string operator()(int &x) const {return std::to_string(x);}
    std::string operator()(float &x) const {return std::to_string(x);}
    std::string operator()(bool &x) const {return std::to_string(x);}
};
