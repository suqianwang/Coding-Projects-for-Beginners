//
//  test.cpp
//  TP1_CP4
//
//  Created by Susan Wang on 10/16/17.
//  Copyright © 2017 Suqian Wang. All rights reserved.
//

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <stdio.h>

#include "Database.h"
#include "Record.h"
#include "Table.h"
#include "aux_function.h"
#include "Application.h"
#include "json.h"

using namespace std;

int main() {

	Application application;

	application.import_table("business",200);
	application.import_table("user", 200);
	application.import_table("review", 100);
	application.import_table("business_review", 2);
	application.import_table("user_review", 100);

	string test_business_id = "YDf95gJZaq05wvo7hTQbbQ";
	string test_user_id = "lsSiIjAKVl-QRxKjRErBeg";
	string test_review_id = "VfBHSwC5Vz_pbFluy07i9Q";



	// get average star number for all business
	double business_stars_avg = application.compute_average("business", "stars");
	cout << endl << "- average star of all business is " << business_stars_avg << endl;

	system("PAUSE");

	// get business number with at least one review
	int business_number = application.count_with_reviews("business");
	cout << "- The number of business with at least one review: " << business_number << endl;

	system("PAUSE");

	// calculate business star range
	vector<double> business_star_range = application.compute_range("business", "stars");
	cout << "- Business star range is (" << business_star_range.at(0) << ", " << business_star_range.at(1) << ")" << endl;

	system("PAUSE");

	// calculate business review number range
	vector<double> business_review_range = application.compute_range("business", "review_count");
	cout << "- Business review number range is (" << business_review_range.at(0) << ", " << business_review_range.at(1) << ")" << endl;

	system("PAUSE");

	// filter
	Table businesss_tar_gt = application.filter("name,review_count,star,is_open", "business", "stars > 4.0");
	application.display_table(businesss_tar_gt, "Business with stars greater that 4.0");

	system("PAUSE");

	Table business_review_count_gt = application.filter("name,review_count,star,is_open", "business", "review_count > 30");
	application.display_table(business_review_count_gt, "Business with Review Number Greater than 30");

	system("PAUSE");

	// find business and user with minimum and maximum review numbers 
	Record user_min_review = application.get_min_max_record("user", "review_count", false);
	Record business_max_review = application.get_min_max_record("business", "review_count", true);
	
	cout << endl << " Business with most number of reviews " << endl;
	application.display_business(business_max_review);
	
	system("PAUSE");

	cout << endl << " User with minimum number of reviews " << endl;
	application.display_user(user_min_review);
	
	system("PAUSE");

	Table business_sort_star = application.sort("business", "stars");
	application.display_all_record(business_sort_star, "business");
	
	system("PAUSE");

	// connect review with corresponding business and user
	Table table = application.connect_review();
	//application.display_all_record(application.get_table("review"), "review");
	
	// display reviews for one business
	test_business_id = application.get_table("business_review").return_record(0).get_record_entry(0);
	Table review_from_one_business = application.review_for_one("business_id", test_business_id);
	cout << endl << "  All the reviews on this business company" << endl;
	application.display_business(application.get_table("business_review").return_record(0));
	application.display_all_record(review_from_one_business, "review");

	system("PAUSE");
	// display reviews for one user
	test_user_id = application.get_table("user_review").return_record(0).get_record_entry(8);
	Table review_one_user = application.review_for_one("business_id", test_user_id);
	cout << endl << "  All the reviews from this user" << endl;
	application.display_business(application.get_table("user_review").return_record(0));
	application.display_all_record(review_one_user, "review");

	system("PAUSE");
}

