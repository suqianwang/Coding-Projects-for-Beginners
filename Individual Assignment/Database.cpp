//
// Database.cpp
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <iomanip>

#include "Course.h"
#include "Book.h"
#include "Database.h"


using namespace std;

// search and return pointer of a book
Book* Database::search_book(string isbn) {
    auto iter = find(this->vec_book_.begin(), this->vec_book_.end(), Book(isbn));
    return &(*iter);
}

// search and return pointer of a course
Course* Database::search_course(string dpt_code, string course_num) {
    auto iter = find(this->vec_course_.begin(), this->vec_course_.end(), Course(dpt_code, course_num));
    return &(*iter);
}

// define a book
void Database::define_book(string isbn, string title) {
    this->vec_book_.push_back(Book(isbn, title));
}

// define chracteristics of a book

void Database::define_book_author(string isbn, string author) {
    Book* p_book = this->search_book(isbn);
    p_book->set_author(author);
}

void Database::define_book_edition(string isbn, string edition) {
    Book* p_book = this->search_book(isbn);
    
    stringstream ss_edition(edition);
    int i_edition;
    ss_edition >> i_edition;
    p_book->set_edition(i_edition);
}

void Database::define_book_date(string isbn, string date) {
    Book* p_book = this->search_book(isbn);
    p_book->set_date(date);
}

// define the cost for a book
void Database::define_book_cost(string isbn, string cost, string price_type) {
    Book* p_book = this->search_book(isbn);
    stringstream ss_cost(cost);
    double f_cost;
    ss_cost >> f_cost;
    p_book->set_cost(f_cost, price_type.at(0));
}

// define a course
void Database::define_course(string dpt_code, string course_num, string course_name) {
    this->vec_course_.push_back(Course(dpt_code, course_num, course_name));
}

// assign a book to a class
void Database::assign_book_class(string isbn, string dpt_code, string course_num, string section_num, string is_required) {
    Book* p_book = this->search_book(isbn);
    Course* p_course = this->search_course(dpt_code, course_num);
    
    p_course->assign_book(isbn, p_book, section_num, is_required.at(0));
}

// print the books required and optional for all sections of a given course
void Database::print_book_all_section(string dpt_code, string course_num) {
    Course* p_course = this->search_course(dpt_code, course_num);
    p_course->print_info();
    p_course->print_all_book();
}

// print the books required and optional for a given section of a course
void Database::print_book_a_section(string dpt_code, string course_num, string section_num) {
    Course* p_course = this->search_course(dpt_code, course_num);
    p_course->print_section_info(section_num);
}

// print all information known about a particular book
void Database::print_book_info(string isbn) {
    Book* p_book = this->search_book(isbn);
    p_book->print_info();
}

// print a list of defined books
void Database::print_book_list() {
    cout << "BOOK LIST: " << endl << endl;
    for (auto iter : this->vec_book_) {
        iter.print_info();
        cout << endl;
    }
}

// print a given course's information
void Database::print_course_info(string dpt_code, string course_num) {
    Course* p_course = this->search_course(dpt_code, course_num);
    p_course->print_info();
}

// print a list of defined courses
void Database::print_course_list() {
    cout << "COURSE_LIST: " << endl << endl;
    for (auto iter : this->vec_course_) {
        iter.print_info();
        cout << endl;
    }
}

// print all books with known publication dates in the given month/year or later
void Database::print_book_date(string date) {
    string s_month = date.substr(0, 2);
    string s_year = date.substr(3, 7);
    
    stringstream ss_month(s_month);
    stringstream ss_year(s_year);
    
    int year = 0;
    int month = 0;
    ss_month >> month;
    ss_year >> year;
    
    for (auto iter : this->vec_book_) {
        if (iter.get_year() > year || (iter.get_year() == year && iter.get_month() >= month))
            cout <<  " Title: " << iter.get_title() << endl << " ISBN: " << iter.get_isbn() << iter.get_date() << endl << endl;
    }
}

// print all books used in a department
void Database::print_book_a_dpt(string dpt_code) {
    map<string, Book*> map_dpt_book;
    
    for (auto& iter : this->vec_course_) {
        if (iter.get_dpt_code() == dpt_code) {
            map<string, Book*> get_book = iter.get_dpt_book_();
            map_dpt_book.insert(get_book.begin(), get_book.end());
        }
    }
    
    for (auto& iter : map_dpt_book)
        cout << " Title: " << iter.second->get_title() << endl << " ISBN: " << iter.second->get_isbn() << endl << endl;
}

// print the average minimum and maximum cost of all books in a department
void Database::print_book_mim_max_cost_a_dpt(string dpt_code) {
    
    double max_cost_sum = 0;
    double min_cost_sum = 0;
    int available_section = 0;
    
    for (auto& iter : this->vec_course_) {
        
        // find courses in the given department
        if (iter.get_dpt_code() == dpt_code) {
            iter.get_max_min_cost(min_cost_sum, max_cost_sum, available_section);
        }
    }
    
    if (available_section == 0) {
        cout << "NO AVAILABLE COSTS FOR ANY BOOK" << endl;
        return;
    }
    
    cout << "MINIMUM AND MAXIMUM AVERAGE: "<< endl;
    cout << " * " << "MINIMUM AVERAGE = " << min_cost_sum / available_section << endl
    << " * " << "MAXIMUM AVERAGE = " << max_cost_sum / available_section << endl;
}
