#ifndef MENU_H
#define MENU_H

class Menu
{
private:
	int	pageIndex;
	int gameMode;
	void setGameMode(int index);
	void setIndex(int index);
public:
			Menu();
			~Menu();
	bool menuChange(int cursorIndex);
	int getIndex();
	int getGameMode();
};
#endif