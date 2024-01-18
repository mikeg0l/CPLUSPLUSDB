#pragma once

#include "tablerow.h"
#include "datatype.h"
#include <vector>

struct Table {
    Table(const std::string& tableName, const std::vector<std::string>& columnNames, const std::vector<std::string>& columnTypes);

    // void selectRows(const std::string& columnName, const std::string& columnName);
    void display();
    void save(const std::string &filePath);
    void insert(const std::map<std::string, std::string>& rowData);
    void addColumn(const std::string &columnName, const std::string &columnType);
    void convertAndAssignValue(const std::string& columnName, const std::string& value, TableRow& row);
    std::vector<TableRow> matchWhereClause(std::istringstream& whereClause);
    void update(const std::map<std::string, std::string>& conditions, const std::string& columnName, const std::string& valueOverride);
    void deleteRow();

    std::string getName();
    std::string getPrimaryKey();
    std::vector<std::string> getColumnOrder();

private:
    std::string name;
    std::string primaryKey;
    std::vector<TableRow> rows;
    std::vector<std::string> columnOrder;
    std::unordered_map<std::string, DataType> columns;
};
