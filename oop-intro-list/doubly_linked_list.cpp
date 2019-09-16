/*
 * doubly_linked_list.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: KZ
 */

#include <iostream>
using namespace std;

struct Node {
	int dat;
	Node *next;
	Node *prev;
};
//-------------------------
Node *first(int);
void add(Node **, int);
Node *find(Node * const, int);
bool remove(Node **, Node **, int);
Node *insert(Node * const, Node **, int, int);
void lprint(Node *);
void ldel(Node *);
//-------------------------
int main() {
	int nn, k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	cin >> nn;
	cout << endl;
	Node *pbeg = first(1); //формування першого елемента списку
	Node *pend = pbeg;     //список складаєтьсчя з одного елемента
	Node *p;
	//додавання елементів в кінець списку 2, 3, ..., nn
	for (int i = 2; i <= nn; i++)
		add(&pend, i);
	lprint(pbeg);  //виведення списку
	//вставка елемента k після елемента m
	cout << "Insert = ";
	cin >> k;
	cout << endl;
	cout << "After = ";
	cin >> m;
	cout << endl;
	p = insert(pbeg, &pend, m, k);
	lprint(pbeg);  //виведення списку
	//вилучення елемента k
	cout << "Delete = ";
	cin >> k;
	cout << endl;
	if (!remove(&pbeg, &pend, k))
		cout << "no find " << endl;
	lprint(pbeg);  //виведення списку
	ldel(pbeg);  //знищення списку
	system("pause");
	return 0;
}
//--------------------------------------------------------
//формування першого елемента списку
Node *first(int d) {
	Node *pv = new Node;
	pv->dat = d;
	pv->next = NULL;
	pv->prev = NULL;
	return pv;
}
//--------------------------------------------------------
//додавання елементів в кінець списку 2, 3, ..., nn
void add(Node **pend, int d) {
	Node *pv = new Node;
	pv->dat = d;
	pv->next = NULL;
	pv->prev = *pend;
	(*pend)->next = pv;
	*pend = pv;
}
//--------------------------------------------------------
//пошук елемента за ключем
Node *find(Node * const pbeg, int d) {
	Node *pv = pbeg;
	while (pv) {
		if (pv->dat == d)
			break;
		pv = pv->next;
	}
	return pv;
}
//-------------------------------------------------------
//вилучення елемента
bool remove(Node **pbeg, Node **pend, int key) {
	if (Node *pkey = find(*pbeg, key)) {
		if (pkey == *pbeg) {
			*pbeg = (*pbeg)->next;
			(*pbeg)->prev = NULL;
		} else if (pkey == *pend) {
			*pend = (*pend)->prev;
			(*pend)->next = NULL;
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
Node *insert(Node * const pbeg, Node **pend, int key, int d) {
	if (Node *pkey = find(pbeg, key)) {
		Node *pv = new Node;
		pv->dat = d;
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
	return NULL;  //місце для вставки не було знайдено
				  //можна було б реалізовувати іншу обробку
				  //наприклад, вставку в кінець списку,
				  //передбачивши можливу порожність списку
}
//-------------------------------------------------------
//виведення списку
void lprint(Node *pbeg) {
	Node *pv = pbeg;
	while (pv) {
		cout << pv->dat << ' ';
		pv = pv->next;
	}
	cout << endl;
}
//-------------------------------------------------------
//знищення списку
void ldel(Node *pbeg) {
	Node *pv;
	while (pbeg) {
		pv = pbeg;
		pbeg = pbeg->next;
		delete pv;
	}
}

