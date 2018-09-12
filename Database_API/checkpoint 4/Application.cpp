//
//  Application.cpp
//  TP1_CP4
//
//  Created by Susan Wang on 10/16/17.
//  Copyright © 2017 Suqian Wang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "json.h"
#include "Record.h"
#include "Table.h"
#include "Database.h"
#include "aux_function.h"
#include "Application.h"


using namespace std;

Application::Application() {

}

// return record

Record Application::get_record(string table_name, string key_name, string key_value) {

	Table& get_table = this->database.get_table(table_name);

	vector<string> attributes = get_table.get_attributes();
	int attri_pos = find(attributes.begin(), attributes.end(), key_name) - attributes.begin();

	// get corresponding record
	Record record;
	for (int i = 0; i < get_table.get_size(); i++) {
		if (get_table.return_record(i).get_record_entry(attri_pos) == key_value) {
			record = get_table.return_record(i);
			break;
		}
	}

	return record;
}

Record Application::get_min_max_record(string table_name, string key_name, bool is_max) {
	Table& get_table = this->database.get_table(table_name);

	vector<string> attributes = get_table.get_attributes();
	int attri_pos = find(attributes.begin(), attributes.end(), key_name) - attributes.begin();

	Record record;
	double bound = stod(get_table.return_record(0).get_record_entry(attri_pos));

	for (int i = 0; i < get_table.get_size(); i++) {
		if (is_max) {
			if (stod(get_table.return_record(i).get_record_entry(attri_pos)) > bound) {
				record = get_table.return_record(i);
				bound = stod(record.get_record_entry(attri_pos));
			}
		}
		else if (stod(get_table.return_record(i).get_record_entry(attri_pos)) < bound) {
			record = get_table.return_record(i);
			bound = stod(record.get_record_entry(attri_pos));
		}
	}

	return record;
}

void Application::generate_part_table(string table_name, int record_num) {
	using json = nlohmann::json;
	ifstream table_file(table_name + ".json");
	json j_import_table;
	
	ofstream output_file(table_name + "_short.json");

	for (int i = 0; i < record_num; i++) {
		table_file >> j_import_table;
		output_file << j_import_table << endl;
	}
	
}

void Application::import_table(string table_name, int record_num) {

	using json = nlohmann::json;
	ifstream table_initial(table_name + ".json");
	json j_table;
	table_initial >> j_table;
	
	// get attribute and insert all into table
	vector<string> attributes;
	for (json::iterator iter = j_table.begin(); iter != j_table.end(); iter++) {
		attributes.push_back(iter.key());
	}
	Table table(attributes);

	int max_record_num = record_num;
	Record record(attributes.size());
	string attr_str;
	ostringstream convert;

	ifstream table_file(table_name + ".json");
	for (int i = 0; i < max_record_num; i++) {
		table_file >> j_table;

		int attr_index = 0;
		for (json::iterator iter = j_table.begin(); iter != j_table.end(); iter++) {
			json object = iter.value();

			attr_str = object.dump();
			removeSubstrs(attr_str, (string)"\"");

			record.set_record_entry(attr_index, attr_str);
			attr_index++;
		}
		table.insert_record(record);
	}

	this->database.add_table(table, table_name);
}

double Application::compute_average(string table_name, string attribute_name) {
	Table& get_table = this->database.get_table(table_name);

	vector<string> attributes = get_table.get_attributes();
	int attri_pos = find(attributes.begin(), attributes.end(), attribute_name) - attributes.begin();

	double value = 0;
	double sum_value = 0;
	for (int i = 0; i < get_table.get_size(); i++) {
		value = stod(get_table.return_record(i).get_record_entry(attri_pos));
		sum_value += value;
	}

	sum_value /= get_table.get_size();

	return sum_value;
}

vector<double> Application::compute_range(string table_name, string attribute_name) {
	Table& get_table = this->database.get_table(table_name);

	//vector<string> attributes = get_table.get_attributes();
	//int attri_pos = find(attributes.begin(), attributes.end(), attribute_name) - attributes.begin();

	double min_value = stod(get_table.min(attribute_name));
	double max_value = stod(get_table.max(attribute_name));

	vector<double> range = { min_value, max_value };

	return range;
}

int Application::count_with_reviews(string table_name) {
	
	Table& get_table = this->database.get_table(table_name);

	return get_table.count("review_count");
}



