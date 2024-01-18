#pragma once

#include <string>
#include <vector>
#include "../table/condition.h"

void parseWhereClause(std::istringstream& whereClause, std::vector<Condition>* conditions, std::vector<std::string>* logicalOperators);
