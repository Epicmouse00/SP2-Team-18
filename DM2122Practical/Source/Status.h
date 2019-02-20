#pragma once
class Status
{
private:
	bool activeStatus[4];
	float statusTimers[4];
public:
	Status();
	~Status();

	void setActive(bool active, int index);
	bool getActive(int index);
	void setTimer(float time, int index);
	void updateTimer(double dt, int index);
	float getTimer(int index);
};