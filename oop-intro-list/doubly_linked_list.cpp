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
};
//-------------------------
ListNode *first(int);
void add(ListNode **, int);
ListNode *find(ListNode * const, int);
bool remove(ListNode **, ListNode **, int);
ListNode *insert(ListNode * const, ListNode **, int, int);
void list_print(ListNode *);
void list_delete(ListNode *);
//-------------------------
int main() {
	int nn, k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	ListNode *pbeg = first(1); //формування першого елемента списку
	ListNode *pend = pbeg;     //список складаєтьсчя з одного елемента
	ListNode *p;
	//додавання елементів в кінець списку 2, 3, ..., nn
	for (int i = 2; i <= nn; i++)
		add(&pend, i);
	list_print(pbeg);  //виведення списку
	//вставка елемента k після елемента m
	cout << "Insert = ";
	//cin >> k;
	k = 42;
	cout << k << endl;
	cout << "After = ";
	//cin >> m;
	m = 4;
	cout << m << endl;
	p = insert(pbeg, &pend, m, k);
	list_print(pbeg);  //виведення списку
	//вилучення елемента k
	cout << "Delete = ";
	//cin >> k;
	k = 5;
	cout << k << endl;
	if (!remove(&pbeg, &pend, k))
		cout << "no find " << endl;
	list_print(pbeg);  //виведення списку
	list_delete(pbeg);  //знищення списку
	//system("pause");
	return 0;
}
//--------------------------------------------------------
//формування першого елемента списку
ListNode *first(int d) {
	ListNode *pv = new ListNode;
	pv->data = d;
	pv->next = nullptr;
	pv->prev = nullptr;
	return pv;
}
//--------------------------------------------------------
//додавання елементів в кінець списку 2, 3, ..., nn
void add(ListNode **pend, int d) {
	ListNode *pv = new ListNode;
	pv->data = d;
	pv->next = nullptr;
	pv->prev = *pend;
	(*pend)->next = pv;
	*pend = pv;
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
		delete pkey;
		return true;
	}
	return false;
}
//-------------------------------------------------------
//вставка елемента
ListNode *insert(ListNode * const pbeg, ListNode **pend, int key, int d) {
	if (ListNode *pkey = find(pbeg, key)) {
		ListNode *pv = new ListNode;
		pv->data = d;
		pv->next = pkey->next; //зв`язок нового вузла з наступним
		pv->prev = pkey;  //зв`язок нового вузла з попереднім
		pkey->next = pv;  //зв`язок попереднього з новим вузлом
		//зв`язок наступного з новим вузлом
		if (pkey != *pend)
			(pv->next)->prev = pv;
		else
			*pend = pv;  //якщо вузол стає останнім, змінюємо покажчик на кінець
		return pv;
	}
	return nullptr;  //місце для вставки не було знайдено
					 //можна було б реалізовувати іншу обробку
					 //наприклад, вставку в кінець списку,
					 //передбачивши можливу порожність списку
}
//-------------------------------------------------------
//виведення списку
void list_print(ListNode *pbeg) {
	ListNode *pv = pbeg;
	while (pv) {
		cout << pv->data << ' ';
		pv = pv->next;
	}
	cout << endl;
}
//-------------------------------------------------------
//знищення списку
void list_delete(ListNode *pbeg) {
	ListNode *pv;
	while (pbeg) {
		pv = pbeg;
		pbeg = pbeg->next;
		delete pv;
	}
}

