#include <sstream>
#include <iomanip>
#include "parser.h"

void parseWhereClause(std::istringstream& whereClause, std::vector<Condition>* conditions, std::vector<std::string>* logicalOperators) {
    while (true) {
        std::string columnName, op, value;
        whereClause >> columnName >> op >> std::quoted(value); // https://stackoverflow.com/questions/33072293/reading-quoted-string-in-c
        auto condition = Condition(columnName, op, value);
        conditions->push_back(condition);

        std::string logicalOperator;
        if (whereClause >> logicalOperator) {
            logicalOperators->push_back(logicalOperator);
        } else {
            break;
        }
    }
}