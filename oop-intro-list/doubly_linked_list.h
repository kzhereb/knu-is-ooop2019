/*
 * doubly_linked_list.h
 *
 *  Created on: Feb 21, 2020
 *      Author: KZ
 */

#ifndef OOP_INTRO_LIST_DOUBLY_LINKED_LIST_H_
#define OOP_INTRO_LIST_DOUBLY_LINKED_LIST_H_
#include "list.h"

#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class ListNode {
public:
	T data;
	ListNode<T> *next;
	ListNode<T> *prev;

	//--------------------------------------------------------
	//формування першого елемента списку
	ListNode(T data) {
		//TODO: pass by const ref
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}

	ListNode(T data, ListNode<T>* prev, ListNode<T>* next) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}

	//-------------------------------------------------------
	//знищення списку
	~ListNode() {
	}

	//-------------------------------------------------------
	//виведення списку
	void list_print(std::ostream& out = std::cout) {
		ListNode *pv = this;
		while (pv) {
			out << pv->data << ' ';
			pv = pv->next;
		}
		out << endl;
	}

};
template<typename T>
ListNode<T> *find(ListNode<T> * const, T);

template<typename T>
class DoublyLinkedList: public AbstractList<T> {
private:
	ListNode<T>* begin;
	ListNode<T>* end;
public:
	DoublyLinkedList(T first_data) {
		begin = new ListNode<T>(first_data);//формування першого елемента списку
		end = begin;	//список складаєтьсчя з одного елемента

	}

	~DoublyLinkedList() {
		ListNode<T> *current = begin, *to_delete;
		while (current) {
			to_delete = current;
			current = current->next;
			delete to_delete;
		}
	}
	void print(std::ostream& out = std::cout) override {
		begin->list_print(out);
	}

	//--------------------------------------------------------
	//додавання елементів в кінець списку 2, 3, ..., nn
	void add(T data) override {
		ListNode<T> *pv = new ListNode<T>(data, end, nullptr);

		end->next = pv;
		end = pv;
	}

	//-------------------------------------------------------
	//вставка елемента
	bool insert(T key, T data) override {
		if (ListNode<T> *pkey = find(begin, key)) {

			//зв`язок нового вузла з наступним
			//зв`язок нового вузла з попереднім
			ListNode<T> *pv = new ListNode<T>(data, pkey, pkey->next);

			pkey->next = pv;  //зв`язок попереднього з новим вузлом
			//зв`язок наступного з новим вузлом
			if (pkey != end)
				(pv->next)->prev = pv;
			else
				end = pv; //якщо вузол стає останнім, змінюємо покажчик на кінець
			return true;
		}
		return false;  //місце для вставки не було знайдено
					   //можна було б реалізовувати іншу обробку
					   //наприклад, вставку в кінець списку,
					   //передбачивши можливу порожність списку
	}

	//-------------------------------------------------------
	//вилучення елемента
	bool remove(T key) override {
		if (ListNode<T> *pkey = find(begin, key)) {
			if (pkey == begin) {
				begin = begin->next;
				begin->prev = nullptr;
			} else if (pkey == end) {
				end = end->prev;
				end->next = nullptr;
			} else {
				(pkey->prev)->next = pkey->next;
				(pkey->next)->prev = pkey->prev;
			}
			delete pkey;
			return true;
		}
		return false;
	}
};

//--------------------------------------------------------
//пошук елемента за ключем
template<typename T>
ListNode<T> *find(ListNode<T> * const pbeg, T d) {
	ListNode<T> *pv = pbeg;
	while (pv) {
		if (pv->data == d)
			break;
		pv = pv->next;
	}
	return pv;
}




#endif /* OOP_INTRO_LIST_DOUBLY_LINKED_LIST_H_ */
