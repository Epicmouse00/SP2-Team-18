#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(int obstacleType)
{
	this->obstacleType = obstacleType;
}

Obstacle::~Obstacle()
{
}

void Obstacle::setX(float x)
{
	this->x = x;
}

void Obstacle::setY(float y)
{
	this->y = y;
}

void Obstacle::setZ(float z)
{
	this->z = z;
}

void Obstacle::setActive(bool active)
{
	this->active = active;
}

float Obstacle::getX() const
{
	return x;
}

float Obstacle::getY() const
{
	return y;
}

float Obstacle::getZ() const
{
	return z;
}

bool Obstacle::getActive()
{
	return active;
}

int Obstacle::getObstacleType()
{
	return obstacleType;
}