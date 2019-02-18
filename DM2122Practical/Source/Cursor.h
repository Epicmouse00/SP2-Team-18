#ifndef CURSOR_H
#define CURSOR_H

class Cursor
{
	float x[4], y[4];
	int positionIndex;
	int numberOfOptions;
public:
	Cursor();
	Cursor(int numberOfOptions);
	~Cursor();
	void addNewPosition(float x, float y, int index);
	void updatePositionIndex(int direction);
	float getX() const;
	float getY() const;
	int getIndex() const;
};

#endif