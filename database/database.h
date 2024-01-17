#pragma once

#include <vector>
#include "../table/table.h"

class Database {
    std::vector<Table> tables;
public:
    Table* getTable(const std::string& name);
    void addTable(const Table& table);
    void loadTable(const std::string &filePath);
    void listTables();
    void deleteTable(const std::string& name);
};
