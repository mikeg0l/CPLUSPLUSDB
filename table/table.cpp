#include <fstream>
#include "table.h"
#include "fmt/core.h"
#include "../utils/printer.h"
#include "../utils/mapper.h"

Table::Table(const std::string& tableName, const std::vector<std::string>& columnNames,
             const std::vector<std::string>& columnTypes)
        : name(tableName) {
    for (size_t i = 0; i < columnNames.size(); i++) {
        columns[columnNames[i]] = Mapper::mapColumnType(columnTypes[i]);
        columnOrder.push_back(columnNames[i]);
    }
    fmt::println("INFO: TABLE CREATED");
}

void Table::insert(const std::map<std::string, std::string>& rowData) {
    TableRow newRow;
    for (const auto& [columnName, value] : rowData) {
        if (columns.find(columnName) != columns.end()) {
            convertAndAssignValue(columnName, value, newRow);
        }
    }
    rows.push_back(newRow);
    fmt::println("INFO: INSERTED ROW");
}

void Table::display() {
    Printer::printHorizontalLine(columns.size());

    for (auto& columnName : columnOrder) {
        fmt::print("{: ^13}|", columnName);
    }

    fmt::print("\n");
    Printer::printHorizontalLine(columns.size());

    for (auto& row : rows) {
        for (const auto& columnName : columnOrder) {
            fmt::print("{: ^13}|", std::visit(DataTypeToStringValue(), row.columns[columnName]));
        }
        fmt::print("\n");
        Printer::printHorizontalLine(columnOrder.size());
    }

    fmt::print("\n");
}

void Table::addColumn(const std::string& columnName, const std::string& columnType) {
    if (columns.find(columnName) != columns.end()) {
        fmt::println("ERROR: COLUMN ALREADY EXISTS");
        return;
    }

    columnOrder.push_back(columnName);
    columns[columnName] = Mapper::mapColumnType(columnType);

    for (auto& row : rows) {
         if (columns[columnName].index() == 0) {
             row.columns[columnName] = std::string();
         } else if (columns[columnName].index() == 1) {
             row.columns[columnName] = int();
         } else if (columns[columnName].index() == 2) {
             row.columns[columnName] = float();
         } else if (columns[columnName].index() == 3) {
             row.columns[columnName] = bool();
         }
    }

    fmt::println("INFO: ADDED COLUMN {} TO TABLE {}", columnName, name);
}

void Table::update(const std::map<std::string, std::string>& conditions, const std::string& columnName, const std::string& valueOverride) {
    for (auto& row : rows) {
        if (columns.find(columnName) == columns.end()) {
            fmt::println("ERROR: COLUMN {} DOESN'T EXIST", columnName);
            return;
        }

        auto updateRow = true;

        for (const auto& [conditionColumn, conditionValue] : conditions) {
            if (row.columns.find(conditionColumn) == row.columns.end()) {
                updateRow = false;
                fmt::println("ERROR: COLUMN {} DOESN'T EXIST", conditionColumn);
                break;
            } else if (std::visit(DataTypeToStringValue(), row.columns[conditionColumn]) != conditionValue) {
                updateRow = false;
                break;
            }
        }

        if (updateRow) {
            convertAndAssignValue(columnName, valueOverride, row);
            fmt::println("INFO: UPDATED COLUMN {} WITH VALUE {}", columnName, valueOverride);
        }
    }
}

void Table::convertAndAssignValue(const std::string& columnName, const std::string& value, TableRow& row) {
    DataType columnType = columns[columnName];

    try {
        if (columnType.index() == 0) { // STRING
            row.columns[columnName] = value;
        } else if (columnType.index() == 1) { // INT
            row.columns[columnName] = std::stoi(value);
        } else if (columnType.index() == 2) { // FLOAT
            row.columns[columnName] = std::stof(value);
        } else if (columnType.index() == 3) { // BOOL
            row.columns[columnName] = (value == "TRUE" or value == "true");
        }
    } catch (const std::invalid_argument &e) {
        fmt::println("ERROR: INVALID TYPE FOR COLUMN {}", columnName);
        return;
    }
}

void Table::save(const std::string& filePath) {
    std::ofstream file("../" + filePath);
    if (!file.is_open()) {
        fmt::println("ERROR: FAILED TO OPEN FILE");
        return;
    }

    file << name << std::endl;

    for (const auto& columnName : columnOrder) {
        file << columnName << " " << std::visit(DataTypeToTypeString(), columns[columnName]) << std::endl;
    }

    file << std::endl;

    for (auto& row : rows) {
        for (const auto& columnName : columnOrder) {
            file << std::visit(DataTypeToStringValueSave(), row.columns[columnName]) << " ";
        }
        file << std::endl;
    }

    file.close();
    fmt::println("INFO: TABLE SAVED TO {}", filePath);
}

void Table::createRelation() {

}

void Table::deleteRow() {

}

std::string Table::getPrimaryKey() {
    return primaryKey;
}

std::string Table::getName() {
    return name;
}

std::vector<std::string> Table::getColumnOrder() {
    return columnOrder;
}
