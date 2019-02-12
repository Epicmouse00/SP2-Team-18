#include "Currency.h"

Currency::Currency(int amount)
{
	balance = amount;
}

Currency::~Currency()
{
}

void Currency::addBalance(int amount)
{
	balance += amount;
}

void Currency::deductBalance(int amount)
{
	balance -= amount;
}

int Currency::getBalance()
{
	return balance;
}