// table operation
Table Application::filter(string select_command, string from_command, string where_command) {
	//string select_command = "";
	//if (from_command == "business") {
	//	select_command = "name,stars,review_count";
	//}
	//else if (from_command == "user") {
	//	select_command = "name,yelping_since";
	//}
	//else if (from_command == "review") {
	//	select_command = "text";
	//}
	Table table = this->database.Query(select_command, from_command, where_command);
	
	return table;
}

Table Application::sort(string table_name, string key_name) {
	Table& table = this->database.get_table(table_name);
	vector<string> attributes = table.get_attributes();
	int attri_pos = find(attributes.begin(), attributes.end(), key_name) - attributes.begin();

	vector<std::pair<string, int>> sort_string;
	vector<std::pair<double, int>> sort_double;

	string str = table.return_record(0).get_record_entry(attri_pos);
	Table sort_table(attributes);
	if (is_number(str)) {
		for (int i = 0; i < table.get_size(); i++) {
			str = table.return_record(i).get_record_entry(attri_pos);
			sort_double.push_back(pair<double, int>(stod(str), i));
		}
		std::sort(sort_double.begin(), sort_double.end());
		std::reverse(sort_double.begin(), sort_double.end());

		for (int i = 0; i < table.get_size(); i++) {
			sort_table.insert_record(table.return_record(sort_double.at(i).second));
		}
	}
	else {
		for (int i = 0; i < table.get_size(); i++) {
			str = table.return_record(i).get_record_entry(attri_pos);
			sort_string.push_back(pair<string, int>(str, i));
		}
		std::sort(sort_string.begin(), sort_string.end());
		std::reverse(sort_string.begin(), sort_string.end());

		for (int i = 0; i < table.get_size(); i++) {
			sort_table.insert_record(table.return_record(sort_string.at(i).second));
		}
	}

	return sort_table;
}

Table Application::review_for_one(string key_name, string key_value) {

	Table& review_table = this->database.get_table("review");
	vector<string> attributes = review_table.get_attributes();
	int attri_pos = find(attributes.begin(), attributes.end(), key_name) - attributes.begin();
	
	Table return_table(attributes);
	Record review_record;
	for (int i = 0; i < review_table.get_size(); i++) {
		review_record = review_table.return_record(i);
		if (review_record.get_record_entry(attri_pos) == key_value) {
			return_table.insert_record(review_record);
		}
	}

	return return_table;
}

Table Application::connect_review() {
	Table return_table;
	Table& review_table = this->database.get_table("review");

	this->import_table("business_review", 2);
	this->import_table("user_review", 100);

	Table& business_review = this->database.get_table("business_review");
	Table& user_review = this->database.get_table("user_review");

	business_review.set_key("business_id");
	user_review.set_key("user_id");

	review_table.set_key("business_id");
	return_table.natural_join(review_table, business_review);

	return_table.set_key("user_id");
	return_table.natural_join(return_table, user_review);

	bool has_read = true;
	if (!has_read) {

	}

	return return_table;
}

Table Application::thin_table(Table& table, vector<string> keep_attri) {
	vector<string> attr = table.get_attributes();
	for (string attri : keep_attri) {
		if (find(keep_attri.begin(), keep_attri.end(), attri) == keep_attri.end()) {
			table.delete_attribute(attri);
		}
	}
	return table;
}
void Application::delete_info(string table_name) {
	this->database.drop_table(table_name);
}

vector<Table> Application::get_all_table() {
	return database.get_tables();
}

// display table
void Application::display_table(Table& table, string table_name) {

	vector<string> attribute = table.get_attributes();

	int entry_width = 25;
	int line_width = int((entry_width + 2) * attribute.size());

	cout << endl << endl;
	cout << center(table_name, line_width) << endl;
	cout << string(line_width, '=') << endl;

	for (string entry : attribute) {
		cout << center(entry, entry_width) << " | ";
	}
	cout << endl;

	cout << string(line_width, '=') << endl;

	int max_display_length = 30;
	int max_print_row = min((int)table.get_size(), 100);
	int max_print_col = min((int)attribute.size(), 6);
	for (int row = 0; row < max_print_row; row++) {
		Record record = table.return_record(row);
		for (int col = 0; col < max_print_col; col++) {
			string attr_value = record.get_record_entry(col);
			if (attr_value.size() < max_display_length) {}
			cout << center(record.get_record_entry(col), entry_width) << " | ";
		}
		cout << endl << std::string(line_width, '-');
		cout << endl;
	}

	cout << endl << endl;
}

