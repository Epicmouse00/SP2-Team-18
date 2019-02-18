#include "Cursor.h"

Cursor::Cursor()
{
	for (int i = 0; i < 4; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}
	positionIndex = 0;
	numberOfOptions = 4;
}

Cursor::Cursor(int numberOfOptions)
{
	for (int i = 0; i < 4; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}
	positionIndex = 0;
	this->numberOfOptions = numberOfOptions;
}

Cursor::~Cursor()
{

}

void Cursor::addNewPosition(float x, float y, int index)
{
	this->x[index] = x;
	this->y[index] = y;
}

void Cursor::updatePositionIndex(int direction)
{
	if (positionIndex > 0 && direction == -1)
	{
		positionIndex += direction;
	}

	else if (positionIndex < numberOfOptions - 1 && direction == 1)
	{
		positionIndex += direction;
	}
}

float Cursor::getX() const
{
	return x[positionIndex];
}

float Cursor::getY() const
{
	return y[positionIndex];
}

int Cursor::getIndex() const
{
	return positionIndex;
}