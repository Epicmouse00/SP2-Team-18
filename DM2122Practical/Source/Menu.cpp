#include "Menu.h"

Menu::Menu()
{
	pageIndex = 0;
	gameMode = 0;
}

Menu::~Menu()
{

}

bool Menu::menuChange(int cursorIndex)
{
	if (pageIndex == 0 && cursorIndex == 3)
	{
		return true;
	}
	if (pageIndex == 1 && cursorIndex == 2)
	{
		setIndex(0);
	}
	else if (pageIndex == 1 && cursorIndex != 2)
	{
		setGameMode(cursorIndex);
		setIndex(2);
	}
	else if (pageIndex == 4 && cursorIndex == 2)
	{
		setIndex(0);
	}
	else if (cursorIndex > 0)
	{
		setIndex(cursorIndex + 2);
	}
	else
	{
		setIndex(cursorIndex + 1);
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