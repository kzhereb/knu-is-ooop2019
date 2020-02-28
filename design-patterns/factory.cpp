/*
 * factory.cpp
 *
 *  Created on: Feb 21, 2020
 *      Author: KZ
 */
//#define CATCH_CONFIG_DISABLE
#include "../unit-testing/catch.hpp"
#include "../oop-intro-list/list.h"
#include "../oop-intro-list/array_list.h"
#include "../oop-intro-list/doubly_linked_list.h"

#include <string>
#include <sstream>

enum class ListType {Array, Linked};

template<typename T>
List<T>* create_list(ListType which, const T& value) {
	if (which == ListType::Linked) {
		return new DoublyLinkedList<T>{value};
	} else if (which == ListType::Array) {
		return new ArrayList<T>{value};
	}
}

TEST_CASE("creating instances based on runtime choice","[patterns]") {
	ListType which = ListType::Array;
	List<int>* list=nullptr;
	if (which == ListType::Linked) {
		list = new DoublyLinkedList<int>{5};
	} else if (which == ListType::Array) {
		list = new ArrayList<int>{5};
	}
	std::stringstream out;
	list->print(out);
	REQUIRE(out.str() == "5 \n");
}

TEST_CASE("creating instances using factory function","[patterns]") {
	ListType which = ListType::Array;
	List<int>* list= create_list(which,5);

	std::stringstream out;
	list->print(out);
	REQUIRE(out.str() == "5 \n");
}



