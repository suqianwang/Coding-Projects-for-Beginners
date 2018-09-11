//
//CmdLineHandler.cpp
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "CmdLineHandler.h"
#include "Database.h"

using namespace std;

void CmdLineHandler::cmd_line_handler(Database& database, string cmd_line) {
	string s_cmd;
	istringstream ss_substring(cmd_line);
	ss_substring >> s_cmd;

	if (s_cmd == "B") {
		string isbn, title;

        // use stringstream to cut isbn off
		ss_substring >> isbn;
		getline(ss_substring, title);
        
        // erase the space before title
		title.erase(0, title.find_first_not_of(" "));
		database.define_book(isbn, title);
	}
	else if (s_cmd == "D") {
		string isbn, char_select, value;
		ss_substring >>isbn >> char_select;
		getline(ss_substring, value);
		value.erase(0, value.find_first_not_of(" "));
		if (char_select == "A")
			database.define_book_author(isbn, value);
		else if (char_select == "E")
			database.define_book_edition(isbn, value);
		else if (char_select == "D")
			database.define_book_date(isbn, value);
	}
	else if (s_cmd == "M") {
		string isbn, cost, price_type;
		ss_substring >> isbn >> cost >> price_type;
		database.define_book_cost(isbn, cost, price_type);
	}
	else if (s_cmd == "C") {
		string dpt_code, course_num, course_name;
		ss_substring >> dpt_code >> course_num;
		getline(ss_substring, course_name);
		course_name.erase(0, course_name.find_first_not_of(" "));

		database.define_course(dpt_code, course_num, course_name);
	}
	else if (s_cmd == "A") {
		string isbn, dpt_code, course_num, section_num, is_required;

		ss_substring >> isbn >> dpt_code >> course_num >> section_num >> is_required;

		database.assign_book_class(isbn, dpt_code, course_num, section_num, is_required);
	}
	else if (s_cmd == "GC") {
		string dpt_code, course_num;
		ss_substring >> dpt_code >> course_num;
		database.print_book_all_section(dpt_code, course_num);
	}
	else if (s_cmd == "GS") {
		string dpt_code, course_num, section_num;
		ss_substring >> dpt_code >> course_num >> section_num;
		database.print_book_a_section(dpt_code, course_num, section_num);
	}
	else if (s_cmd == "GB") {
		string isbn;
		ss_substring >> isbn;
		database.print_book_info(isbn);
	}
	else if (s_cmd == "PB") {
		database.print_book_list();
	}
	else if (s_cmd == "PC") {
		database.print_course_list();
	}
	else if (s_cmd == "PY") {
		string date;
		ss_substring >> date;
		database.print_book_date(date);
	}
	else if (s_cmd == "PD") {
		string dpt_code;
		ss_substring >> dpt_code;
		database.print_book_a_dpt(dpt_code);
	}
	else if (s_cmd == "PM") {
		string dpt_code;
		ss_substring >> dpt_code;
		database.print_book_mim_max_cost_a_dpt(dpt_code);
	}
}
