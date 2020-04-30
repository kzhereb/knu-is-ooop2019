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
protected:
	bool execution_succeeded = false;
public:
	virtual ~BankAccountCommand() {
	}
	virtual bool execute() = 0;
	virtual bool undo() = 0;
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
		this->execution_succeeded = account.deposit(amount);
		return this->execution_succeeded;
	}
	bool undo() override {
		if(! this->execution_succeeded) {return false;}
		return account.withdraw(amount);
	}
};

class WithdrawCommand: public BankAccountCommand {
private:
	BankAccount& account;
	int amount;
public:
	WithdrawCommand(BankAccount& account, int amount) :
			account { account }, amount { amount } {
	}
	bool execute() override {
		this->execution_succeeded = account.withdraw(amount);
		return this->execution_succeeded;
	}
	bool undo() override {
		if(! this->execution_succeeded) {return false;}
		return account.deposit(amount);
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

	REQUIRE_FALSE( command2.execute() );
	REQUIRE(account.get_amount()==1200);

	REQUIRE(command3.execute());
	REQUIRE(account.get_amount()==700);

	REQUIRE(command3.undo());
	REQUIRE(account.get_amount()==1200);

	REQUIRE_FALSE( command2.undo());
	REQUIRE(account.get_amount()==1200);

	REQUIRE(command1.undo());
	REQUIRE(account.get_amount()==1000);

}


