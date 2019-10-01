/*
 * templates_demo.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: KZ
 */
//#define CATCH_CONFIG_DISABLE
#include "catch.hpp"

template<typename T>
int test_func(T data) {
	return 1;
}

int test_func(int data) {
	return 2;
}

TEST_CASE("name resolution","[templates]") {
	int data=145;
	CHECK(test_func(data)==2);
	CHECK(test_func<int>(data)==1);

	float float_data=14.5;
	CHECK(test_func(float_data)==1);
	CHECK(test_func<int>(float_data)==1);
}

