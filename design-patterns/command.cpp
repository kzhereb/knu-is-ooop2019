/*
 * command.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: KZ
 */
#include "../unit-testing/catch.hpp"
#include <vector>
#include <iostream>
#include <memory>

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

class MacroCommand: public BankAccountCommand {
private:
	std::vector<std::shared_ptr<BankAccountCommand>> commands;
public:
	MacroCommand(std::initializer_list<std::shared_ptr<BankAccountCommand>> const& commands):
		commands{commands} {}
	bool execute() override {
		std::size_t size = commands.size();
		for(std::size_t i = 0; i<size;i++) {
			if (! commands[i]->execute()) {
				this->execution_succeeded = false;
				for (std::size_t j=i-1; j>=0; j--) {
					commands[j]->undo();
					if (j==0) {break;}
				}
				return false;
			}
		}
		this->execution_succeeded = true;
		return true;
	}

	bool undo() override {
		if (! this->execution_succeeded) {return false;}
		std::size_t size = commands.size();
		for (std::size_t i = size-1;i>=0; i--) {
			commands[i]->undo();
			if (i==0) {break;}
		}
		return true;
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

	SECTION("Macro command") {
		MacroCommand macro{std::make_shared<DepositCommand>(account,200),
			std::make_shared<WithdrawCommand>(account,500)};
		REQUIRE(account.get_amount()==1000);

		REQUIRE(macro.execute());
		REQUIRE(account.get_amount()==700);

		REQUIRE(macro.undo());
		REQUIRE(account.get_amount()==1000);

	}

	SECTION("Macro command fails") {
		MacroCommand macro{std::make_shared<DepositCommand>(account,200),
			std::make_shared<WithdrawCommand>(account,2000),
			std::make_shared<WithdrawCommand>(account,500)};
		REQUIRE(account.get_amount()==1000);

		REQUIRE_FALSE(macro.execute());
		REQUIRE(account.get_amount()==1000);

		REQUIRE_FALSE(macro.undo());
		REQUIRE(account.get_amount()==1000);

	}

}


