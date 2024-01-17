#include "mapper.h"

 DataType Mapper::mapColumnType(const std::string& columnType) {
    if (columnType == "string" or columnType == "STRING") {
        return std::string("str");
    } else if (columnType == "int" or columnType == "INT") {
        return int();
    } else if (columnType == "float" or columnType == "FLOAT") {
        return float();
    } else if (columnType == "bool" or columnType == "BOOL") {
        return bool();
    }
}
