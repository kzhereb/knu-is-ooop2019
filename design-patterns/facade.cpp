/*
 * facade.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: KZ
 */
#include "../unit-testing/catch.hpp"

#include <random>
#include <ctime>

class RandomGenerator {
private:
	std::mt19937 generator;
public:
	RandomGenerator() {
		static std::random_device rd;
		std::seed_seq seq{rd(),(unsigned) time(nullptr)};
		generator = std::mt19937{seq};
	}
	int random_int(int low, int high) {
		std::uniform_int_distribution<int> dist{low,high};
		return dist(generator);
	}
};

TEST_CASE("random numbers are in correct range", "[patterns]") {
	RandomGenerator gen;
	int random_value = gen.random_int(10,20);
	REQUIRE(random_value>=10 );
	REQUIRE(random_value<=20 );
}
