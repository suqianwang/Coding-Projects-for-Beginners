//
//  Application.h
//  TP1_CP4
//
//  Created by Susan Wang on 10/16/17.
//  Copyright © 2017 Suqian Wang. All rights reserved.
//

#pragma once

#include "Database.h"

class Application {
private:
	Database database;

public:
		
	Application();

	Record get_record(string table_name, string key_name, string key_value);
	Record get_min_max_record(string table_name, string key_name, bool is_max);
	
	void generate_part_table(string table_name, int record_num);
	void import_table(string table_name, int record_num);
	void import_reviews(string table_name, string key_name);

	double compute_average(string table_name, string attribute_name);
	vector<double> compute_range(string table_name, string attribute_name);
	int count_with_reviews(string table_name);
	
	Table get_table(string table_name) { return this->database.get_table(table_name); };
	Table filter(string select_command, string from_command, string where_command);
	Table review_for_one(string key_name, string key_value);
	Table connect_review();
	Table sort(string table_name, string key_name);
	Table thin_table(Table& table, vector<string> keep_attri);

	void display_table(Table& table, string table_name);
	void display_all_record(Table& table, string table_name);
	void display_business(Record& business_record);
	void display_user(Record& user_record);
	void display_review(Record& review_record);

	// operation on database
	void display_all_table_name();
	void delete_info(string table_name);

	vector<Table> get_all_table();
	// give summary information about all records in summary table concerned with one record 
	// specified by record_key in table "record_from"

	void display_summary(string from_table, string record_key, string summary_table);

	// business_table_name: the name business table recorded in database
	// business_key: the key specify the precise business record
	// summary_review_or_user: table_name, reviews or users.
	void display_summary_for_a_business(string business_table_name, string business_key, string summary_review_or_user);
	void display_compliments_for_a_user(string customer_key);
	//
};

string center(const string s, const int w);

void removeSubstrs(string& s, string& p);
