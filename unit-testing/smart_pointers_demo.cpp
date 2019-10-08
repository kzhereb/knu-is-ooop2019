/*
 * smart_pointers_demo.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: KZ
 */

//#define CATCH_CONFIG_DISABLE
#include "catch.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using std::cout;
using std::endl;
using std::vector;
using std::string;

vector<string> global_log;

void log(const string& message) {
	global_log.push_back(message);
	cout << message << endl;

}

class Testable {
private:
	int value;
public:
	Testable() {
		log("Testable ctor");
	}
	int get_value() {return value;}
	void set_value(int val) { value = val;}
	~Testable() {
		log("Testable dtor");
	}
};

TEST_CASE("constructors and destructors", "[constructor]") {
	global_log.clear();
	SECTION("stack allocation"){
		{
			Testable under_test;
			CHECK(global_log.size()==1);
			CHECK(global_log[0]=="Testable ctor");
			under_test.set_value(145);
			CHECK(under_test.get_value()==145);
		}
		CHECK(global_log.size()==2);
		CHECK(global_log[1]=="Testable dtor");
	}
	SECTION("heap allocation"){
		//{
			Testable* under_test = new Testable;
			CHECK(global_log.size()==1);
			CHECK(global_log[0]=="Testable ctor");
			under_test->set_value(145);
			CHECK(under_test->get_value()==145);
			delete under_test;
		//}
		CHECK(global_log.size()==2);
		CHECK(global_log[1]=="Testable dtor");
	}
	SECTION("smart pointer allocation"){
		{
			std::unique_ptr<Testable> under_test =
					std::make_unique<Testable>();
			CHECK(global_log.size()==1);
			CHECK(global_log[0]=="Testable ctor");
			//under_test.set_value(145); //ERROR

			under_test->set_value(145);
			CHECK(under_test->get_value()==145);

			//delete under_test; //ERROR
		}
		CHECK(global_log.size()==2);
		CHECK(global_log[1]=="Testable dtor");
	}

}



