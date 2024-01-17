#pragma once

#include "../table/datatype.h"

struct Mapper {
    static DataType mapColumnType(const std::string& columnType);
};

/*
 https://stackoverflow.com/questions/76074067/c-getting-the-held-index-of-a-variant-without-using-stdget
 https://en.cppreference.com/w/cpp/utility/variant/visit
 https://cpp-polska.pl/post/jak-uzywac-stdvisit-z-wieloma-wariantami
 */
struct DataTypeToStringValue {
    std::string operator()(const std::string &x) const {return x;}
    std::string operator()(int &x) const {return std::to_string(x);}
    std::string operator()(float &x) const {return std::to_string(x);}
    std::string operator()(bool &x) const {
        if (x == 1) {
            return "TRUE";
        } else {
            return "FALSE";
        }
    }
};

struct DataTypeToStringType {
    std::string operator()(const std::string &x) const {return "STRING";}
    std::string operator()(int &x) const {return "INT";}
    std::string operator()(float &x) const {return "FLOAT";}
    std::string operator()(bool &x) const {return "BOOL";}
};
