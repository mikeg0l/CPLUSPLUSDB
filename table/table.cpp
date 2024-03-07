#include <fstream>
#include "table.h"
#include "fmt/core.h"
#include "../utils/printer.h"
#include "../utils/mapper.h"
#include "condition.h"
#include "../utils/parser.h"

Table::Table(const std::string& tableName, const std::vector<std::string>& columnNames, const std::vector<std::string>& columnTypes): name(tableName) {
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

void Table::select(std::vector<TableRow> matchedRows, const std::vector<std::string>& columnNames) {
    Printer::printHorizontalLine(columnNames.size());
    for (auto& columnName : columnOrder) {
        if (std::find(columnNames.begin(), columnNames.end(), columnName) != columnNames.end()) {
            Printer::printColumnOrValue(columnName);
        }
    }

    fmt::print("\n");
    Printer::printHorizontalLine(columnNames.size());

    for (auto& row : matchedRows) {
        for (auto& columnName : columnNames) {
            Printer::printColumnOrValue(std::visit(DataTypeToStringValue(), row.columns[columnName]));
        }
        fmt::print("\n");
        Printer::printHorizontalLine(columnNames.size());
    }
}

std::vector<TableRow> matchLimitClause(std::istringstream* limitClause) {

}

void Table::rename(const std::string& tableName) {
    name = tableName;
}

void Table::update(std::vector<TableRow> matchedRows, const std::string& columnName, const std::string& valueOverride) {
    auto ctr = 0;
    for (auto & row : rows) {
        for (auto matchedRow : matchedRows) {
            if (matchedRow == row) {
                convertAndAssignValue(columnName, valueOverride, row);
                ctr++;
            }
        }
    }
    fmt::println("INFO: UPDATED {} ROWS", ctr);
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
            row.columns[columnName] = (value == "true");
        }
    } catch (const std::invalid_argument &e) {
        fmt::println("ERROR: INVALID TYPE FOR COLUMN {}", columnName);
        return;
    }
}

void Table::save(const std::string& filePath) {
    std::ofstream file("../" + filePath, std::ios::app);
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

std::vector<TableRow> Table::matchWhereClause(std::istringstream& whereClause) {
    std::vector<TableRow> matchedRows;

    std::vector<Condition> conditions;
    std::vector<std::string> logicalOperators;

    parseWhereClause(whereClause, &conditions, &logicalOperators);

    for (auto& row : rows) {
        for (auto& [columnName, columnValue] : row.columns) {
            for (auto& condition : conditions) {
                if (condition.getColumnName() == columnName) {
                    condition.eval(columnValue);
                }
            }
        }

        bool rowValid = conditions[0].getResult();
        for (int i = 0; i < logicalOperators.size(); i++) {
            if (logicalOperators[i] == "AND") {
                rowValid = rowValid && conditions[i+1].getResult();
            } else {
                rowValid = rowValid || conditions[i+1].getResult();
            }
        }

        if (rowValid) {
            matchedRows.push_back(row);
        }

        for (auto& condition : conditions) {
            condition.clearResult();
        }
    }

    return matchedRows;
}

void Table::deleteRow(std::vector<TableRow>& matchedRows) {
    auto ctr = 0;
    for (int i = 0; i < rows.size(); i++) {
        for (auto matchedRow : matchedRows) {
            if (matchedRow == rows[i]) {
                rows.erase(rows.begin()+i);
                ctr++;
            }
        }
    }
    fmt::println("INFO: DELETED {} ROWS", ctr);
}

std::string Table::getName() {
    return name;
}

std::vector<std::string> Table::getColumnOrder() {
    return columnOrder;
}

std::vector<TableRow> Table::getRows() {
    return rows;
}
