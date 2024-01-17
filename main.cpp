#include "table/tablerow.h"
#include "table/table.h"
#include "fmt/core.h"

int main() {
    auto command = std::string("CREATE TABLE blabla (INT id, STRING name, STRING surname)");

    auto table = new Table();
    auto tableName = "PEOPLE";
    auto columnNames = std::vector<std::string>({"ID", "NAME", "SURNAME", "AGE"});
    auto columnTypes = std::vector<std::string>({"INT", "STRING", "STRING", "INT"});
    table->createTable(tableName, columnNames, columnTypes);
    table->display();
    auto insertData = std::map<std::string,std::string>{{"ID", "1"}, {"NAME", "Borys"}, {"SURNAME", "Maciejewski"}, {"AGE", "20"}};
    auto insertData2 = std::map<std::string,std::string>{{"ID", "2"}, {"NAME", "Paweł"}, {"SURNAME", "Walda"}, {"AGE", "19"}};
    auto insertData3 = std::map<std::string,std::string>{{"ID", "3"}, {"NAME", "Mateusz"}, {"SURNAME", "Krasucki"}, {"AGE", "21"}};
    table->insert(insertData);
    table->insert(insertData2);
    table->insert(insertData3);
    table->display();
    table->addColumn("HEIGHT", "FLOAT");
    table->display();

}
