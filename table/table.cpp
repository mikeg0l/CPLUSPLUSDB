#include "table.h"
#include "fmt/core.h"
#include "../utils/printer.h"
#include "../utils/mapper.h"

void Table::insert(const std::map<std::string, std::string>& rowData) {
    auto newRow = TableRow();
    for (const auto& [columnName, value] : rowData) {
        if (columns.find(columnName) != columns.end()) {
            try { // https://en.cppreference.com/w/cpp/language/try_catch
                DataType columnType = columns[columnName];
                if (columnType.index() == 0 ) { // STRING
                    newRow.columns[columnName] = value;
                } else if (columnType.index() == 1) { // INT
                    newRow.columns[columnName] = std::stoi(value);
                } else if (columnType.index() == 2) { // FLOAT
                    newRow.columns[columnName] = std::stof(value);
                } else if (columnType.index() == 3) { // BOOL
                    newRow.columns[columnName] = (value == "TRUE" or value == "true");
                }
            } catch (const std::invalid_argument& e) {
                fmt::println("ERROR INSERTING ROW\nINVALID TYPE FOR {} COLUMN", columnName);
                return;
            }
        }
    }
    rows.push_back(newRow);
    fmt::println("INSERTED ROW");
}

void Table::display() {
    Printer::printHorizontalLine(columns.size());

    for (auto& columnName : columnOrder) {
        fmt::print("{: ^20}|", columnName);
    }

    fmt::print("\n");
    Printer::printHorizontalLine(columns.size());

    for (auto& row : rows) {
        for (const auto& columnName : columnOrder) {
            fmt::print("{: ^20}|", std::visit(DataTypeToString(), row.columns[columnName]));
        }
        fmt::print("\n");
        Printer::printHorizontalLine(columnOrder.size());
    }

    fmt::print("\n");
}

void Table::createTable(const std::string &tableName, const std::vector<std::string> &columnNames, const std::vector<std::string>& columnTypes) {
    name = tableName;
    for (size_t i = 0; i < columnNames.size(); i++) {
        columns[columnNames[i]] = Mapper::mapColumnType(columnTypes[i]);
        columnOrder.push_back(columnNames[i]);
    }
    fmt::println("TABLE CREATED");
}

void Table::addColumn(const std::string& columnName, const std::string& columnType) {
    if (columns.find(columnName) != columns.end()) {
        fmt::println("COLUMN ALREADY EXISTS");
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

    fmt::println("ADDED COLUMN {} TO {} TABLE", columnName, name);
}

void Table::load(std::filesystem::path &path) {

}

void Table::save() {

}

void Table::update() {

}

void Table::createRelation() {

}

void Table::deleteRow() {

}

void Table::deleteTable() {

}
