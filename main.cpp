#include <iostream>
#include <sstream>
#include "table/tablerow.h"
#include "table/table.h"
#include "database/database.h"
#include "fmt/core.h"

int main() {
    Database db;
    db.loadTable("DATA.txt");

    while (true) {
        std::string input, command;
        std::getline(std::cin, input);
        std::istringstream iss(input);

        iss >> command;
        if (command == "CREATE") {
            fmt::println("wow");
        }
        /**
         * SAVE tableName filePath
         *
         * @param tableName The name of the table which will be saved
         * @param filePath The path to which table data will be saved to
         */
        else if (command == "SAVE") {
            std::string tableName, filePath;
            iss >> tableName >> filePath;
            db.getTable(tableName)->save(filePath);
        }

        else if (command == "LOAD") {
            std::string filePath;
            iss >> filePath;
            db.loadTable(filePath);
        }

        else if (command == "UPDATE") {

        }

        else if (command == "DELETE") {

        }

        else if (command == "ADD") {
            std::string subCommand;
            iss >> subCommand;
            if (subCommand == "COLUMN") {
                std::string tableName, columnName, columnType;
                iss >> tableName >> columnName >> columnType;
                db.getTable(tableName)->addColumn(columnName, columnType);
            }
        }

        else if (command == "INSERT") {

        }

        else if (command == "DISPLAY") {
            std::string tableName;
            iss >> tableName;
            db.getTable(tableName)->display();
        }


        else if (command == "LIST") {
            db.listTables();
        }

    }
    db.getTable("EMPLOYEES")->display();
    db.getTable("EMPLOYEES")->update({{"NAME", "Borys"}}, "HEIGHT", "115.5");
    db.getTable("EMPLOYEES")->display();
}
