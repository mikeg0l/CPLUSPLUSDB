#include "handlers.h"
#include "../utils/mapper.h"
#include <sstream>
#include <iomanip>
#include <fmt/core.h>

void handleCreateTable(Database& db, std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;
    std::string tmp;
    std::vector<std::string> columnNames, columnTypes;
    while (iss >> tmp) {
        columnNames.push_back(tmp);
        iss >> tmp;
        columnTypes.push_back(tmp);
    }

    db.addTable(Table(tableName, columnNames, columnTypes));
}

void handleDeleteTable(Database& db, std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;
    db.deleteTable(tableName);
    fmt::println("INFO: TABLE {} DELETED", tableName);
}

void handleSelect(Database& db, std::istringstream& iss) {
    auto columnsToSelect = std::vector<std::string>();
    bool selectAllColumns = false;
    std::string column, tableName, ddlOperation;
    iss >> column;
    while (column != "FROM") {
        if (column == "*") {
            iss >> column;
            selectAllColumns = true;
            break;
        }
        columnsToSelect.push_back(column);
        iss >> column;
    }

    iss >> tableName;

    if (selectAllColumns) {
        columnsToSelect = db.getTable(tableName)->getColumnOrder();
    }

    iss >> ddlOperation;

    if (ddlOperation == "WHERE") {
        auto rows = db.getTable(tableName)->matchWhereClause(iss);
        db.getTable(tableName)->select(rows, columnsToSelect);
    } else {
        db.getTable(tableName)->select(db.getTable(tableName)->getRows(), columnsToSelect);
    }
}

void handleSave(Database& db, std::istringstream& iss) {
    std::string tableName, filePath;
    iss >> tableName >> filePath;
    db.getTable(tableName)->save(filePath);
}

void handleLoad(Database& db, std::istringstream& iss) {
    std::string filePath;
    iss >> filePath;
    db.loadTable(filePath);
}

void handleAddColumn(Database& db, std::istringstream& iss) {
    std::string tableName, columnName, columnType;
    iss >> tableName >> columnName >> columnType;
    db.getTable(tableName)->addColumn(columnName, columnType);
}

void handleDeleteRow(Database& db, std::istringstream& iss) {
    std::string tableName, from, ddlOperation;

    iss >> from >> tableName >> ddlOperation;

    if (ddlOperation == "WHERE") {
        auto rows = db.getTable(tableName)->matchWhereClause(iss);
        db.getTable(tableName)->deleteRow(rows);
    }
}

void handleInsert(Database& db, std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;

    std::map<std::string, std::string> rowData;
    for (const auto& columnName : db.getTable(tableName)->getColumnOrder()) {
        std::string value;
        iss >> std::quoted(value); // https://stackoverflow.com/questions/36567786/how-to-ask-stringstream-dont-split-data-in-quotes-c
        rowData[columnName] = value;
    }

    db.getTable(tableName)->insert(rowData);
}

void handleUpdate(Database& db, std::istringstream& iss) {
    std::string tableName, columnName, columnValue, ddlOperation;
    iss >> tableName >> columnName >> std::quoted(columnValue) >> ddlOperation;

    if (ddlOperation == "WHERE") {
        auto rows = db.getTable(tableName)->matchWhereClause(iss);
        db.getTable(tableName)->update(rows, columnName, columnValue);
    } else {
        db.getTable(tableName)->update(db.getTable(tableName)->getRows(), columnName, columnValue);
    }
}

void handleRename(Database& db, std::istringstream& iss) {
    std::string tableName, newTableName;
    iss >> tableName >> newTableName;

    db.getTable(tableName)->rename(newTableName);
    fmt::println("INFO: RENAMED TABLE {} TO {}", tableName, newTableName);
}


void handleList(Database& db, std::istringstream& iss) {
    db.listTables();
}

void handleDisplay(Database& db, std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;
    db.getTable(tableName)->select(db.getTable(tableName)->getRows(), db.getTable(tableName)->getColumnOrder());
}
