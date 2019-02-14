#include "Cursor.h"

Cursor::Cursor()
{
	initialPosition = 0.f;
	spacing = -1.f;
	numberOfOptions = 1;
	positionIndex = 0;
}

Cursor::Cursor(float initialPosition, float spacing, int numberOfOptions)
{
	this->initialPosition = initialPosition;
	this->spacing = spacing;
	this->numberOfOptions = numberOfOptions;
	positionIndex = 0;
}

Cursor::~Cursor()
{

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

float Cursor::outputPosition()
{
	return initialPosition + (positionIndex * spacing);
}

int Cursor::getIndex() const
{
	return positionIndex;
}