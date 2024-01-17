#include <iostream>
#include <sstream>
#include "table/tablerow.h"
#include "table/table.h"
#include "database/database.h"
#include "fmt/core.h"
#include "handlers/handlers.h"

int main() {
    Database db;
    db.loadTable("dupa_dump");

    while (true) {
        std::string input, command;
        std::getline(std::cin, input);
        std::istringstream iss(input);

        iss >> command;

        if (command == "CREATE") {
            std::string subCommand;
            iss >> subCommand;

            /**
             * Create table in the database.
             * Supported types:
             * - STRING (If contains space, enter in quotes example "Jestem dzielny")
             * - INT
             * - FLOAT
             * - BOOL (Value can be true or false)
             *
             * Usage:
             * CREATE TABLE tableName columnName columnType columnName columnType ...
             *
             * @param tableName The name of the table which will be created
             * @param columnName The name of the column that will be added
             * @param columnType The type of the column that will be added
             */
            if (subCommand == "TABLE") {
                handleCreateTable(db, iss);
            }
        }

        /**
         * Save the specified table to given file path
         *
         * Usage:
         * SAVE tableName filePath
         *
         * @param tableName The name of the table which will be saved
         * @param filePath The path to which table data will be saved to
         */
        else if (command == "SAVE") {
            handleSave(db, iss);
        }

        /**
         * Load table from given file path into the database
         *
         * Usage:
         * LOAD filePath
         *
         * @param filePath The path to which table data will be saved to
         */
        else if (command == "LOAD") {
            handleLoad(db, iss);
        }

        else if (command == "SELECT") {

        }

        else if (command == "UPDATE") {

        }

        else if (command == "DELETE") {
            std::string subCommand;
            iss >> subCommand;

            /**
             * Usage:
             * DELETE TABLE tableName
             *
             * Delete given table from database
             *
             * @param tableName Name of the table that will be deleted
             */
            if (subCommand == "TABLE") {
                handleDeleteTable(db, iss);
            }
            if (subCommand == "ROW") {
                // ADD DELETE ROW
            }
        }

        else if (command == "ADD") {
            std::string subCommand;
            iss >> subCommand;

            /**
             * Load table from given file path into the database
             *
             * Usage:
             * ADD COLUMN tableName columnName columnType
             *
             * @param tableName Name of the table that will get modified
             * @param columnName Name of the column that will be added
             * @param columnType Type of the column that will be added
             */
            if (subCommand == "COLUMN") {
                handleAddColumn(db, iss);
            }
        }

        /**
         * Insert data into desired table
         *
         * Usage:
         * INSERT tableName value value value ...
         *
         * @param tableName Name of the table that the data will be inserted into
         * @param value Value that will
         */
        else if (command == "INSERT") {
            handleInsert(db, iss);
        }

        /**
         * Usage:
         * DISPLAY tableName
         *
         * Display all data in given table
         *
         * @param tableName Name of the table that will be displayed
         */
        else if (command == "DISPLAY") {
            handleDisplay(db, iss);
        }

        /**
         * Usage:
         * LIST
         *
         * List all tables in database
         */
        else if (command == "LIST") {
            handleList(db, iss);
        }

        /**
         * Usage:
         * EXIT
         *
         * Exit program
         */
        else if (command == "EXIT") {
            return 0;
        }

    }
}

/*
 * TODO:
 * - SELECTy
 * - obsługa JOINÓw
 * - obsługa wielu WHERE oraz operatorów logicznych
 * - WHERE NAME = Maciej AND SURNAME = Siemek OR AGE > 9
 */
