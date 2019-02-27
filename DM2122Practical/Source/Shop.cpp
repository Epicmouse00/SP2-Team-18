#include "Shop.h"

Shop::Shop()
{
	index = 0;
	for (int i = 0; i < 5; ++i)
	{
		car[i] = false;
	}
	equip = 0;
	balance = 0;
}

Shop::~Shop()
{
}

void Shop::loadCarData(bool ownedCar, int index)
{
	car[index] = ownedCar;
}

void Shop::loadNumberData(int equip, int balance)
{
	this->equip = equip;
	this->balance = balance;
}

int Shop::getCost() const
{
	switch (index)
	{
	case 1:
		return 200;
		break;
	case 2:
		return 250;
		break;
	case 3:
		return 300;
		break;
	case 4:
		return 500;
		break;
	default:
		return 0;
		break;
	}
}

int Shop::getIndex() const
{
	return index;
}

void Shop::nextIndex()
{
	if (index < 4)
	{
		index++;
	}
}

void Shop::previousIndex()
{
	if (index > 0)
	{
		index--;
	}
}

void Shop::resetIndex()
{
	index = 0;
}

bool Shop::isOwned(int index) const
{
	return car[index];
}

void Shop::setOwned(int index)
{
	car[index] = true;
}

void Shop::setEquip()
{
	equip = index;
}

bool Shop::isEquip() const
{
	return (equip == index);
}

int Shop::getEquip() const
{
	return equip;
}

int Shop::getBalance() const
{
	return balance;
}

void Shop::setBalance(int balance)
{
	this->balance = balance;
}
