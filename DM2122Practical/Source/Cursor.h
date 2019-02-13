#ifndef CURSOR_H
#define CURSOR_H

class Cursor
{
	float initialPosition;
	float positionIndex;
public:
	Cursor();
	~Cursor();
	void updatePositionIndex(int direction);
	float outputPosition();
};

#endif