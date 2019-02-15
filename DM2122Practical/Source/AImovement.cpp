#include "AImovement.h"
/*
	Check if obstacle is short
		if yes, jump
		if not,
			check next lane if doesnt have tall obstacle
			if dont have, move there
			if not,
				move to next lane to check if there are free lanes
*/


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
			}
			if (obstacle[lane][row].getZ() - forward < 350.f)
			{
				if (obstacle[lane][row].getObstacleType() == 1) // Tall
				{
					if (lane == 0) //if on edge
						right = true;
					else if (lane == 3)
						left = true;
					else
					{
						if (obstacle[lane - 1][row].getObstacleType() == 0) //if next lane is free
							left = true;
						else if (obstacle[lane + 1][row].getObstacleType() == 0)
							right = true;
						else
						{
							if (lane == 1) //if both lanes aren't free
								right = true;
							else if (lane == 2)
								left = true;
						}
					}
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
