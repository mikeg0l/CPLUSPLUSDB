#pragma once

#include "tablerow.h"
#include "datatype.h"
#include <vector>

struct Table {
    Table(const std::string& tableName, const std::vector<std::string>& columnNames, const std::vector<std::string>& columnTypes);

    void save(const std::string& filePath);
    void rename(const std::string& tableName);
    void insert(const std::map<std::string, std::string>& rowData);
    void addColumn(const std::string& columnName, const std::string& columnType);
    void convertAndAssignValue(const std::string& columnName, const std::string& value, TableRow& row);
    void update(std::vector<TableRow> matchedRows, const std::string& columnName, const std::string& valueOverride);
    void select(std::vector<TableRow> rows, const std::vector<std::string>& columnNames);
    void deleteRow(std::vector<TableRow>& matchedRows);
    std::vector<TableRow> matchWhereClause(std::istringstream& whereClause);

    std::string getName();
    std::vector<TableRow> getRows();
    std::vector<std::string> getColumnOrder();

private:
    std::string name;
    std::vector<TableRow> rows;
    std::vector<std::string> columnOrder;
    std::unordered_map<std::string, DataType> columns;
};
