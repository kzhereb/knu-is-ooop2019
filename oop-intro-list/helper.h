/*
 * helper.h
 *
 *  Created on: Oct 1, 2019
 *      Author: KZ
 */

#ifndef OOP_INTRO_LIST_HELPER_H_
#define OOP_INTRO_LIST_HELPER_H_
#include <iostream>
#include <vector>

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



#endif /* OOP_INTRO_LIST_HELPER_H_ */
