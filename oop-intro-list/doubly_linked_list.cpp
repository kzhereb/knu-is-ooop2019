/*
 * doubly_linked_list.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: KZ
 */

#include <iostream>
using std::cout;
using std::endl;

class ListNode {
public:
	int data;
	ListNode *next;
	ListNode *prev;

	//--------------------------------------------------------
	//формування першого елемента списку
	ListNode (int data) {
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}

	ListNode (int data, ListNode* prev, ListNode* next) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}

	//-------------------------------------------------------
	//знищення списку
	~ListNode() {
		if (this->next) {
			delete this->next;
		}

	}

	//-------------------------------------------------------
	//виведення списку
	void list_print() {
		ListNode *pv = this;
		while (pv) {
			cout << pv->data << ' ';
			pv = pv->next;
		}
		cout << endl;
	}


};

ListNode *find(ListNode * const, int);


class DoublyLinkedList {
public:
	ListNode* begin;
	ListNode* end;

	DoublyLinkedList(int first_data) {
		begin = new ListNode(first_data);//формування першого елемента списку
		end = begin;//список складаєтьсчя з одного елемента

	}

	void print() {
		begin->list_print();
	}

	//--------------------------------------------------------
	//додавання елементів в кінець списку 2, 3, ..., nn
	void add(int data) {
		ListNode *pv = new ListNode(data,end,nullptr);

		end->next = pv;
		end = pv;
	}

	//-------------------------------------------------------
	//вставка елемента
	ListNode *insert(int key, int data) {
		if (ListNode *pkey = find(begin, key)) {

			//зв`язок нового вузла з наступним
			//зв`язок нового вузла з попереднім
			ListNode *pv = new ListNode(data,pkey, pkey->next);

			pkey->next = pv;  //зв`язок попереднього з новим вузлом
			//зв`язок наступного з новим вузлом
			if (pkey != end)
				(pv->next)->prev = pv;
			else
				end = pv;  //якщо вузол стає останнім, змінюємо покажчик на кінець
			return pv;
		}
		return nullptr;  //місце для вставки не було знайдено
						 //можна було б реалізовувати іншу обробку
						 //наприклад, вставку в кінець списку,
						 //передбачивши можливу порожність списку
	}
};

//-------------------------



bool remove(ListNode **, ListNode **, int);

//-------------------------
int main() {
	int nn, k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	DoublyLinkedList my_list{1};


	//додавання елементів в кінець списку 2, 3, ..., nn
	for (int i = 2; i <= nn; i++)
		my_list.add(i);
	my_list.print();  //виведення списку
	//вставка елемента k після елемента m
	cout << "Insert = ";
	//cin >> k;
	k = 42;
	cout << k << endl;
	cout << "After = ";
	//cin >> m;
	m = 4;
	cout << m << endl;
	my_list.insert(m, k);
	my_list.print();  //виведення списку
//	//вилучення елемента k
//	cout << "Delete = ";
//	//cin >> k;
//	k = 5;
//	cout << k << endl;
//	if (!remove(&pbeg, &pend, k))
//		cout << "no find " << endl;
//	pbeg->list_print();  //виведення списку
//
//	delete pbeg;  //знищення списку
	//system("pause");
	return 0;
}


//--------------------------------------------------------
//пошук елемента за ключем
ListNode *find(ListNode * const pbeg, int d) {
	ListNode *pv = pbeg;
	while (pv) {
		if (pv->data == d)
			break;
		pv = pv->next;
	}
	return pv;
}
//-------------------------------------------------------
//вилучення елемента
bool remove(ListNode **pbeg, ListNode **pend, int key) {
	if (ListNode *pkey = find(*pbeg, key)) {
		if (pkey == *pbeg) {
			*pbeg = (*pbeg)->next;
			(*pbeg)->prev = nullptr;
		} else if (pkey == *pend) {
			*pend = (*pend)->prev;
			(*pend)->next = nullptr;
		} else {
			(pkey->prev)->next = pkey->next;
			(pkey->next)->prev = pkey->prev;
		}
		pkey->next = nullptr; // HACK: so that entire list is not deleted
		delete pkey;
		return true;
	}
	return false;
}




