#include "Cursor.h"

Cursor::Cursor()
{
	initialPosition = 3.0f;
	positionIndex = 0.f;
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

	else if (positionIndex < 2 && direction == 1)
	{
		positionIndex += direction;
	}
}

float Cursor::outputPosition()
{
	return initialPosition + (positionIndex * -3.f);
}