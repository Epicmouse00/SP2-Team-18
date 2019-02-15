#include "AImovement.h"



AImovement::AImovement()
{
}

AImovement::AImovement(int lane, float forward, Obstacle obstacle[4][100], PowerUps powerups[4][50])
{
	jump = false;
	left = false;
	right = false;

	forward *= 3;
	for (size_t row = 0; row < 100; row++)
	{
		if(obstacle[lane][row].getZ() > forward)
		{
			if(obstacle[lane][row].getZ() - forward < 150.f)
			{
				if(obstacle[lane][row].getObstacleType() == 0) // Short
					jump = true;
				else
				{
					//change lanes
				}
			}
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
