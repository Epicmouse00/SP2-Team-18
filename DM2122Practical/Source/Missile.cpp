#include "Missile.h"

Missile::Missile()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	shot = false;
	hit = false;
}

Missile::~Missile()
{
}

void Missile::setXYZ(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Missile::getX()
{
	return x;
}

float Missile::getY()
{
	return y;
}

float Missile::getZ()
{
	return z;
}

void Missile::setShot(bool isShot)
{
	shot = isShot;
}

bool Missile::getShot()
{
	return shot;
}

void Missile::setHit(bool isHit)
{
	hit = isHit;
}

bool Missile::getHit()
{
	return hit;
}