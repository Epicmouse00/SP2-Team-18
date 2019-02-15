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

	bool haveObstacle = false;
	int row = 0;
	if ((3 * (forward - 600)) / 400 > 0) // Row in front of car
		row = (3 * (forward - 600)) / 400;
	forward *= 3;
	
	if(obstacle[lane][row].getActive())
	{
		if (obstacle[lane][row].getZ() < 400.f + forward)
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
		if (obstacle[lane][row].getZ() < 200.f + forward)
		{
			haveObstacle = true;
			if (obstacle[lane][row].getObstacleType() == 0) // Short
				jump = true;
		}
	}
	/*
	if ((3 * (forward)) / 800 > 0) // Row in front of car
		row = (3 * (forward)) / 800;
	else
		row = 0;

	if (!haveObstacle && !powerups[lane][row].getActive())// if no powerup in front and no near obstacles
	{
		if (powerups[lane - 1][row].getActive()) // check powerup side
			left = true;
		else if (powerups[lane + 1][row].getActive())
			right = true;
		else // if no surrounding powerups
		{
			if (lane == 0)
				right = true;
			else if (lane == 3)
				left = true;
		}
	
	*/
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
