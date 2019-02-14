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
	int		texture;
	const float	laneDist	= 7.5f;
	const float	laneOffset	= -0.75f;
public:
			Car();
			Car(bool isPlayer);
			~Car();
	bool	UpdatePlayerStrafe(double dt, float delayTime, bool left, bool right);
	void	UpdatePlayerJump(double dt, bool jump);
	int		getLane();
	float	getMovement();
	float	getJump();
	void	setTexture(int texture);
	int		getTexture();
};

