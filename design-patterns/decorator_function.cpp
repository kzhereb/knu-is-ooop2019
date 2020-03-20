/*
 * decorator_function.cpp
 *
 *  Created on: Mar 20, 2020
 *      Author: KZ
 */

#include "../unit-testing/catch.hpp"

#include <ostream>
#include <sstream>
#include <memory>

class Function {
public:
	virtual int calculate(int value) = 0;
	int operator()(int value) { return calculate(value);}
};

class SquareFunction: public Function {
public:
	int calculate(int value) override {
		return value*value;
	}
};

class LoggerFunction: public Function {
private:
	std::shared_ptr<Function> func;
	std::ostream& log;
public:
	LoggerFunction(std::shared_ptr<Function> func,  std::ostream & log):
		func(func),log(log) {}
	int calculate(int value) override {
		log<<"value="<<value<<std::endl;
		int result = func->calculate(value);
		log<<"result="<<result<<std::endl;
		return result;
	}
};

TEST_CASE("function decorators", "[pattern]") {
	std::shared_ptr<Function> square = std::make_shared<SquareFunction>();

	REQUIRE(square->calculate(3)==9);
	std::stringstream log;

	std::shared_ptr<Function> logging_square = std::make_shared<LoggerFunction>(square,log);
	REQUIRE(logging_square->calculate(3)==9);
	REQUIRE(log.str() == "value=3\nresult=9\n");

}

