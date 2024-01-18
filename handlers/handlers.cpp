#include "handlers.h"
#include <sstream>
#include <iomanip>

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
}

void handleSelect(Database& db, std::istringstream& iss) {
    std::string whereClause, tableName;
    iss >> tableName;
    db.getTable(tableName)->matchWhereClause(iss);
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

}

void handleList(Database& db, std::istringstream& iss) {
    db.listTables();
}

void handleDisplay(Database& db, std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;
    db.getTable(tableName)->display();
}
