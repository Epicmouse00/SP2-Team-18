#ifndef CURSOR_H
#define CURSOR_H

class Cursor
{
	float initialPosition;
	int positionIndex;
public:
	Cursor();
	~Cursor();
	void updatePositionIndex(int direction);
	float outputPosition();
	int getIndex();
};

#endif