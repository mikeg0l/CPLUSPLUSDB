#pragma once

#include <string>
#include <vector>
#include "datatype.h"

struct Condition {
    void eval(DataType& columnValue);
    Condition(std::string columnValue, std::string op, std::string value) : columnName(columnValue), op(op), value(value){};
    std::string getColumnName();
    std::string getOp();
    std::string getValue();
    void clearResult();
    bool getResult();

private:
    std::string columnName;
    std::string op;
    std::string value;
    bool result;
};