/*
 * test_factorial.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: KZ
 */

#include "catch.hpp"


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    CHECK( Factorial(2) == 145 );
    CHECK( Factorial(3) == 7 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Factorials are computed again", "[factorial]" ) {
    REQUIRE( Factorial(0) == 0 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 145 );
    REQUIRE( Factorial(10) == 145 );
}
