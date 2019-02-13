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
};
#endif