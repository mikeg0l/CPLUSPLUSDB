#pragma once

#include "tablerow.h"
#include "datatype.h"
#include <vector>

struct Table {
    Table(const std::string& tableName, const std::vector<std::string>& columnNames, const std::vector<std::string>& columnTypes);
    // void findRows(const std::string& columnName, const std::string& columnName);
    void display();
    void insert(const std::map<std::string, std::string>& rowData);
    void addColumn(const std::string &columnName, const std::string &columnType);
    void convertAndAssignValue(const std::string& columnName, const std::string& value, TableRow& row);
    void createRelation();
    void update(const std::map<std::string, std::string>& conditions, const std::string& columnName, const std::string& valueOverride);
    void deleteRow();
    void deleteTable();
    void save(const std::string &filePath);

    std::string getName();
    std::string getPrimaryKey();

private:
    std::string name;
    std::vector<TableRow> rows;
    std::unordered_map<std::string, DataType> columns;
    std::vector<std::string> columnOrder;
    std::string primaryKey;
};

enum class Command {
    SELECT,
    CREATE,
    UPDATE,
    INSERT,
    DELETE,
    SAVE,
    LOAD
};

enum class Clause {
    WHERE,
    JOIN,
    LIMIT,
    FROM
};