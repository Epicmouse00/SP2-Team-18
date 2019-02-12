#pragma once
class Currency
{
private:
	int balance;
public:
	Currency(int amount);
	~Currency();

	void addBalance(int amount);
	void deductBalance(int amount);
	int getBalance();
};