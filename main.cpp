#include <iostream>
#include <sstream>
#include "table/tablerow.h"
#include "table/table.h"
#include "database/database.h"
#include "fmt/core.h"
#include "handlers/handlers.h"

int main() {
    Database db;

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
         * Multiple tables can be saved into single file
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
         * Load tables from given file path into the database
         *
         * Usage:
         * LOAD filePath
         *
         * @param filePath The path to which table data will be saved to
         */
        else if (command == "LOAD") {
            handleLoad(db, iss);
        }

        /**
         * Usage:
         * SELECT selectColumnName, selectColumnName, ... FROM tableName WHERE columnName aOp columnValue lOp [...]
         *
         * Select desired columns from table based on provided conditions
         *
         * @param selectColumnName Name of the column that will be selected
         * @param tableName Name of the table that the row(s) will selected from
         * @param columnName Name of the column used in condition
         * @param aOp Arithmetic operator used in condition (=, !=, >, <, >=, <=)
         * @param columnValue Value of the column used in condition
         * @param lOp Logical operator used in condition (AND or OR)
         */
        else if (command == "SELECT") {
            handleSelect(db, iss);
        }

        /**
         * Usage:
         * UPDATE tableName updateColumnName overrideValue WHERE columnName aOp columnValue lOp [...]
         *
         * Select desired columns from table based on provided conditions
         *
         * @param tableName Name of the table that the row(s) will selected from
         * @param updateColumnName Name of the column used in condition
         * @param overrideValue Value of the column that will be update used in condition
         * @param columnName Name of the column used in condition
         * @param aOp Arithmetic operator used in condition (=, !=, >, <, >=, <=)
         * @param columnValue Value of the column used in condition
         * @param lOp Logical operator used in condition (AND or OR)
         */
        else if (command == "UPDATE") {
            handleUpdate(db, iss);
        }

        /**
         * Usage:
         * RENAME tableName newTableName
         *
         * Rename the table
         *
         * @param tableName Name of the table that will be renamed
         * @param newTableName New name of the table
         */
        else if (command == "RENAME") {
            handleRename(db, iss);
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

            /**
             * Delete rows from given table
             *
             * Usage:
             * DELETE ROW FROM tableName WHERE columnName aOp columnValue lOp [...]
             *
             * @param tableName Name of the table that the row(s) will be deleted from
             * @param columnName Name of the column used in condition
             * @param aOp Arithmetic operator used in condition (=, !=, >, <, >=, <=)
             * @param columnValue Value of the column used in condition
             * @param lOp Logical operator used in condition (AND or OR)
             */
            if (subCommand == "ROW") {
                handleDeleteRow(db, iss);
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
        else {
            fmt::println("ERROR: UNKNOWN COMMAND");
        }
    }
}