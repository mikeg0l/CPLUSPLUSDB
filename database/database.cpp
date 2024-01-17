#include <fstream>
#include <sstream>
#include <iomanip>
#include "database.h"
#include "fmt/core.h"

/*
 Rozwiązanie problemu z przekazywaniem adresu fizycznego tabeli zamiast kopii
 https://www.educative.io/answers/resolving-the-function-returns-address-of-local-variable-error
 */
Table* Database::getTable(const std::string& name) {
    for (auto& table : tables) {
        if (table.getName() == name) {
            return &table;
        }
    }
    fmt::println("ERROR: TABLE NOT FOUND");
}

void Database::addTable(const Table& table) {
    tables.push_back(table);
}

void Database::loadTable(const std::string& filePath) {
    std::ifstream file("../" + filePath);
    if (!file.is_open()) {
        fmt::println("ERROR: FAILED TO OPEN FILE FOR LOADING TABLE DATA");
        return;
    }

    std::string tableName;
    std::getline(file, tableName);

    std::vector<std::string> columnNames;
    std::vector<std::string> columnTypes;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }

        std::istringstream iss(line);
        std::string columnName;
        std::string columnType;
        iss >> columnName >> columnType;

        columnNames.push_back(columnName);
        columnTypes.push_back(columnType);
    }

    Table table(tableName, columnNames, columnTypes);

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::map<std::string, std::string> rowData;
        for (const auto& columnName : columnNames) {
            std::string value;
            iss >> std::quoted(value);
            rowData[columnName] = value;
        }

        table.insert(rowData);
    }

    tables.push_back(table);

    file.close();
    fmt::println("INFO: TABLE LOADED FROM {}", filePath);
}

void Database::listTables() {
    for (auto& table : tables) {
        fmt::println("{}", table.getName());
    }
}

void Database::deleteTable(const std::string& name) {
    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i].getName() == name) {
            tables.erase(tables.begin()+i);
        }
    }
}
