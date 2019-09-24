/*
 * constructor_demo.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: KZ
 */
#define CATCH_CONFIG_DISABLE
#include "catch.hpp"

#include <vector>
#include <string>
using std::vector;
using std::string;

TEST_CASE("Vector<int> constructors","[oop]") {
	vector<int> vec1{5};
	vector<int> vec2(5);
	CHECK(vec1.size()==1);
	CHECK(vec2.size()==5);

	CHECK(vec1[0]==5);
	CHECK(vec2[0]==0);
	CHECK(vec2[1]==0);
	CHECK(vec2[4]==0);






}

TEST_CASE("Vector<string> constructors","[oop]") {
	vector<string> vec1{"5"};
	//vector<string> vec2((int)"5"); //converts char* to int
	CHECK(vec1.size()==1);


	CHECK(vec1[0]=="5");







}



