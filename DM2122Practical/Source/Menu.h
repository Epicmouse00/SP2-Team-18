#ifndef MENU_H
#define MENU_H

class Menu
{
private:
	int buttonIndex;
public:
	Menu();
	~Menu();
	void changeIndex(int direction);
	int outputCursorPosition();
};

#endif
