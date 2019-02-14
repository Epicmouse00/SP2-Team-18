#ifndef CURSOR_H
#define CURSOR_H

class Cursor
{
	float initialPosition;
	float spacing;
	int positionIndex;
	int numberOfOptions;
public:
	Cursor();
	Cursor(float initialPosition, float spacing, int numberOfOptions);
	~Cursor();
	void updatePositionIndex(int direction);
	float outputPosition() const;
	int getIndex() const;
};

#endif