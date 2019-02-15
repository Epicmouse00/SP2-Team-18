#pragma once
#include "Car.h"
#include "Obstacle.h"

class AImovement
{
private:
	bool	jump;
	bool	left;
	bool	right;
public:
			AImovement();
			AImovement(Car car, Obstacle List[4][100]);
			~AImovement();
	bool	getJump() const;
	bool	getLeft() const;
	bool	getRight() const;
};

