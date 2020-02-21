/*
 * list.h
 *
 *  Created on: Oct 1, 2019
 *      Author: KZ
 */

#ifndef OOP_INTRO_LIST_LIST_H_
#define OOP_INTRO_LIST_LIST_H_
#include <iostream>


template<typename T>
class List {
public:
	virtual void print(std::ostream& out = std::cout)=0;
	virtual void add(T data)=0;
	virtual bool insert(T key, T data)=0;
	virtual bool remove(T key)=0;

};


#endif /* OOP_INTRO_LIST_LIST_H_ */
