#pragma once
#include "Saving.h"

class Shop
{
private:
	int index;
	int equip;
	bool car[5];
public:
	Shop();
	~Shop();

	int getCost() const;
	int getIndex() const;
	void nextIndex();
	void previousIndex();
	void resetIndex();
	bool isOwned() const;
	bool isOwned(int index) const;
	void setOwned();
	bool getColour(int colourIndex) const;
	void setEquip();
	bool isEquip() const;
	int	getEquip() const;
};