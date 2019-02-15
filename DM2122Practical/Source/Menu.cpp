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
	if (pageIndex == 0 && cursorIndex == 3)
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
	else if (cursorIndex > 1)
	{
		setIndex(cursorIndex + 1);
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

int Menu::getIndex() const
{
	return pageIndex;
}

void Menu::setGameMode(int index)
{
	pageIndex = index;
}

int Menu::getGameMode() const
{
	return gameMode;
}