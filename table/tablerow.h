#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <variant>
#include "datatype.h"

struct TableRow {
    std::unordered_map<std::string, DataType> columns;
    bool operator==(const TableRow& other);
    bool operator!=(const TableRow& other);
};