void Application::display_all_record(Table& table, string table_name) {

	for (int i = 0; i < table.get_size(); i++) {
		Record record = table.return_record(i);
		if (table_name == "business") {
			this->display_business(record);
		}
		else if (table_name == "user") {
			this->display_user(record);
		}
		else if (table_name == "review") {
			this->display_review(record);
		}
	}
}

void Application::display_business(Record& business_record) {

	int attribute_width = 15;

	cout << endl;
	cout << "--- business record ---" << endl;
	cout << "  " << left << setw(attribute_width) << "name: " << business_record.get_record_entry(9) << endl;
	cout << "  " << left << setw(attribute_width) << "starts: " << business_record.get_record_entry(13) << endl;
	cout << "  " << left << setw(attribute_width) << "reviews: " << business_record.get_record_entry(12) << endl;
	cout << "  " << left << setw(attribute_width) << "address: " << business_record.get_record_entry(0) << endl;
	cout << "  " << left << setw(attribute_width) << " " << business_record.get_record_entry(4) << ", "
		<< business_record.get_record_entry(14) << ", "
		<< business_record.get_record_entry(11) << endl;
		cout << "  " << left << setw(attribute_width) << "is open: " << ((business_record.get_record_entry(6) == "1")? "open" : "closed") << endl;
				 
	cout << "  " << left << setw(attribute_width) << "hours: " << business_record.get_record_entry(5) << endl;
}

void Application::display_user(Record& user_record) {
	int attribute_width = 15;
	
	cout << endl;
	cout << "--- user record ---" << endl;
	cout << endl;
	cout << "  " << left << setw(attribute_width) << "name: " << user_record.get_record_entry(17) << endl;
	cout << "  " << left << setw(attribute_width) << "review count: " << user_record.get_record_entry(18) << endl;
	cout << "  " << left << setw(attribute_width) << "yelping since: " << user_record.get_record_entry(21) << endl;
	cout << "  " << left << setw(attribute_width) << "average stars: " << user_record.get_record_entry(0) << endl;
}

void Application::display_review(Record& review_record) {
	
	vector<string> attributes = this->database.get_table("review").get_attributes();

	string business_id = review_record.get_record_entry(0);
	string user_id = review_record.get_record_entry(8);

	Record business_record = this->get_record("business_review", "business_id", business_id);
	Record user_record = this->get_record("user_review", "user_id", user_id);

	string business_name = (business_record.get_record_size() != 0) ? business_record.get_record_entry(9) : "";
	string user_name = (business_record.get_record_size() != 0) ? user_record.get_record_entry(17) : "";
	int attribute_width = 15;

	cout << endl;
	cout << "--- review record ---" << endl;
	cout << endl;
	cout << "  " << left << setw(attribute_width) << "business: " << business_name << endl;
	cout << "  " << left << setw(attribute_width) << "user: " << user_name << endl;
	cout << "  " << left << setw(attribute_width) << "date: " << review_record.get_record_entry(2) << endl;
	cout << "  " << left << setw(attribute_width) << "stars: " << review_record.get_record_entry(5) << endl;
	cout << endl << "  " << review_record.get_record_entry(6) << endl;
	cout << endl << "  " << left << setw(attribute_width) << "useful: " << review_record.get_record_entry(7) << endl;
}

void Application::display_all_table_name() {
	vector<string> table_name = this->database.list_table();
	
	cout << endl;
	cout << "All Table in Database:" << endl;
	for (string str : table_name) {
		cout << "  " << str << endl;
	}
	cout << endl;
}


// aux function for table printing
string center(const string s, const int w) {
	stringstream ss, spaces;
	// count excess room to pad
	int padding = int(w - s.size());
	for (int i = 0; i<padding / 2; ++i) {
		spaces << " ";
	}
	// format with padding
	ss << spaces.str() << s << spaces.str();
	// if odd #, add 1 space
	if (padding>0 && padding % 2 != 0) {
		ss << " ";
	}
	return ss.str();
}

void removeSubstrs(string& s, string& p) {
	string::size_type n = p.length();
	for (string::size_type i = s.find(p);
		i != string::npos;
		i = s.find(p))
		s.erase(i, n);
}
