//
// Database.cpp
// Created by Dario Avendano on 9/24/2017.
// Team 44: Alex Kaiser, Dario Avendano, Suqian Wang
//

#include "Database.h"

Database::Database(){
    //database constructor
}

void Database::add_table(Table table, string table_name){
    
}

void Database::drop_table(string table_name){
    
}

vector<string> Database::list_table(){
    vector<string> tables_name;
    return tables_name;
}
vector<Table> Database::get_tables(){
    vector<Table> tables;
    return tables;
}

Table Database::Query(string select_command , string from_command , string where_command){
    Table table;
    return table;
}
