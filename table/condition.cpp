#include "condition.h"
#include "../utils/mapper.h"

bool Condition::eval(DataType& columnValue) {
    if (std::holds_alternative<bool>(columnValue)) {
        if (op == "=") {

        } else if (op == "!=") {

        }
    }
}

std::string Condition::getColumnName() {
    return columnName;
}

std::string Condition::getOp() {
    return op;
}

std::string Condition::getValue() {
    return "value";
}

