#include "Obstacle.h"

unsigned int Obstacle::noObstacle = 0;

Obstacle::Obstacle()
{
	noObstacle++;
}

Obstacle::Obstacle(int obstacleType)
{
	noObstacle++;
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

float Obstacle::getX()
{
	return x;
}

float Obstacle::getY()
{
	return y;
}

float Obstacle::getZ()
{
	return z;
}

unsigned int Obstacle::getNoObstacle()
{
	return noObstacle;
}