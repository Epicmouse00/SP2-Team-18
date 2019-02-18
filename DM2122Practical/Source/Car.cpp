#include "Car.h"


Car::Car()
{
	Movement = 0.f;
	Lane = 0;
	Jump = 0.f;
	Forward = 0.f;
	JumpPressed = false;
	isPlayer = true;
	resetTime = false;
	texture = 0;
}

Car::Car(bool isPlayer)
{
	Jump = 0.f;
	Forward = 0.f;
	JumpPressed = false;
	resetTime = false;
	this->isPlayer = isPlayer;
	texture = 0;
	if (isPlayer)
	{
		Lane = 1;
		Movement = 1 * laneDist;
	}
	else
	{
		Lane = 2;
		Movement = 0 * laneDist;
	}
}


Car::~Car()
{
}

int Car::getLane() const
{
	return Lane;
}

float Car::getMovement() const
{
	return Movement;
}

float Car::getJump() const
{
	return Jump;
}

float Car::getForward() const
{
	return Forward;
}


bool Car::UpdatePlayerStrafe(double dt, float delayTime, bool left, bool right)
{
	resetTime = false;
	if (delayTime >= 0.7f)
	{
		if (right)
		{
			if (Lane < 3)
			{
				Lane++;
				resetTime = true;
			}
		}
		if (left)
		{
			if (Lane > 0)
			{
				Lane--;
				resetTime = true;
			}
		}
	}

	float lanePos;
	switch (Lane)
	{
	case 0:
		lanePos = 2 * laneDist;
		break;
	case 1:
		lanePos = 1 * laneDist;
		break;
	case 2:
		lanePos = 0 * laneDist;
		break;
	case 3:
		lanePos = -1 * laneDist;
		break;
	default:
		lanePos = 0.f;
		break;
	}

	if (Movement <= lanePos - 1.5f)
		Movement += (float)(70 * dt);
	else if (Movement > lanePos + 1.5f)
		Movement -= (float)(70 * dt);
	else
		Movement = lanePos + laneOffset;

	return resetTime;

}

void Car::UpdatePlayerJump(double dt, bool jump)
{
	const float jumpHeight = 10.0f;
	//Player Jump
	if (jump && Jump <= 0)
	{
		JumpPressed = true;
	}

	if (JumpPressed == true)
	{
		if (Jump < jumpHeight)
		{
			Jump += (float)(40 * dt);
		}
		else if (Jump < jumpHeight + 2.f)
		{
			Jump += (float)(20 * dt);
		}
		else
		{
			JumpPressed = false;
		}
	}
	else
	{
		if (Jump > 0)
		{
			if ((Jump -= (float)(40 * dt)) >= 0)
			{
				Jump -= (float)(40 * dt);
			}
			else
			{
				Jump = 0;
			}
		}
	}

}

void Car::UpdatePlayerForward(double dt, float boost)
{
	Forward += (float)((150 + boost) * dt);
}

void Car::setTexture(int texture)
{
	this->texture = texture;
}

int Car::getTexture() const
{
	return texture;
}

bool Car::collisionPowerUp(PowerUps powerups[4][50]) const
{
	const float range = 10.f; // I put 10 first idk what number to put
	const float height = 5.f; // I put 5 first idk what number to put
	int row = 0;
	float forward = 3 * Forward;
	if (forward / 800 > 0) // Row in front of car
		row = ((int)forward / 800);
	if (Jump < height && powerups[Lane][row].getZ() > forward - range && powerups[Lane][row].getZ() < forward + range)
		return true;
	return false;
}

bool Car::collisionObstacle(Obstacle obstacle[4][100]) const
{
	const float range = 10.f;  // I put 10 first idk what number to put
	const float height = 5.f; // I put 5 first idk what number to put
	int row = 0;
	float forward = 3 * Forward;
	if ((forward - 600) / 400 > 0) // Row in front of car
		row = ((int)forward - 600) / 400;
	if (((Jump < height && obstacle[Lane][row].getObstacleType() == 0) || obstacle[Lane][row].getObstacleType() == 1) && obstacle[Lane][row].getZ() > forward - range && obstacle[Lane][row].getZ() < forward + range)
		return true;
	return false;
}
