/*
 * singleton.cpp
 *
 *  Created on: Jan 21, 2020
 *      Author: KZ
 */
#include <iostream>
#include <sstream>

//#define CATCH_CONFIG_DISABLE
#include "../unit-testing/catch.hpp"

class Singleton
{
	private:
		int value;
    public:
        static Singleton& getInstance()
        {
            static Singleton    instance{5}; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
        int getValue() { return value;}
        void setValue(int val) {value= val;}
    private:
        Singleton(int param) :value{param} {}                    // Constructor? (the {} brackets) are needed here.
        //~Singleton() {std::cout<<"singleton private destructor"<<std::endl;}  //prevent users from trying to delete instance, should not happen anyway (it is reference)
    public:
        Singleton(Singleton const&) = delete;
        void operator=(Singleton const&) = delete;
};

TEST_CASE("can access singleton through single instance", "[patterns]") {
	REQUIRE(Singleton::getInstance().getValue() == 5);
	int old_value = Singleton::getInstance().getValue();
	SECTION("can change value") {

		Singleton::getInstance().setValue(7);
		REQUIRE(Singleton::getInstance().getValue() == 7);
	}
	SECTION("saving instance") {

		// Singleton instance = Singleton::getInstance(); //ERROR - copy constructor unavailable
		Singleton& instance = Singleton::getInstance();
		instance.setValue(35);
		REQUIRE(Singleton::getInstance().getValue() == 35);
	}

	SECTION("comparing references to instance") {
		Singleton& instance = Singleton::getInstance();
		//REQUIRE(instance == Singleton::getInstance()); //ERROR - operator== not defined
		REQUIRE(&instance == &(Singleton::getInstance()));
	}
	Singleton::getInstance().setValue(old_value); // need to return old value


}

TEST_CASE("can try to delete singleton, but it fails",  "[pattern]") {
	Singleton& instance = Singleton::getInstance();
	Singleton* ptr = &instance;
	REQUIRE(ptr->getValue()==5);
	delete ptr; //UNDEFINED BEHAVIOR
	REQUIRE(Singleton::getInstance().getValue() == 5); //may work or may fail

}


struct TestPrivateDestructor {

	TestPrivateDestructor(std::ostream& out=std::cout): out{out} { out<<"ctor"<<std::endl;}
	void test_method(int value) { out<<value<<std::endl;}

	~TestPrivateDestructor() {out<<"dtor"<<std::endl;} //won't compile if it is private
private:
	std::ostream& out;
};

TEST_CASE("private destructor when going out of scope","[oop]") {
	std::stringstream out;
	{
		TestPrivateDestructor test{out};
		test.test_method(5);
	}
	REQUIRE(out.str() == "ctor\n5\ndtor\n");

}


int main_1() {
	std::cout<<Singleton::getInstance().getValue()<<std::endl;
	Singleton::getInstance().setValue(15);
	std::cout<<Singleton::getInstance().getValue()<<std::endl;
	//Singleton s;
	Singleton& instance = Singleton::getInstance();
	instance.setValue(25);
	std::cout<<Singleton::getInstance().getValue()<<std::endl;
	return 0;
}


