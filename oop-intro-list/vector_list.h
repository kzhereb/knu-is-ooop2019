/*
 * vector_list.h
 *
 *  Created on: Mar 6, 2020
 *      Author: KZ
 */

#ifndef OOP_INTRO_LIST_VECTOR_LIST_H_
#define OOP_INTRO_LIST_VECTOR_LIST_H_

#include "list.h"

#include <vector>
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class VectorList: public AbstractList<T> {
private:
	std::vector<T> impl;
public:
	VectorList(T first_data) : impl{first_data} {

	}
	void print(std::ostream& out = std::cout) override {
		for(auto const& item: impl) {
			out << item << " ";
		}
		out << endl;
	}
	void add(T data) override {
		impl.push_back(data);
	}
	bool insert(T key, T data) override {
		auto it = std::find(std::begin(impl), std::end(impl), key);
		if (it == std::end(impl)) {
			return false;
		}
		// our insert() inserts after key; vector insert() inserts before it
		impl.insert(it+1,data);
	}
	bool remove(T key) override {
		//TODO: implement me
		throw std::logic_error("Not implemented");
	}
};




#endif /* OOP_INTRO_LIST_VECTOR_LIST_H_ */
