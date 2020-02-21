/*
 * singleton.cpp
 *
 *  Created on: Jan 21, 2020
 *      Author: KZ
 */
#include <iostream>

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


