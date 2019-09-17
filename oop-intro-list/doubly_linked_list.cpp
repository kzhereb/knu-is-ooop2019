/*
 * doubly_linked_list.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: KZ
 */

#include <iostream>
#include <vector>
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
template<typename T>
ListNode<T> *find(ListNode<T> * const, T);

template<typename T>
class DoublyLinkedList {
private:
	ListNode<T>* begin;
	ListNode<T>* end;
public:
	DoublyLinkedList(T first_data) {
		begin = new ListNode<T>(first_data);//формування першого елемента списку
		end = begin;	//список складаєтьсчя з одного елемента

	}

	void print() {
		begin->list_print();
	}

	//--------------------------------------------------------
	//додавання елементів в кінець списку 2, 3, ..., nn
	void add(T data) {
		ListNode<T> *pv = new ListNode<T>(data, end, nullptr);

		end->next = pv;
		end = pv;
	}

	//-------------------------------------------------------
	//вставка елемента
	ListNode<T> *insert(T key, T data) {
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
			return pv;
		}
		return nullptr;  //місце для вставки не було знайдено
						 //можна було б реалізовувати іншу обробку
						 //наприклад, вставку в кінець списку,
						 //передбачивши можливу порожність списку
	}

	//-------------------------------------------------------
	//вилучення елемента
	bool remove(T key) {
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
			pkey->next = nullptr; // HACK: so that entire list is not deleted
			delete pkey;
			return true;
		}
		return false;
	}
};

void test_doubles() {
	cout<<"Doubles"<<endl;
	double nn, k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	DoublyLinkedList<double> my_list { 0.1 };

	for (double i = 1.1; i <= nn; i++)
		my_list.add(i);
	my_list.print();
	//вставка елемента k після елемента m
	cout << "Insert = ";
	//cin >> k;
	k = 4.2;
	cout << k << endl;
	cout << "After = ";
	//cin >> m;
	m = 2.1;
	cout << m << endl;
	my_list.insert(m, k);
	my_list.print();  //виведення списку
	//вилучення елемента k
	cout << "Delete = ";
	//cin >> k;
	k = 5.1;
	cout << k << endl;
	if (!my_list.remove(k))
		cout << "no find " << endl;
	my_list.print();  //виведення списку
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os<<"[";
	char sep = ' ';
	for(const T& obj : vec) {
		os<<sep<<obj;
		sep = ',';
	}
	os<<" ]";
	return os;
}

void test_int_vectors() {
	cout<<"Int vectors"<<endl;
	using std::vector;
	int nn;
	vector<int> k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	DoublyLinkedList<vector<int>> my_list { { 1,4,5} };

	for (int i = 2; i <= nn; i++)
		my_list.add({i,4,5});
	my_list.print();

//	//вставка елемента k після елемента m
//	cout << "Insert = ";
//	//cin >> k;
//	k = 4.2;
//	cout << k << endl;
//	cout << "After = ";
//	//cin >> m;
//	m = 2.1;
//	cout << m << endl;
//	my_list.insert(m, k);
//	my_list.print();  //виведення списку
//	//вилучення елемента k
//	cout << "Delete = ";
//	//cin >> k;
//	k = 5.1;
//	cout << k << endl;
//	if (!my_list.remove(k))
//		cout << "no find " << endl;
//	my_list.print();  //виведення списку
}

//-------------------------
int main() {
	test_doubles();
	test_int_vectors();

	int nn, k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	DoublyLinkedList<int> my_list { 1 };

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
	//вилучення елемента k
	cout << "Delete = ";
	//cin >> k;
	k = 5;
	cout << k << endl;
	if (!my_list.remove(k))
		cout << "no find " << endl;
	my_list.print();  //виведення списку
//
//	delete pbeg;  //знищення списку
	//system("pause");
	return 0;
}

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

