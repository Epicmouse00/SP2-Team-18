#include "Currency.h"

Currency::Currency()
{
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

int Currency::getBalance() const
{
	return balance;
}

void Currency::setBalance(int amount)
{
	balance = amount;
}