/*
 * builder.cpp
 *
 *  Created on: Feb 28, 2020
 *      Author: KZ
 */

#include "../unit-testing/catch.hpp"

#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

class Student {
	friend class StudentBuilder;
	friend std::ostream& operator<<(std::ostream& out, const Student& student) {
		out<<"Name="<<student.name<<std::endl;
		out<<"Group="<<student.group<<std::endl;
		if (student.height != -1) {
			out<<"Height="<<student.height<<std::endl;
		}
		if (student.weight != -1) {
			out<<"Weight="<<student.weight<<std::endl;
		}
		if (student.IQ != -1) {
			out<<"IQ="<<student.IQ<<std::endl;
		}
		if (student.average_grades != -1) {
			out<<"Average grades="<<student.average_grades<<std::endl;
		}
		return out;
	}
private:
	std::string name;
	std::string group;
	int height = -1; //in cm
	int weight = -1; //in kg
	int IQ = -1;
	double average_grades  = -1; // GPA
public:
	Student(std::string name, std::string group) :
			name { name }, group { group } {
	}
};



class StudentBuilder {
private:
	Student student;
public:
	StudentBuilder(std::string name, std::string group) :
		student{name, group} {

	}
	StudentBuilder& setHeight(int height) {
		student.height = height;
		return *this;
	}
	StudentBuilder& setWeight(int weight) {
		student.weight = weight;
		return *this;
	}
	StudentBuilder& setIQ(int IQ) {
		student.IQ = IQ;
		return *this;
	}
	StudentBuilder& setAverageGrades(double average_grades) {
		student.average_grades = average_grades;
		return *this;
	}

	StudentBuilder& setAll(std::unordered_map<std::string,int> const& config) {
		if (config.count("IQ") > 0) {
			student.IQ = config["IQ"];
		}
		if (config.count("height") > 0) {
			student.height = config["height"];
		}
		if (config.count("weight") > 0) {
			student.weight = config["weight"];
		}
	}

	Student getResult() {
		return student;
	}

};

TEST_CASE("creating student using builder", "[patterns]") {
	Student student = StudentBuilder{"Vasyl","K-10"}
								.setHeight(170)
								.setWeight(70)
								.setIQ(120)
								.getResult();

	std::stringstream out;
	out<<student;
	REQUIRE(out.str() == "Name=Vasyl\nGroup=K-10\nHeight=170\nWeight=70\nIQ=120\n");
}

TEST_CASE("creating student without optional fields", "[patterns]") {
	Student student = StudentBuilder{"Vasyl","K-10"}
								.getResult();

	std::stringstream out;
	out<<student;
	REQUIRE(out.str() == "Name=Vasyl\nGroup=K-10\n");
}

TEST_CASE("create unordered_map of strings","[stl]") {
	std::unordered_map<std::string, int> map {{"test",10}};
	REQUIRE(map["test"]==10);
}

TEST_CASE("creating student using map", "[patterns]") {
	//std::unordered_map<std::string, int>
	Student student = StudentBuilder{"Vasyl","K-10"}
								.setAll({{"IQ",120},
										 {"height",170}
										})
								.setAverageGrades(92.5)
								.getResult();

	std::stringstream out;
	out<<student;
	REQUIRE(out.str() == "Name=Vasyl\nGroup=K-10\nHeight=170\nIQ=120\nAverage grades=92.5\n");
}

