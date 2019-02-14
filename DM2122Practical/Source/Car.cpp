#include "Car.h"


Car::Car()
{
	Movement = 0.f;
	Lane = 0;
	Jump = 0.f;
	JumpPressed = false;
	isPlayer = true;
	resetTime = false;
}

Car::Car(bool isPlayer)
{
	Movement = -2.f;
	Lane = 0;
	Jump = 0.f;
	JumpPressed = false;
	resetTime = false;
	this->isPlayer = isPlayer;
	if (isPlayer)
		Lane = 1;
	else
		Lane = 2;
}


Car::~Car()
{
}

int Car::getLane()
{
	return Lane;
}

float Car::getMovement()
{
	return Movement;
}

float Car::getJump()
{
	return Jump;
}


bool Car::UpdatePlayerStrafe(double dt, float delayTime, bool left, bool right)
{
	resetTime = false;
	if (delayTime >= 1.0f)
	{
		if (left)
		{
			if (Lane < 3)
			{
				Lane++;
				resetTime = true;
			}
		}
		if (right)
		{
			if (Lane > 0)
			{
				Lane--;
				resetTime = true;
			}
		}
	}

	float lanePos;
	const float laneDist = 7.5f;
	const float laneOffset = -0.75f;
	switch (Lane)
	{
	case 0:
		lanePos = -laneDist;
		break;
	case 1:
		lanePos = 0.0f;
		break;
	case 2:
		lanePos = laneDist;
		break;
	case 3:
		lanePos = 2 * laneDist;
		break;
	default:
		lanePos = 0.f;
		break;
	}

	if (Movement <= lanePos - 1.5f)
		Movement += (float)(50 * dt);
	else if (Movement > lanePos + 1.5f)
		Movement -= (float)(50 * dt);
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