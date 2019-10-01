/*
 * doubly_linked_list.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: KZ
 */

#include "policies.h"

#include <iostream>
#include <vector>
using std::cout;
using std::endl;

template<typename T>
class List {
public:
	virtual void print()=0;
	virtual void add(T data)=0;
	virtual bool insert(T key, T data)=0;
	virtual bool remove(T key)=0;

};

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
class DoublyLinkedList: public List<T> {
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
	void print() override {
		begin->list_print();
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
	void print() override {
		for (int i = 0; i < size; i++) {
			cout << items[i] << " ";
		}
		cout << endl;
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


template<typename T>
T get_test_data(int index) {
	return T { index };
}

template<>
double get_test_data<double>(int index) {
	return index + 0.1;
}

template<typename T>
void test_list(List<T>* my_list) {
	cout << "Any list" << endl;
	int nn;
	T k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	//ArrayList<double> my_list { 0.1 };

	for (int i = 2; i <= nn; i++)
		my_list->add(get_test_data<T>(i));
	my_list->print();
	//вставка елемента k після елемента m
	cout << "Insert = ";
	//cin >> k;
	k = get_test_data<T>(10);
	cout << k << endl;
	cout << "After = ";
	//cin >> m;
	m = get_test_data<T>(4);
	cout << m << endl;
	my_list->insert(m, k);
	my_list->print();  //виведення списку
	//вилучення елемента k
	cout << "Delete = ";
	//cin >> k;
	k = get_test_data<T>(5);
	cout << k << endl;
	if (!my_list->remove(k))
		cout << "no find " << endl;
	my_list->print();  //виведення списку
}

void test_doubles() {
	cout << "Doubles" << endl;
	double nn, k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	ArrayList<double> my_list { 0.1 };

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
//	//вилучення елемента k
//	cout << "Delete = ";
//	//cin >> k;
//	k = 5.1;
//	cout << k << endl;
//	if (!my_list.remove(k))
//		cout << "no find " << endl;
//	my_list.print();  //виведення списку
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	char sep = ' ';
	for (const T& obj : vec) {
		os << sep << obj;
		sep = ',';
	}
	os << " ]";
	return os;
}

void test_int_vectors() {
	cout << "Int vectors" << endl;
	using std::vector;
	int nn;
	vector<int> k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	ArrayList<vector<int>> my_list { { 1, 4, 5 } };

	for (int i = 2; i <= nn; i++)
		my_list.add( { i, 4, 5 });
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

void test_int_vector_vectors() {
	cout << "Int vector vectors" << endl;
	using std::vector;
	int nn;
	vector<vector<int>> k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	DoublyLinkedList<vector<vector<int>>> my_list { { { 0, 1 }, { 1, 9 } } };

	for (int i = 2; i <= nn; i++)
		my_list.add( { { 0, i }, { i, 9 } });
	my_list.print();
}
//-------------------------
int main() {
	using std::vector;
	test_doubles();
	test_int_vectors();
	test_int_vector_vectors();

	ArrayList<double>* list1 = new ArrayList<double>(0.1);
	test_list(list1);
	List<vector<int>>* list2 = new DoublyLinkedList<vector<int>>( { 1, 2 });
	test_list(list2);

	ArrayListConfigurable<double,GrowTriplePolicy,ShrinkQuarterPolicy>* list3 =
			new ArrayListConfigurable<double,GrowTriplePolicy,ShrinkQuarterPolicy>(0.1);
	test_list(list3);

	bool need_triple = true;
	GrowPolicy* grow_policy = need_triple ? new GrowTriplePolicy: new GrowPolicy;
	bool need_shrink = false;
	ShrinkPolicy* shrink_policy = need_shrink ? new ShrinkQuarterPolicy: new ShrinkPolicy;

	ArrayListConfigurable<double,GrowPolicy,ShrinkPolicy>* list4 =
				new ArrayListConfigurable<double,GrowPolicy,ShrinkPolicy>(0.1,grow_policy, shrink_policy);
	test_list(list4);



	int nn, k, m;
	//визначаємось з кількістю елементів
	cout << "Number = ";
	//cin >> nn;
	nn = 7;
	cout << nn << endl;
	ArrayList<int> my_list { 1 };

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

