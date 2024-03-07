#include "tablerow.h"

bool TableRow::operator==(const TableRow &other) {
    for (auto& [columnName, columnValue] : columns) {
        for (auto& [columnNameOther, columnValueOther] : other.columns) {
            if (columnName == columnNameOther && columnValue != columnValueOther) {
                return false;
            }
        }
    }
    return true;
}

bool TableRow::operator!=(const TableRow &other) {
    for (auto& [columnName, columnValue] : columns) {
        for (auto& [columnNameOther, columnValueOther] : other.columns) {
            if (columnName == columnNameOther && columnValue == columnValueOther) {
                return false;
            }
        }
    }
    return true;
}
