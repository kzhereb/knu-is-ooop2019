/*
 * policies.cpp
 *
 *  Created on: Oct 1, 2019
 *      Author: KZ
 */

#include "policies.h"

bool GrowPolicy::change_capacity(int size, int& capacity) {
	if (size == capacity) {
		capacity *=2;
		return true;
	}
	return false;
}


