#ifndef MISSILE_H
#define MISSILE_H
class Missile
{
private:
	float x;
	float y;
	float z;
	bool shot;
	bool hit;
public:
	Missile();
	~Missile();

	void setXYZ(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setShot(bool isShot);
	bool getShot();
	void setHit(bool isHit);
	bool getHit();
};
#endif