#include "tablerow.h"
#include "fmt/core.h"

struct DataTypeToString {
    std::string operator()(const std::string &x) const {return x;}
    std::string operator()(int &x) const {return std::to_string(x);}
    std::string operator()(float &x) const {return std::to_string(x);}
    std::string operator()(bool &x) const {return std::to_string(x);}
    // std::string operator()(std::monostate &x) const {return "";}
};