# Database Application

This database application allows people to explore the Yelp review data

## Getting Started

Run the executable file: csce315_tp1_cp4.exe.
This is a demo of the database application.

### Prerequisites

What header files and other standard libs you need

```

#include <iostream>
#include <string>

#include "Database.h"
#include "Record.h"
#include "Table.h"
#include "aux_function.h"
#include "Application.h"

#include "json.h"
```


The open source lib for json file reading and writing are based on json lib developed by Niels Lohmann. For more information, read his website on github

[JSON for Modern C++ 2.1.1](https://nlohmann.github.io/json/)
[README.md](https://github.com/nlohmann/json)


## Application Interface

Description on how to use interface from ```Applicaiton.cpp```

### File Operation

Import data from json and generate json file from database

```
// create an empty application
Application application;

// import data by calling import_table("file_name", record_num);
// number_of_records should not be greater than the total number of records in the file
application.import_table("business", 200);
application.import_table("user", 100);
application.import_table("review", 100);

```

To generate small json file from a big json file with number of starting records

```

// read from file "table_name.json" and generate a short file "table_name_short.json"
application.generate_part_table("business", 50);

```


### Data Statistics

Get a record with minimum attribute value or maximum attribute value in a table

```

// get the user record with minimum review counts
Record user_min_review = application.get_min_max_record("user", "review_count", false);

// get the business with highest star level
Record business_max_review = application.get_min_max_record("business", "review_count", true);
```

Compute range for a given attribute

```

// the first double number is the minimum number and the second one is the largest
vector<double> business_star_range = application.compute_range("business", "stars");
cout << "- Business star range is (" << business_star_range.at(0) << ", " << business_star_range.at(1) << ")" << endl;


// get the number of business with at least one review
cout << "- the number of business with reviews is" << application.count_with_reviews("business") << endl;
```

Computer average value of a given attribute


```

// calculate the average star for all business record
double business_stars_avg = application.compute_average("business", "stars");
cout << "- average value is " << business_stars_avg << endl;
```

### Table Operation

Use filter to select what user want to show under given logic conditions

```

// collect business with star higher than 3.0
Table businesss_tar_gt = application.filter("name,review_count,star,is_open", "business", "stars > 3.0");
application.display_table(businesss_tar_gt, "Business with stars greater that 3.0");

// collect businesss record with review counts more than
Table business_review_count_gt = application.filter("name,review_count,star,is_open", "business", "review_count > 30");
application.display_table(business_review_count_gt, "Business with Review Number Greater than 10");

```

Use sort to sort a existing table in the database

```

// sort business by how many review counts with it
Table business_sort_review = application.sort("business", "review_count");

// sort business by the star level it has
Table business_sort_stars = application.sort("business", "star");

```

To get all reviews for one business or from one use, you can use ```review_for_one```

```

// combine all reviews for one business with test_business_id
Table review_from_one_business = application.review_for_one("business_id", test_business_id);


```

Another way to set all reviews with corresponding business and user is to connect them

```

// natural join review with business table and user table
// this will create a table with all attributes from business and user
Table table = application.connect_review();

```

To delete an existing table in the database

```

// delete a dump table
application.delete_info("dump_table");

```


### Display

There are mainly three kind of display functions, to display table in general form, or display all records in type "business", "user" or "review". 

```

// display the record with minimum review number
Record business_min_review = application.get_min_max_record("business", "review_count", false);
application.display_business(business_min_review);

// display a user record
application.display_user(user_record);

// display all records from one specific table, type should be business, user or review
// display review after connection
Table business_sort_review = application.sort("business", "review_count");
application.display_all_record(business_sort_review, "business");

// display all table name existing in the database
application.display_all_table_name();

```


A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

The project are built in VS2017 environment, to run all predifined tests, you should run execution program directly with all json file in the same directory.

## Interfaces management

These are about all interfaces management and how we use them.

### What interfaces we use

All below are list of interface we use and where to use them.

```
Table Database::Query(string select_command , string from_command , string where_command)
```

Query interface is used in `Application::filter` to set what user want to manage the table

```
void Database::add_table(Table table, string table_name)
```

This function is used in each place when a new table need to be inserted into application database. Before all operation on the table, 'Application::import' will read json file and use this function to add them into database.


```
void Database::drop_table(string table_name)

```

This is used to delete information in database

```
vector<string> Database::list_table()
```

List all name of existing table in the database, `this is used in Application::display_all_table_name()`

```
Table Database::get_table(string table_name)
```

`get_table` is a very commonly used function. At each place we want to seach for a corresponding table in the database, we need to search for them first. Almost all the application funcitons use this interface to access table in database.

```
vector<Table> Database::get_tables()
```

This will return all the table in the database which is used in `Application::get_all_table()`



For Table functions

```
void Table::insert_record(Record record)

vector<string> Table::get_attributes() const

unsigned long int Table::get_size() const

Record Table::return_record(int index)
```

For all functions above, almost every application function uses them. This is because many operation on records and tables need access read and write the table entries.

```
void Table::delete_attribute(string attribute_name)
```

To make table thiner, application has funcitonth 'in_table'  to keep what attributes user want. 'delete_attribute' will delete all other attributes.

```
string Table::max(string attribute_name)
string Table::min(string attribute_name)
```

These two functions are used in 'Application::compute_range' which computes the range for one specific attribute value.

```
void Table::set_key(string attribute_name)
Table Table::natural_join(Table& table_1, Table& table_2)
```

To connect review table with business table and user table, we use natural join in `Table Application::connect_review()` to get name for all review records.



For Record functions

```
Record()

string get_record_entry(int index) const
```
For all functions above, almost every application function uses them. This is because many operation on records and tables need access read and write the table entries.

```
record(int record_size)
```
Used in `Application::import_table`, after retrieving the attribute list from a table, create records with same number of entries

```
int get_record_size() const
```

Get number of entries in a record, used in `Application::display_review` for determining a record is empty or not, if it is not empty, we can access the content of this record

```
void set_record_entry(int index, string record_entry);
```

Used in `Application::import_table`, after a fixed length record was created, fill its entries using this function



Interfaces not used

```
void add_attribute(string attribute_name)
```

reason: database is huge and predefined, add an attribute requires to set all entries of each record in the table.

```
Table cross_join(Table& table_1, Table& table_2)
```

reason: crossjoin combine two separate hierarchies and result in a complex detailed data set, it is not friendly to a large database.

## Notes
Team 43's library file can't be linked to our project, we used our own API.


## Authors

* **Suqian Wang** - ** - [application_ourAPI](https://github.tamu.edu/wangsuqian123/Team-Project-1/tree/master/application_ourAPI)

See also the list of [contributors](https://github.tamu.edu/wangsuqian123/Team-Project-1/graphs/contributors) who participated in this project.

