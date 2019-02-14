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
	if (delayTime >= 1.0f)
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