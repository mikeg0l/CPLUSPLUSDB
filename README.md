# Database Management System

This project implements a simple Database Management System in C++, allowing users to perform various operations on tables within a database. The system supports commands such as creating tables, saving/loading data, selecting, updating, deleting, adding columns, inserting data, displaying tables, and listing all tables in the database.

**Note**:
All string values apart from column names should be written in quotes

Example:
- ```INSERT PEOPLE 3 "Maciej" "Kowalski"```
- ```SELECT * FROM PEOPLE WHERE NAME = "Maciej"```

**Note 2**:

All conditions in `WHERE` clause are evaluated from left to right

## DDL
### CREATE TABLE

Create a table in the database.

**Supported Types:**
- STRING
- INT
- FLOAT
- BOOL

**Usage:**
```
CREATE TABLE tableName columnName columnType columnName columnType ...
```

**Parameters:**

- `tableName`: The name of the table which will be created.
- `columnName`: The name of the column that will be added.
- `columnType`: The type of the column that will be added.

**Examples:**

```
CREATE TABLE Employees ID INT Name STRING Age INT
```

This command is used to create a table named `Employees` with columns `ID` (integer), `Name` (string), and `Age` (integer).

```
CREATE TABLE Auta ID INT Marka STRING Model STRING Czy_elektryczne BOOL POJEMNOSC_SILNIKA FLOAT
```
This command is used to create a table named `Auta` with columns `ID` (integer), `Marka ` (string), `Model` (string), `Czy_elektryczne` (bool), `POJEMNOSC_SILNIKA` (float).



### ADD COLUMN

Load table from a given file path into the database.

**Usage:**
```
ADD COLUMN tableName columnName columnType
```

**Parameters:**

- `tableName`: Name of the table that will get modified.
- `columnName`: Name of the column that will be added.
- `columnType`: Type of the column that will be added.

**Example**:
```
ADD COLUMN Employees Salary INT
```

This command is used to add a column named `Salary` with the type `INT` to the `Employees` table.

### DELETE TABLE

Delete a given table from the database.

**Usage:**
```
DELETE TABLE tableName
```

**Parameters:**

- `tableName`: Name of the table that will be deleted.

**Example**:

```
DELETE TABLE Employees
```
This command is used to delete the `Employees` table from the database.

**Note**:

Make sure to specify the correct table name and conditions for row deletion.

### RENAME

Rename a given table.

**Usage:**
```
RENAME tableName newTableName
```

**Parameters:**

- `tableName`: Name of the table that will be renamed.
- `newTableName`: New name of the table.

**Example**:

```
RENAME Employees Workers
```
This command is used to rename the `Employees` table to `Workers`.


## DML

### INSERT

Insert data into the desired table.

**Usage:**
```
INSERT tableName value value value ...
```

**Parameters**:

- `tableName`: Name of the table that the data will be inserted into.
- `value`: Value that will be inserted.

**Example**:

```
INSERT Employees 1 "John Doe" 30
```

This command is used to insert a new row into the `Employees` table with values `1` for the first column, `John Doe` for the second column, and `30` for the third column.



### DELETE ROW

Delete rows from a given table based on specified conditions.

**Usage:**
```
DELETE ROW FROM tableName WHERE columnName aOp columnValue lOp [...]
```

**Parameters**:

- `tableName`: Name of the table that the row(s) will be deleted from.
- `columnName`: Name of the column used in the condition.
- `aOp`: Arithmetic operator used in the condition (=, !=, >, <, >=, <=).
- `columnValue`: Value of the column used in the condition.
- `lOp`: Logical operator used in the condition (AND or OR).

**Example**:
```
DELETE ROW FROM Employees WHERE Salary > 50000 AND Department = "IT"
```

This command is used to delete rows from the `Employees` table where the `Salary` is greater than 50000 and the `Department` is "IT".

### UPDATE

Update specified columns in a table based on provided conditions.

**Usage:**
```
UPDATE tableName updateColumnName overrideValue WHERE columnName aOp columnValue lOp [...]
```

**Parameters**:

- `tableName`: Name of the table that the row(s) will be selected from.
- `updateColumnName`: Name of the column that will be updated.
- `overrideValue`: Value that will be used to update the specified column.
- `columnName`: Name of the column used in the condition.
- `aOp`: Arithmetic operator used in the condition (=, !=, >, <, >=, <=).
- `columnValue`: Value of the column used in the condition.
- `lOp`: Logical operator used in the condition (AND or OR).

**Example**:
```
UPDATE Employees Salary 60000 WHERE Department = "IT" AND Age > 30
```

This command is used to update the `Salary` column to `60000` for rows in the `Employees` table where the `Department` is "IT" and the `Age` is greater than 30.

## DQL 

### SELECT

Select desired columns from a table based on provided conditions.

**Usage:**
```
SELECT selectColumnName, [...] FROM tableName WHERE columnName aOp columnValue lOp [...]
```

**Parameters**:
- `selectColumnName`: Name of the column that will be selected.
- `tableName`: Name of the table that the row(s) will be selected from.
- `columnName`: Name of the column used in the condition.
- `aOp`: Arithmetic operator used in the condition (=, !=, >, <, >=, <=).
- `columnValue`: Value of the column used in the condition.
- `lOp`: Logical operator used in the condition (`AND` or `OR`).

**Example**:
```
SELECT Name, Age FROM Employees WHERE Salary > 50000 AND Department = "IT"
```

This command is used to select the `Name` and `Age` columns from the `Employees` table where the `Salary` is greater than 50000 and the `Department` is "IT".



### DISPLAY

Display all data in a given table.

**Usage:**
```
DISPLAY tableName
```

**Parameters**:

- `tableName`: Name of the table that will be displayed.

**Example**:
```
DISPLAY Employees
```

This command is used to display all data in the `Employees` table.

### LIST

List all tables in the database.

**Usage:**
```
LIST
```

## SAVE/LOAD

### SAVE

Save the specified table to a given file path.
Multiple tables can be stored in single file.

**Usage:**
```
SAVE tableName filePath
```

**Parameters**:

- `tableName`: The name of the table which will be saved.
- `filePath`: The path to which table data will be saved.

**Example**:
```
SAVE Employees /path/to/save/Employees_data.txt
```

This command is used to save the `Employees` table to the specified file path (`/path/to/save/Employees_data.txt`).

### LOAD

Load tables from a given file path into the database.
Can load multiple tables from single file

**Usage:**
```
LOAD filePath
```

**Parameters**:

- `filePath`: The path to which table data will be saved.

**Example**:

```
LOAD /path/to/load/Employees_data.txt
```

This command is used to load data from the specified file path (`/path/to/load/Employees_data.txt`) into the database.