/*
 * command.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: KZ
 */
#include "../unit-testing/catch.hpp"

class BankAccount {
private:
	int amount;
	int min_amount;
public:
	BankAccount(int amount, int min_amount = 0) :
			amount { amount }, min_amount { min_amount } {
	}

	int get_amount() const {
		return amount;
	}

	bool deposit(int amount) {
		this->amount += amount;
		return true;
	}

	bool withdraw(int amount) {
		if (this->amount - amount < min_amount) {
			return false;
		}
		this->amount -= amount;
		return true;
	}
};

class BankAccountCommand {
public:
	virtual ~BankAccountCommand() {
	}
	virtual bool execute() = 0;
};

class DepositCommand: public BankAccountCommand {
private:
	int amount;
	BankAccount& account;
public:
	DepositCommand(BankAccount& account, int amount) :
			account { account }, amount { amount } {
	}
	bool execute() override {
		return account.deposit(amount);
	}
};

class WithdrawCommand: public BankAccountCommand {
private:
	int amount;
	BankAccount& account;
public:
	WithdrawCommand(BankAccount& account, int amount) :
			account { account }, amount { amount } {
	}
	bool execute() override {
		return account.withdraw(amount);
	}
};


TEST_CASE("working with commands", "[patterns]"){
	BankAccount account{1000,-100};
	DepositCommand command1 {account, 200};
	WithdrawCommand command2 {account, 2000};
	WithdrawCommand command3 {account, 500};

	REQUIRE(account.get_amount()==1000);

	REQUIRE(command1.execute());
	REQUIRE(account.get_amount()==1200);

	REQUIRE(! command2.execute() );
	REQUIRE(account.get_amount()==1200);

	REQUIRE(command3.execute());
	REQUIRE(account.get_amount()==700);

}


