#include "AImovement.h"
/*
	Check if have obstacle
		if have, check if obstacle is short
			if short, jump
			if tall,
				check next lane if doesnt have tall obstacle
				if dont have, move there
				if not,
					move to next lane to check if there are free lanes

		if not, check if have items
			if have, do nothing
			if no items, check next lane
				if have, move there


			if not, move to center
*/


AImovement::AImovement()
{
}

AImovement::AImovement(int lane, float forward, Obstacle obstacle[4][100], PowerUps powerups[4][50])
{
	jump = false;
	left = false;
	right = false;
	float range = 0.f;
	bool haveObstacle = false;
	int row = 0;
	forward *= 3;
	if ((forward - 600) / 400 > 0) // Row in front of car
		row = ((int)forward - 600) / 400;
	if(obstacle[lane][row].getActive())
	{
		range = 300.f;
		if (obstacle[lane][row].getZ() < range + forward)
		{
			haveObstacle = true;
			if (obstacle[lane][row].getObstacleType() == 1) // Tall
			{
				if (lane == 0) //if on edge
					right = true;
				else if (lane == 3)
					left = true;
				else if (!obstacle[lane - 1][row].getActive() || obstacle[lane - 1][row].getObstacleType() != 1) //if next lane is free
					left = true;
				else if (!obstacle[lane + 1][row].getActive() || obstacle[lane + 1][row].getObstacleType() != 1)
					right = true;
				else if (lane == 1) //if both lanes aren't free
					right = true;
				else if (lane == 2)
					left = true;
			}
		}
		range = 200.f;
		if (obstacle[lane][row].getZ() < range + forward)
		{
			haveObstacle = true;
			if (obstacle[lane][row].getObstacleType() == 0) // Short
				jump = true;
		}
	}
	range = 100.f;
	if (forward / 800 > 0) // Row in front of car
		row = ((int)forward / 800);
	else
		row = 0;
	if (!haveObstacle && !powerups[lane][row].getActive())// if no powerup in front and no near obstacles
	{
		if (lane > 0 && powerups[lane - 1][row].getActive() && powerups[lane - 1][row].getZ() < range + forward) // check powerup side
			left = true;
		else if (lane < 3 && powerups[lane + 1][row].getActive() && powerups[lane + 1][row].getZ() < range + forward)
			right = true;
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
