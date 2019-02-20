#include "Shop.h"

Shop::Shop()
{
	index = 0;

	Saving save;
	for (int i = 0; i < 5; ++i)
	{
		car[i] = save.getCar(i);
	}
	equip = save.getEquip();
}

Shop::~Shop()
{
}

int Shop::getCost() const
{
	switch (index)
	{
	case 0:
		return 10;
		break;
	case 1:
		return 20;
		break;
	case 2:
		return 30;
		break;
	case 3:
		return 40;
		break;
	case 4:
		return 50;
		break;
	}
	return 0;
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

bool Shop::isOwned() const
{
	return car[index];
}

void Shop::setOwned()
{
	car[index] = true;
}

bool Shop::getColour(int colourIndex) const
{
	return car[colourIndex];
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
