//
// Table.cpp
// Created by Alex Kaiser on 9/21/2017.
// Team 44: Alex Kaiser, Dario Avendano, Suqian Wang
//

#include "Table.h"

Table::Table(vector<string> attribute_name): columns(attribute_name) {};

void Table::add_attribute(string attribute_name){
    
}

void Table::delete_attribute(string attribute_name){
    
}

void Table::insert_record(Record record){
    
}

vector<string> Table::get_attributes() const{
    vector<string> sorted_columns;
    return sorted_columns;
}

unsigned long int Table::get_size() const{
    return this->rows.size();
}

Record Table::return_record(int index){
    return this->rows.at(index);
}

void Table::set_key(string attribute_name){
    
}

int Table::count(string attribute_name){
    return 0;
}

string Table::max(string attribute_name){
    return NULL;
}

string Table::min(string attribute_name){
    return NULL;
}

Table cross_join(Table table_1, Table table_2){
    Table table;
    return table;
}
Table natural_join(Table table_1, Table table_2){
    Table table;
    return table;
}
