/*
 * doubly_linked_list.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: KZ
 */
#include "list.h"
#include "helper.h"
#include "array_list.h"
#include "array_list_configurable.h"
#include "doubly_linked_list.h"
#include "policies.h"


#include <iostream>
#include <vector>
using std::cout;
using std::endl;




template<typename T>
T get_test_data(int index) {
	return T { index };
}

template<>
double get_test_data<double>(int index) {
	return index + 0.1;
}

template<typename T>
void test_list(AbstractList<T>* my_list) {
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
int main_list() {
	using std::vector;
	test_doubles();
	test_int_vectors();
	test_int_vector_vectors();

	ArrayList<double>* list1 = new ArrayList<double>(0.1);
	test_list(list1);
	AbstractList<vector<int>>* list2 = new DoublyLinkedList<vector<int>>( { 1, 2 });
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



