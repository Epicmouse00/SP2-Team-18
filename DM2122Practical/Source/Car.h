#ifndef CAR_H 
#define CAR_H
#include "PowerUps.h"
#include "obstacle.h"

class Car
{
private:
	float	Movement;
	int		Lane;
	float	Jump;
	float	Forward;
	bool	JumpPressed;
	bool	isPlayer;
	bool	resetTime;
	int		texture;
	float	maxSpeed;
	float	acceleration;
	const float	laneDist	= 7.5f;
	const float	laneOffset	= -0.75f;
public:
			Car();
			Car(bool isPlayer);
			~Car();
	bool	UpdatePlayerStrafe(double dt, float delayTime, bool left, bool right);
	void	UpdatePlayerJump(double dt, bool jump);
	void	UpdatePlayerForward(double dt, float boost);
	int		getLane() const;
	float	getMovement() const;
	float	getJump() const;
	float	getForward() const;
	void	setTexture(int texture);
	int		getTexture() const;
	bool	collisionPowerUp(PowerUps powerups[4][50]) const;
	bool	collisionObstacle(Obstacle obstacle[4][100]) const;
	void	setPlayerForward(float dist);
	void	setMaxSpeed(float maxSpeed);
	void	setAcceleration(float acceleration);
	float	getMaxSpeed() const;
	float	getAcceleration() const;
};

#endif