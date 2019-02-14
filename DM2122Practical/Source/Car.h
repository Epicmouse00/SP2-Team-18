#pragma once
class Car
{
private:
	float	Movement;
	int		Lane;
	float	Jump;
	bool	JumpPressed;
	bool	isPlayer;
	bool	resetTime;
public:
			Car();
			Car(bool isPlayer);
			~Car();
	bool	UpdatePlayerStrafe(double dt, float delayTime, bool left, bool right);
	void	UpdatePlayerJump(double dt, bool jump);
	int		getLane();
	float	getMovement();
	float	getJump();
};

