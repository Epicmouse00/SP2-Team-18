#include "AImovement.h"



AImovement::AImovement()
{
}

AImovement::AImovement(Car car, Obstacle List[4][100])
{
	jump = false;
	left = false;
	right = false;

	for (size_t row = 0; row < 100; row++)
	{
		if(List[car.getLane()][row].getZ() < car.getForward())
		{
			//idk
		}
	}
}

AImovement::~AImovement()
{
}

bool AImovement::getJump() const
{
	return jump;
}

bool AImovement::getLeft() const
{
	return left;
}

bool AImovement::getRight() const
{
	return right;
}
