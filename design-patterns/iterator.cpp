/*
 * iterator.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: KZ
 */
#include "../unit-testing/catch.hpp"

#include <iostream>
#include <cstddef>

class Container {

	class ContainerIterator {
	private:
		std::size_t current_position;
		Container& container;
	public:
		ContainerIterator(std::size_t current_position, Container& container):
			current_position{current_position}, container{container} {}

		ContainerIterator& operator++() {
			current_position +=2;
			return *this;
		}
		int& operator*() {
			return container.array[current_position];
		}
		bool operator!=(const ContainerIterator& other) {
			if ((current_position>=container.size) && (other.current_position>=container.size)) {
				return false;
			}
			return (current_position != other.current_position);
		}
	};
public:
	class OddTraversal {
	private:
		Container& container;
	public:
		OddTraversal(Container& container): container{container} {}
		ContainerIterator begin() { return container.odd_begin();}
		ContainerIterator end() { return container.end();}
	} odd_traversal;

private:
	int* array;
	std::size_t size;
public:
	Container(std::size_t size):size{size}, odd_traversal{*this} {
		array = new int[size];
		for(std::size_t i=0;i<size;i++) {
			array[i] = i;
		}
	}
	~Container() {
		delete [] array;
	}
	ContainerIterator begin() {
		return ContainerIterator{0,*this};
	}
	ContainerIterator odd_begin() {
		return ContainerIterator{1,*this};
	}
	ContainerIterator end() {
		return ContainerIterator{size,*this};
	}
};

TEST_CASE("traversing using iterator","[patterns]") {
	Container array{10};
	std::size_t count = 0;
	for(auto& item:array) {
		std::cout<<item<<std::endl;
		REQUIRE(item==count*2);
		count++;
	}
	REQUIRE(count==5);

	count = 0;
	for(auto& item:array.odd_traversal) {
		std::cout<<item<<std::endl;
		REQUIRE(item==count*2+1);
		count++;
	}
	REQUIRE(count==5);

}






