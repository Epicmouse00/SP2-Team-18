#include "Status.h"

Status::Status()
{
	for (int i = 0; i < 4; i++)
	{
		activeStatus[i] = false;
		statusTimers[i] = 0.f;
	}
}

Status::~Status()
{
}

void Status::setActive(bool active, int index)
{
	activeStatus[index] = active;
}

bool Status::getActive(int index)
{
	return activeStatus[index];
}

void Status::setTimer(float time, int index)
{
	statusTimers[index] = time;
}

void Status::updateTimer(double dt, int index)
{
	statusTimers[index] += dt;
}

float Status::getTimer(int index)
{
	return statusTimers[index];
}