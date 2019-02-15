#pragma once
#include <cstdlib>
class PowerUps
{
private:
	float x;
	float y;
	float z;
	int type;
public:
	PowerUps();
	~PowerUps();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float getX();
	float getY();
	float getZ();
	int getType();
};