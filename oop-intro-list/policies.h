/*
 * policies.h
 *
 *  Created on: Oct 1, 2019
 *      Author: KZ
 */

#ifndef OOP_INTRO_LIST_POLICIES_H_
#define OOP_INTRO_LIST_POLICIES_H_


class Policy {
public:
	virtual bool change_capacity(int size, int& capacity) =0;
};
class GrowPolicy: public Policy {
public:
	bool change_capacity(int size, int& capacity) override ;
};
bool GrowPolicy::change_capacity(int size, int& capacity) {
	if (size == capacity) {
		capacity *=2;
		return true;
	}
	return false;
}

class GrowTriplePolicy: public GrowPolicy {
public:
	bool change_capacity(int size, int& capacity) override {
		if (size == capacity) {
			capacity *=3;
			return true;
		}
		return false;
	}
};

class ShrinkPolicy: public Policy {
public:
	bool change_capacity(int size, int& capacity) override {
		// default shrink policy is to never shrink
		return false;
	}
};

class ShrinkQuarterPolicy: public ShrinkPolicy {
public:
	bool change_capacity(int size, int& capacity) override {
		if (size*4<capacity) {
			capacity = capacity / 2;
			return true;
		}
		return false;
	}
};



#endif /* OOP_INTRO_LIST_POLICIES_H_ */
