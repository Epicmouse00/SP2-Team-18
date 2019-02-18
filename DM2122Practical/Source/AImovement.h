#pragma once
#include "Obstacle.h"
#include "PowerUps.h"

class AImovement
{
private:
	bool	jump;
	bool	left;
	bool	right;
public:
			AImovement();
			AImovement(int lane, float forward, Obstacle obstacle[4][100], PowerUps powerups[4][50]);
			~AImovement();
	bool	getJump() const;
	bool	getLeft() const;
	bool	getRight() const;
};

