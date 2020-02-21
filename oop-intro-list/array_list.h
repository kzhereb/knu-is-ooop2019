/*
 * array_list.h
 *
 *  Created on: Oct 1, 2019
 *      Author: KZ
 */


#ifndef OOP_INTRO_LIST_ARRAY_LIST_H_
#define OOP_INTRO_LIST_ARRAY_LIST_H_

#include "list.h"
#include "helper.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class ArrayList: public List<T> {
protected:
	int size;
	int capacity;
	T* items;
	const int INITIAL_CAPACITY = 4;

	virtual void grow_capacity();

	int find(T key) {
		for (int i = 0; i < size; i++) {
			if (items[i] == key) {
				return i;
			}
		}
		return -1;
	}

public:
	ArrayList(T first_data) {
		items = new T[INITIAL_CAPACITY];
		items[0] = first_data;
		capacity = INITIAL_CAPACITY;
		size = 1;
	}

	~ArrayList() {
		delete[] items;
	}
	void print(std::ostream& out=std::cout) override {
		for (int i = 0; i < size; i++) {
			out << items[i] << " ";
		}
		out << endl;
	}

	//--------------------------------------------------------
	//додавання елементів в кінець списку 2, 3, ..., nn
	void add(T data) override {
		if (size == capacity) {
			grow_capacity();
		}
		items[size] = data;
		size++;
	}

	//-------------------------------------------------------
	//вставка елемента
	bool insert(T key, T data) override {
		int key_index = find(key);
		if (key_index == -1) { // not found
			return false;
		}
		if (size == capacity) {
			grow_capacity();
		}
		key_index++; //insert after this index
		for (int i = size; i > key_index; i--) {
			items[i] = items[i - 1];
		}
		items[key_index] = data;
		size++;
		return true;
	}
//
//	//-------------------------------------------------------
//	//вилучення елемента
	bool remove(T key) override {
		int key_index = find(key);
		if (key_index == -1) { // not found
			return false;
		}
		for (int i = key_index; i < size - 1; i++) {
			items[i] = items[i + 1];
		}
		size--;
		return true;
	}
};


#include "array_list.hxx"


#endif /* OOP_INTRO_LIST_ARRAY_LIST_H_ */
