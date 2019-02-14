#include "Menu.h"

Menu::Menu()
{
	pageIndex = 0;
}

Menu::~Menu()
{

}

bool Menu::menuChange(int cursorIndex)
{
	cursorIndex += 1;
	if (pageIndex == 0 && cursorIndex == 4)
	{
		return true;
	}
	if (pageIndex == 0 && (cursorIndex == 2 || cursorIndex == 3))
	{
		return false;
	}
	if (pageIndex == 1 && cursorIndex == 3)
	{
		setIndex(0);
	}
	else if (pageIndex == 1 && cursorIndex != 3)
	{
		setGameMode(cursorIndex);
		setIndex(2);
	}
	else
	{
		setIndex(cursorIndex);
	}
	return false;
}

void Menu::setIndex(int index)
{
	pageIndex = index;
}

int Menu::getIndex()
{
	return pageIndex;
}

void Menu::setGameMode(int index)
{
	pageIndex = index;
}

int Menu::getGameMode()
{
	return gameMode;
}