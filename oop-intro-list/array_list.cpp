/*
 * array_list.cpp
 *
 *  Created on: Oct 1, 2019
 *      Author: KZ
 */
#include "array_list.h"
#include <vector>

template<typename T>
void ArrayList<T>::grow_capacity() {
	capacity *= 2;
	T* new_items = new T[capacity];
	for (int i = 0; i < size; i++) {
		new_items[i] = items[i];
	}
	delete[] items;
	items = new_items;
}


template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<std::vector<int>>;



