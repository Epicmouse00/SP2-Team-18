#pragma once
#include "Saving.h"

class Shop
{
private:
	int index;
	bool grey;
	bool cyan;
	bool orange;
	bool red;
	bool green;
public:
	Shop();
	~Shop();

	int getCost();
	int getColour();
	void nextIndex();
	void previousIndex();
	void resetIndex();
	bool isOwned();
	void setOwned();
	bool getColour(int colourIndex);
};