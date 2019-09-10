/*
 * catch_demo.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: KZ
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    CHECK( Factorial(5) == 125 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Factorials are computed again", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(5) == 125 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );

    REQUIRE( Factorial(10) == 3628800 );
}


////#include<iostream>
//int main(int argc, char* argv[]) {
//	//int result = Catch::Session().run( argc, argv );
//	//std::cout<<"Hello world"<<std::endl;
//	return 0;
//}


