#include "condition.h"
#include "fmt/core.h"
#include "../utils/mapper.h"

void Condition::eval(DataType& columnValue) {
    if (std::holds_alternative<int>(columnValue)) {
        int columnValueInt = std::get<int>(columnValue);
        int valueInt = std::stoi(value);

        if (op == "=") {
            result = (columnValueInt == valueInt);
        } else if (op == "!=") {
            result = (columnValueInt != valueInt);
        } else if (op == ">") {
            result = (columnValueInt > valueInt);
        } else if (op == "<") {
            result = (columnValueInt < valueInt);
        } else if (op == ">=") {
            result = (columnValueInt >= valueInt);
        } else if (op == "<=") {
            result = (columnValueInt <= valueInt);
        }
    } else if (std::holds_alternative<float>(columnValue)) {
        float columnValueFloat = std::get<float>(columnValue);
        float valueFloat = std::stof(value);

        if (op == "=") {
            result = (columnValueFloat == valueFloat);
        } else if (op == "!=") {
            result = (columnValueFloat != valueFloat);
        } else if (op == ">") {
            result = (columnValueFloat > valueFloat);
        } else if (op == "<") {
            result = (columnValueFloat < valueFloat);
        } else if (op == ">=") {
            result = (columnValueFloat >= valueFloat);
        } else if (op == "<=") {
            result = (columnValueFloat <= valueFloat);
        }
    } else if (std::holds_alternative<bool>(columnValue)) {
        bool columnValueBool = std::get<bool>(columnValue);
        bool valueBool = (value == "true");

        if (op == "=") {
            result = (columnValueBool == valueBool);
        } else if (op == "!=") {
            result = (columnValueBool != valueBool);
        }
    } else if (std::holds_alternative<std::string>(columnValue)) {
        std::string columnString = std::get<std::string>(columnValue);
        if (op == "=") {
            result = (columnString == value);
        } else if (op == "!=") {
            result = (columnString != value);
        }
    } else {
        result = false;
    }
}

std::string Condition::getColumnName() {
    return columnName;
}

std::string Condition::getOp() {
    return op;
}

void Condition::clearResult() {
    result = false;
}

std::string Condition::getValue() {
    return value;
}

bool Condition::getResult() {
    return result;
}

