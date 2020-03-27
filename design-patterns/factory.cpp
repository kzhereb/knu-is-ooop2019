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
#include "../oop-intro-list/array_list_configurable.h"

#include <string>
#include <sstream>
#include <memory>


enum class ListType {Array, Linked};

template<typename T>
AbstractList<T>* create_list(ListType which, const T& value) {
	if (which == ListType::Linked) {
		return new DoublyLinkedList<T>{value};
	} else if (which == ListType::Array) {
		return new ArrayList<T>{value};
	}
}

class ListFactorySingleton {
private:
	ListType which;
public:
    static ListFactorySingleton& getInstance()
    {
        static ListFactorySingleton    instance{ListType::Array}; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
    void setWhich(ListType which) {
    	this->which = which;
    }
    template <typename T>
    AbstractList<T>* createList( const T& value) {
    	if (which == ListType::Linked) {
    		return new DoublyLinkedList<T>{value};
    	} else if (which == ListType::Array) {
    		return new ArrayList<T>{value};
    	}
    }
private:
    ListFactorySingleton(ListType which):which{which} {}
public:
    ListFactorySingleton(ListFactorySingleton const&) = delete;
    void operator=(ListFactorySingleton const&) = delete;

};

template <typename T>
class ListFactory {
public:
	virtual AbstractList<T>* createList( const T& value) = 0;
	virtual ~ListFactory() {}
};

template <typename T>
class ArrayListFactory: public ListFactory<T> {
public:
	AbstractList<T>* createList( const T& value) override {
		return new ArrayList<T>{value};
	}
};

template <typename T>
class DoublyLinkedListFactory: public ListFactory<T> {
public:
	AbstractList<T>* createList( const T& value) override {
		return new DoublyLinkedList<T>{value};
	}
};

template <typename T>
class ArrayListConfigurableFactory: public ListFactory<T> {
private:
	GrowPolicy* grow_policy = nullptr;
	ShrinkPolicy* shrink_policy = nullptr;
public:
	AbstractList<T>* createList( const T& value) override {
		return new ArrayListConfigurable<T,
				GrowPolicy,
				ShrinkPolicy>{value,grow_policy,shrink_policy};
	}

	void setGrowPolicy(GrowPolicy* grow_policy) {
		this->grow_policy = grow_policy;
	}

	void setShrinkPolicy(ShrinkPolicy* shrink_policy) {
		this->shrink_policy = shrink_policy;
	}


};

TEST_CASE("creating instances based on runtime choice","[patterns]") {
	ListType which = ListType::Array;
	AbstractList<int>* list=nullptr;
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
	AbstractList<int>* list= create_list(which,5);

	std::stringstream out;
	list->print(out);
	REQUIRE(out.str() == "5 \n");
}

TEST_CASE("creating instances using factory singleton","[patterns]") {
	ListType which = ListType::Linked;
	ListFactorySingleton::getInstance().setWhich(which);
	AbstractList<int>* list= ListFactorySingleton::getInstance().createList(5);

	std::stringstream out;
	list->print(out);
	REQUIRE(out.str() == "5 \n");
}

TEST_CASE("creating instances using abstract factory","[patterns]") {

	ArrayListConfigurableFactory<int> * factory_ptr = new ArrayListConfigurableFactory<int>();
	factory_ptr->setGrowPolicy(new GrowTriplePolicy);
	std::unique_ptr<ListFactory<int>> factory {factory_ptr};


	AbstractList<int>* list= factory->createList(5);

	std::stringstream out;
	list->print(out);
	REQUIRE(out.str() == "5 \n");
}



