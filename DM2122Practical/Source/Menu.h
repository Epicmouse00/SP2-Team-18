#ifndef MENU_H
#define MENU_H

class Menu
{
private:
	int	pageIndex;
public:
			Menu();
			~Menu();
	void	changeIndex(int newScreenIndex);
	int menuChange(int cursorIndex);
	void setIndex(int index);
	int getIndex();
};
#endif