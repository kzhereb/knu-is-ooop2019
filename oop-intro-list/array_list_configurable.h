/*
 * array_list_configurable.h
 *
 *  Created on: Mar 6, 2020
 *      Author: KZ
 */

#ifndef OOP_INTRO_LIST_ARRAY_LIST_CONFIGURABLE_H_
#define OOP_INTRO_LIST_ARRAY_LIST_CONFIGURABLE_H_

#include "array_list.h"
#include "policies.h"


template<typename T, typename GrowPolicyT, typename ShrinkPolicyT>
class ArrayListConfigurable: public ArrayList<T> {
protected:
	GrowPolicyT* grow_policy;
	ShrinkPolicyT* shrink_policy;
	void grow_capacity() override {
		bool changed = grow_policy->change_capacity(this->size, this->capacity);
		if (!changed) {return;}
		T* new_items = new T[this->capacity];
		for (int i = 0; i < this->size; i++) {
			new_items[i] = this->items[i];
		}
		delete[] this->items;
		this->items = new_items;
	}
	void shrink_capacity() {
		bool changed = shrink_policy->change_capacity(this->size, this->capacity);
		if (!changed) {return;}
		T* new_items = new T[this->capacity];
		for (int i = 0; i < this->size; i++) {
			new_items[i] = this->items[i];
		}
		delete[] this->items;
		this->items = new_items;
	}
public:
	ArrayListConfigurable(T first_data, GrowPolicyT* grow_policy = nullptr,
			ShrinkPolicyT* shrink_policy = nullptr) :
			ArrayList<T> { first_data }, grow_policy { grow_policy }, shrink_policy {
					shrink_policy } {
		if (grow_policy == nullptr) {
			this->grow_policy = new GrowPolicyT;
		}
		if (shrink_policy == nullptr) {
			this->shrink_policy = new ShrinkPolicyT;
		}
	}

	bool remove(T key) override {
		int key_index = this->find(key);
		if (key_index == -1) { // not found
			return false;
		}
		shrink_capacity();
		for (int i = key_index; i < this->size - 1; i++) {
			this->items[i] = this->items[i + 1];
		}
		this->size--;
		return true;
	}

};





#endif /* OOP_INTRO_LIST_ARRAY_LIST_CONFIGURABLE_H_ */
