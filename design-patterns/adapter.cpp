/*
 * adapter.cpp
 *
 *  Created on: Mar 6, 2020
 *      Author: KZ
 */

#include "../unit-testing/catch.hpp"
#include "../oop-intro-list/list.h"
#include "../oop-intro-list/array_list.h"
#include "../oop-intro-list/vector_list.h"
#include <string>
#include <sstream>


TEST_CASE("Inserting into list","[patterns]") {
	AbstractList<int>* list = nullptr;
	SECTION("Array List") {
		list = new ArrayList<int>{5};
	}
	SECTION("Vector List") {
		list = new VectorList<int>{5};
	}

	list->insert(5,7);

	std::stringstream out;
	list->print(out);
	REQUIRE(out.str() == "5 7 \n");

}


