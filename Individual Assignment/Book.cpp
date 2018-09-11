//
//  Book.cpp
//

#include <stdio.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Book.h"

using namespace std;

// get sum of minimum cost in one section, if none available, return -1
double SectionClass::book_cost_min() {
    bool is_any_cost = false;
    double min_cost_sum = 0;
    for (auto& iter : this->map_is_required_) {
        if (iter.second == 'R') {
            Book* p_book = this->map_book_[iter.first];
            if (p_book->is_cost_known()) {
                is_any_cost = true;
                min_cost_sum += p_book->get_min_cost();
            }
        }
    }
    
    if (is_any_cost) return min_cost_sum;
    else return -1;
}

// get sum of maximum cost in one section, if none available, return -1
double SectionClass::book_cost_max() {
    bool is_any_cost = false;
    double max_cost_sum = 0;
    for (auto& iter : this->map_book_) {
        Book* p_book = iter.second;
        if (p_book->is_cost_known()) {
            is_any_cost = true;
            max_cost_sum += p_book->get_max_cost();
        }
    }
    
    if (is_any_cost) return max_cost_sum;
    else return -1;
}

// assign a book to a section
void SectionClass::assign_book(string isbn, Book* p_book, char is_required) {
    this->map_book_[isbn] = p_book;
    this->map_is_required_[isbn] = is_required;
}

// print all books of a section
void SectionClass::print_all_book() {
    cout << "SECTION BOOKS:" << endl;
    for (auto iter = this->map_book_.begin(); iter != this->map_book_.end(); iter++) {
        cout << " Title: " << iter->second->get_title() << endl << " ISBN: " << iter->second->get_isbn() << endl << endl;
    }
}

// get minimum cost of a book, if no available cost, return -1;
double Book::get_min_cost() {
    if (!this->b_cost_) return -1;
    
    double min_cost = this->map_cost_.begin()->second;
    for (auto& iter : this->map_cost_)
        if (iter.second < min_cost)
            min_cost = iter.second;
    return min_cost;
}

// get maximum cost of a book, if no available cost, return -1;
double Book::get_max_cost() {
    if (!this->b_cost_) return -1;
    
    double max_cost = this->map_cost_.begin()->second;
    
    for (auto& iter : this->map_cost_)
        if (iter.second > max_cost)
            max_cost = iter.second;
    return max_cost;
}

bool Book::operator == (const Book& book_that) {
    return this->isbn_ == book_that.get_isbn();
}

bool Book::operator == (const string& isbn_that) {
    return this->isbn_ == isbn_that;
}

void Book::set_date(string date) {
    
    // convert string date into int month and year
    this->b_date_ = true;
    this->date_ = date;
    string s_month = date.substr(0, 3);
    string s_year = date.substr(3, 7);
    
    stringstream ss_month(s_month);
    stringstream ss_year(s_year);
    
    ss_month >> this->month_;
    ss_year >> this->year_;
}

// print all available information of a book
void Book::print_info() {
    if (this->b_isbn_)		cout << left << setw(15) << "ISBN: " << right << setw(8) << this->isbn_ << endl;
    if (this->b_title_)		cout << left << setw(15) << "TITLE: " << right << setw(8) << this->title_ << endl;
    if (this->b_edition_)	cout << left << setw(15) << "EDITION: " << left << setw(8) << this->edition_ << endl;
    if (this->b_author_)	cout <<  left << setw(15) << "AUTHOR: " << right << setw(8) << this->author_ << endl;
    if (this->b_date_)		cout <<  left << setw(15) << "DATE: " << right << setw(7) << this->date_ <<endl;
    if (this->b_cost_) {
        cout <<  left << setw(15) << "COST: ";
        for (auto iter = this->map_cost_.begin(); iter != this->map_cost_.end(); iter++)
            cout << iter->second << "(" << iter->first << ")" << " ";
        cout << endl;
    }
}
