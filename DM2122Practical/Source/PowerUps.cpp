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

void PowerUps::setActive(bool active)
{
	active = active;
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

bool PowerUps::getActive()
{
	return active;
}

int PowerUps::getType()
{
	return type;
}