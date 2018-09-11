//
//  Course.h
//

#ifndef COURSE_H_
#define COURSE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include"Book.h"

using namespace std;

class Course {
public:
    
    string dpt_code_;
    string course_num_;
    string course_name_;
    // a map stores all class sections of a course
    map<string, SectionClass> map_class_;
    // a map stores pointers point to books assigned to a course
    map<string, Book*> map_book_; // check whether a book is assigned to a class
    
    // default constructor
    Course() {};
    // destructor
    ~Course() {};
    // constructors
    Course(string dpt_code, string course_num): dpt_code_(dpt_code), course_num_(course_num) {};
    Course(string dpt_code, string course_num, string course_name) : dpt_code_(dpt_code), course_num_(course_num), course_name_(course_name) {};
    // overloding == operator
    bool operator == (const Course& course_that) {
        return this->dpt_code_ == course_that.dpt_code_ &&
        this->course_num_ == course_that.course_num_;
    };
    // get course information: department code, course number, course number
    string get_dpt_code() { return this->dpt_code_; };
    string get_course_num() { return this->course_num_; };
    string get_course_name() { return this->course_name_; };
    map<string, Book*> get_dpt_book_() { return map_book_; };
    
    // get min and max costs of all books of a course
    void get_max_min_cost(double& min_cost_sum, double& max_cost_sum, int& available_section);
    // print a course's info
    void print_info();
    // print all book for a course
    void print_all_book();
    
    // assign a book to a class
    void assign_book(string isbn, Book* p_book, string section_num, char is_required);
    // print a class's info
    void print_section_info(string section_num);
    
};

#endif /* COURSE_H_ */
