#pragma once

#include <map>
#include <string>
#include <variant>
#include "datatype.h"

struct TableRow {
    std::map<std::string, DataType> columns;
};
