//
// Database.h
//

#ifndef DATABASE_H_
#define DATABASE_H_

#include "Course.h"
#include "Book.h"

using namespace std;

class Database {
private:
    vector<Book> vec_book_;
    vector<SectionClass> vec_class_;
    vector<Course> vec_course_;
    
public:
    Database() {};
    ~Database() {};
    
    Book* search_book(string isbn);
    Course* search_course(string dpt_code, string course_num);
    
    // define a book
    void define_book(string isbn, string title);
    void define_book_cost(string isbn, string cost, string price_type);
    void assign_book_class(string isbn, string dpt_num, string course_num, string section_num);
    void define_book_author(string isbn, string author);
    void define_book_edition(string isbn, string edition);
    void define_book_date(string isbn, string date);
    // define a course
    void define_course(string dpt_code, string course_num, string course_name);
    // assign a book to a class
    void assign_book_class(string isbn, string dpt_code, string course_num, string section_num, string is_required);
    
    // print features
    void print_book_all_section(string dpt_code, string course_num);
    void print_book_a_section(string dpt_code, string course_num, string section_num);
    void print_book_info(string isbn);
    void print_book_list();
    void print_course_info(string dpt_code, string course_num);
    void print_course_list();
    void print_book_date(string date);
    void print_book_a_dpt(string dpt_code);
    void print_book_mim_max_cost_a_dpt(string dpt_code);
};

#endif /* DATABASE_H_ */
