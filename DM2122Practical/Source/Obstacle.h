#pragma once
class Obstacle
{
	enum O_Type
	{
		O_DEFAULT,
		O_TALL,
		O_LONG
	};

public:
			Obstacle();
			Obstacle(int obstacleType);
			~Obstacle();
	void	setX(float x);
	void	setY(float y);
	void	setZ(float z);
	float	getX();
	float	getY();
	float	getZ();
	static int	getNoObstacle();
private:
	int		obstacleType	= O_DEFAULT;
	float	x				= 0;
	float	y				= 0;
	float	z				= 0;
	static int noObstacle;
};

