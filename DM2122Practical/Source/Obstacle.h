#ifndef OBSTACLE_H
#define OBSTACLE_H
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
	void	setActive(bool active);
	float	getX() const;
	float	getY() const;
	float	getZ() const;
	bool	getActive() const;
	int		getObstacleType();
private:
	int		obstacleType	= O_DEFAULT;
	float	x				= 0;
	float	y				= 0;
	float	z				= 0;
	bool	active			= false;
};
#endif