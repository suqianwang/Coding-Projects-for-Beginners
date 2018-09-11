//
//  Book.h
//

#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <iostream>
#include <map>

using namespace std;

class Book;
class SectionClass;

class SectionClass {
public:
    map<string, Book*> map_book_;
    map<string, char> map_is_required_;
    string section_num_;
    
    SectionClass() {};
    ~SectionClass() {};
    
    SectionClass(string section_num): section_num_(section_num) {};
    
    double book_cost_max();
    double book_cost_min();
    
    void assign_book(string isbn, Book* p_book, char is_required);
    
    void print_all_book();
};

// Book class definition
class Book {
public:
    string isbn_ = "";
    string title_ = "";
    string author_ = "";
    int edition_ = 0;
    string date_ = "";
    
    int month_ = 0;
    int year_ = 0;
    
    map<char, double> map_cost_;
    
    // flag, whether a  member is set or not
    bool b_isbn_ = false;
    bool b_title_ = false;
    bool b_author_ = false;
    bool b_edition_ = false;
    bool b_date_ = false;
    bool b_cost_ = false;
    
    // constructors
    Book() {};
    Book(string isbn): isbn_(isbn), b_isbn_(true){};
    Book(string isbn, string title): isbn_(isbn), title_(title), b_isbn_(true), b_title_(true){};
    // destructor
    ~Book() {};
    
    bool operator == (const Book& book_that);
    bool operator == (const string& isbn_that);
    
    // access features of Book
    string get_isbn() const { return this->isbn_; };
    string get_title() const { return this->title_; };
    string get_date() const { return this->date_; };
    int get_month() const { return this->month_; };
    int get_year() const { return this->year_; };
    
    // determine if the cost of a book is known or not
    bool is_cost_known() const { return this->b_cost_; };
    
    // the minimum / maximum cost of a book(vary from different version)
    double get_min_cost();
    double get_max_cost();
    
    // define features of Book
    void set_isbn(string isbn) { this->isbn_ = isbn; this->b_isbn_ = true; };
    void set_title(string title) { this->title_ = title; this->b_title_ = true; };
    void set_author(string author) { this->author_ = author; this->b_author_ = true; };
    void set_edition(int edition) { this->edition_ = edition; this->b_edition_ = true; };
    void set_date(string date);
    void set_cost(double cost, char price_type) { this->map_cost_[price_type] = cost; this->b_cost_ = true; };
    
    // print book information
    void print_info();
};

#endif /* BOOK_H_ */
