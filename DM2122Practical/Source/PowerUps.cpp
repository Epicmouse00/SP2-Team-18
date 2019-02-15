#include "PowerUps.h"

PowerUps::PowerUps()
{
	type = rand() % 4;
}

PowerUps::~PowerUps()
{
}

void PowerUps::setX(float setX)
{
	x = setX;
}

void PowerUps::setY(float setY)
{
	y = setY;
}

void PowerUps::setZ(float setZ)
{
	z = setZ;
}

float PowerUps::getX()
{
	return x;
}

float PowerUps::getY()
{
	return y;
}

float PowerUps::getZ()
{
	return z;
}

int PowerUps::getType()
{
	return type;
}