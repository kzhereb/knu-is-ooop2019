/*
 * pointers_demo.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: KZ
 */
#define CATCH_CONFIG_DISABLE
#include "catch.hpp"

#include <string>
#include <stdexcept>

#include <cstring>

using std::string;

class Student {
private:
	string name;
	int age;
	string group;
	int course;
	static const int STUDENT_MIN_AGE = 15;

public:
	Student(string name, int age, string group="", int course=0) :
			name { name }, age { age },
			group { group }, course { course } {

	}
	string get_name() { return name; }
	void set_name(string name) { this->name = name; }

	int get_age() { return age; }
	void set_age(int age) {
		if (age < STUDENT_MIN_AGE) {
			throw std::invalid_argument("age");
		}
		this->age = age;
	}



};

TEST_CASE("Exception","[exception]") {
	Student * student = new Student{"Vasya",13,"K19",1};
	REQUIRE(student->get_name()=="Vasya");
	REQUIRE(student->get_age()==13);
	SECTION("Set correct age") {
		student->set_age(17);
		REQUIRE(student->get_age()==17);
	}
	SECTION("Set wrong age") {
		try {
			student->set_age(12);
		} catch (const std::invalid_argument& exc) {
			REQUIRE(strcmp(exc.what(),"age")==0);
			REQUIRE(student->get_age()==13);
		}

	}
	SECTION("Empty") {

	}
}

void birthday(Student* student) {
	student->set_age(student->get_age()+1);
}

void change_int(int value) {
	value = 42;
}

void change_int_pointer(int* value) {
	*value = 42;
}
void change_int_reference(int& value) {
	value = 45;
}

void replace(Student* student) {
	student = new Student(student->get_name()+" clone",student->get_age()-1);
}

void replace_real(Student** student) {
	*student = new Student((*student)->get_name()+" clone",(*student)->get_age()-1);
}

TEST_CASE("Pointers and pointers to pointers (class)","[pointer]") {
	Student * student = new Student{"Vasya",17,"K19",1};
	SECTION("Pointer - 1*") {
		REQUIRE(student->get_name()=="Vasya");
		REQUIRE(student->get_age()==17);

	}
	SECTION("Pointer without arrow - 1*") {
		REQUIRE((*student).get_name()=="Vasya");
		REQUIRE((*student).get_age()==17);

	}
	SECTION("Pointer to pointer - 2*") {
		Student ** p2p_student = & student;
		REQUIRE((*p2p_student)->get_name()=="Vasya");
		REQUIRE((*p2p_student)->get_age()==17);
		SECTION("Pointer to pointer without arrow - 2*") {
			REQUIRE((**p2p_student).get_name()=="Vasya");
			REQUIRE((**p2p_student).get_age()==17);
		}
	}

	SECTION("birthday" ) {
		birthday(student);
		REQUIRE(student->get_age()==18);
	}
	SECTION("replace" ) {
		replace(student);
		//not changed
		CHECK(student->get_name()=="Vasya");
		CHECK(student->get_age()==17);
	}
	SECTION("replace_real" ) {
		replace_real(&student);
		//not changed
		CHECK(student->get_name()=="Vasya clone");
		CHECK(student->get_age()==16);
	}
	SECTION("change_int") {
		int val = 123;
		change_int(val);
		CHECK(val == 123);
		change_int_pointer(&val);
		CHECK(val == 42);
		change_int_reference(val);
		CHECK(val == 45);
	}
 }

