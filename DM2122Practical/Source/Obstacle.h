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
private:
	int		obstacleType	= O_DEFAULT;
	int		x				= 0;
	int		y				= 0;
	int		z				= 0;
};

