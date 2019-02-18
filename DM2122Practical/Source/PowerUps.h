#pragma once
#include <cstdlib>
class PowerUps
{
private:
	float x;
	float y;
	float z;
	int type;
	bool active;
public:
	PowerUps();
	~PowerUps();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setActive(bool active);
	float getX();
	float getY();
	float getZ();
	bool getActive();
	int getType();
};