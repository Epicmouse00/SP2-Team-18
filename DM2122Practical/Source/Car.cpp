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
	Flight = false;
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
	if (Flight == false)
	{
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
}

void Car::UpdatePlayerForward(double dt, float boost)
{
	Forward += (float)((100 + boost) * dt);
}

void Car::UpdatePlayerFlight(double dt, float height, bool status)
{
	if (Jump <= 0)
	{
		Flight = true;
	}

	if (status == true)
	{
		if (Jump <= height)
		{
			Jump += (float)(40 * dt);
		}
	}
	else
	{
		Flight = false;
	}
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
	const float range = 20.f;
	const float height = 5.f;
	int row = 0;
	float forward = 3 * Forward;
	if (forward / 800 > 0) // Row in front of car
		row = ((int)forward / 800);
	if (powerups[Lane][row].getActive() && Jump < height &&  powerups[Lane][row].getZ() > forward - range && powerups[Lane][row].getZ() < forward + range)
		return true;
	return false;
}

bool Car::collisionObstacle(Obstacle obstacle[4][100]) const
{
	const float range = 20.f;
	const float height = 5.f;
	int row = 0;
	float forward = 3 * Forward;
	if ((forward - 600) / 400 > 0) // Row in front of car
		row = ((int)forward - 600) / 400;
	if (obstacle[Lane][row].getActive() && ((Jump < height && obstacle[Lane][row].getObstacleType() == 0) || obstacle[Lane][row].getObstacleType() == 1) && obstacle[Lane][row].getZ() > forward - range && obstacle[Lane][row].getZ() < forward + range)
		return true;
	return false;
}

void Car::setPlayerForward(float dist)
{
	Forward = dist;
}

void Car::setPlayerLane(int lane)
{
	Lane = lane;
}

void Car::setMaxSpeed(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

void Car::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

float Car::getMaxSpeed() const
{
	return maxSpeed;
}

float Car::getAcceleration() const
{
	return acceleration;
}
