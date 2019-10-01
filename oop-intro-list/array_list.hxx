/*
 * array_list.hxx
 *
 *  Created on: Oct 1, 2019
 *      Author: KZ
 */
#include "array_list.h"
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




