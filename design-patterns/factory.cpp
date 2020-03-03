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

class ListFactory {
private:
	ListType which;
public:
    static ListFactory& getInstance()
    {
        static ListFactory    instance{ListType::Array}; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
    void setWhich(ListType which) {
    	this->which = which;
    }
    template <typename T>
    List<T>* createList( const T& value) {
    	if (which == ListType::Linked) {
    		return new DoublyLinkedList<T>{value};
    	} else if (which == ListType::Array) {
    		return new ArrayList<T>{value};
    	}
    }
private:
    ListFactory(ListType which):which{which} {}
public:
    ListFactory(ListFactory const&) = delete;
    void operator=(ListFactory const&) = delete;

};

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

TEST_CASE("creating instances using factory class","[patterns]") {
	ListType which = ListType::Linked;
	ListFactory::getInstance().setWhich(which);
	List<int>* list= ListFactory::getInstance().createList(5);

	std::stringstream out;
	list->print(out);
	REQUIRE(out.str() == "5 \n");
}



