//
//  Course.cpp
//

#include <stdio.h>
#include <string>
#include <iomanip>

#include "Course.h"
#include "Book.h"

using namespace std;

// get min and max costs of all books of a course
void Course::get_max_min_cost(double& min_cost_sum, double& max_cost_sum, int& available_section) {
    double min_cost = 0;
    double max_cost = 0;
    // iterator iterate through all the classes of a course
    for (auto& iter : this->map_class_) {
        max_cost = iter.second.book_cost_max();
        min_cost = iter.second.book_cost_min();
        if (min_cost != -1) {
            min_cost_sum += min_cost;
            max_cost_sum += max_cost;
            available_section += 1;
        }
    }
}

// print a course's information: department code, course number, and name
void Course::print_info() {
    cout << left << setw(15) << "DPT CODE: " << left << setw(8) << this->dpt_code_ << endl;
    cout << left << setw(15) << "NUMBER: " << left << setw(8) << this->course_num_ << endl;
    cout << left << setw(15) << "NAME: " << left << setw(8) << this->course_name_ << endl;
}

// print all books title and isbn for a given course
void Course::print_all_book() {
    cout << "DPT BOOKS: " << endl;
    for (auto iter = this->map_book_.begin(); iter != this->map_book_.end(); iter++) {
        cout << " Title: " << iter->second->get_title() << endl << " ISBN: " << iter->second->get_isbn() << endl << endl;
    }
}

// assign a book to a class
void Course::assign_book(string isbn, Book* p_book, string section_num, char is_required) {
    this->map_book_[isbn] = p_book;
    
    // find the class(section)
    auto iter = this->map_class_.find(section_num);
    if (iter != this->map_class_.end()) {
        // section has already exist, assign the book to it
        iter->second.assign_book(isbn, p_book, is_required);
    }
    else {
        // section does not exist, add this section, then assign the book to it
        SectionClass section_class(section_num);
        section_class.assign_book(isbn, p_book, is_required);
        this->map_class_.insert(pair<string, SectionClass>(section_num, section_class));
    }
}

// print a section's section number and books assigned to this section
void Course::print_section_info(string section_num) {
    this->print_info();
    cout << left << setw(15) << "SECTION: " << left << setw(8) << section_num << endl;
    this->map_class_[section_num].print_all_book();
}
