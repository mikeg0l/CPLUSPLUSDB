#pragma once

#include "tablerow.h"
#include "datatype.h"
#include <vector>
#include <filesystem>

struct Table {
    // void findRows(const std::string& columnName, const std::string& columnName);
    void display();
    void createTable(const std::string &tableName, const std::vector<std::string>& columnNames, const std::vector<std::string>& columnTypes);
    void save();
    void insert(const std::map<std::string, std::string>& rowData);
    void addColumn(const std::string &columnName, const std::string &columnType);
    void load(std::filesystem::path& path);
    void createRelation();
    void update();
    void deleteRow();
    void deleteTable();

private:
    std::string name;
    std::vector<TableRow> rows;
    std::map<std::string, DataType> columns;
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