/*
 * bridge.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: KZ
 */
#include "../unit-testing/catch.hpp"

#include <vector>
#include <list>
#include <memory>

template<typename T>
class ContainerImpl {
public:
	virtual void add(T item)=0;
	virtual T get(std::size_t index)=0;
	virtual std::size_t size() = 0;
};

template<typename T>
class LinearContainer {
protected:
	std::shared_ptr<ContainerImpl<T>> impl;
public:
	LinearContainer(std::shared_ptr<ContainerImpl<T>> impl): impl{impl} {}
	virtual ~LinearContainer() = default;
	virtual void add(T item) { impl->add(item);}
	virtual std::size_t size()  {return impl->size();}
};



template<typename T>
class List: public LinearContainer<T> {
public:
	List(std::shared_ptr<ContainerImpl<T>> impl): LinearContainer<T>(impl) {}
	T get(std::size_t index) { return this->impl->get(index); }
};

template<typename T>
class Stack: public LinearContainer<T> {
public:
	Stack(std::shared_ptr<ContainerImpl<T>> impl): LinearContainer<T>(impl) {}
	void push(T item) { this->add(item);}
	T peek() {return this->impl->get(this->impl->size()-1); }
};

template<typename T>
class VectorImpl: public ContainerImpl<T> {
private:
	std::vector<T> vec;
public:
	void add(T item) override { vec.push_back(item);}
	T get(std::size_t index) override { return vec[index];}
	std::size_t size() override {return vec.size();}
};

template<typename T>
class LinkedListImpl: public ContainerImpl<T> {
private:
	std::list<T> lst;
public:
	void add(T item) override { lst.push_back(item);}
	T get(std::size_t index) override {
		if (index>=lst.size()) { throw std::invalid_argument("index out of range"); }
		std::size_t current = 0;
		for (const auto& item: lst) {
			if (current == index) { return item;}
			current++;
		}
	}
	std::size_t size() override {return lst.size();}
};


TEST_CASE("working with lists", "[patterns]") {
	List<int>* list = nullptr;
	SECTION("vector impl") {
		list = new List<int> {std::make_shared<VectorImpl<int>>()};
	}
	SECTION("linked list impl") {
		list = new List<int> {std::make_shared<LinkedListImpl<int>>()};
	}
	list->add(1);
	list->add(4);
	list->add(5);
	REQUIRE(list->size() == 3);
	REQUIRE(list->get(1) == 4);
}

TEST_CASE("working with stacks", "[patterns]") {
	Stack<int>* stack=nullptr;
	SECTION("vector impl") {
		stack = new Stack<int> {std::make_shared<VectorImpl<int>>()};
	}
	SECTION("linked list impl") {
		stack = new Stack<int> {std::make_shared<LinkedListImpl<int>>()};
	}
	stack->push(1);
	stack->push(4);
	stack->push(5);
	REQUIRE(stack->size() == 3);
	REQUIRE(stack->peek() == 5);

}



