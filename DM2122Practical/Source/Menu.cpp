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
	if (cursorIndex == -1) // Set WINLOSE screen
	{
		setIndex(5);
		return false;
	}
	if (pageIndex == 0 && cursorIndex == 3) // Quit
	{
		return true;
	}
	if (pageIndex == 1 && cursorIndex == 2) // Gamechoose Back
	{
		setIndex(0);
	}
	else if (pageIndex == 1 && cursorIndex != 2) // Gamechoose Gamemode
	{
		setGameMode(cursorIndex);
		setIndex(2);
	}
	else if (pageIndex == 3 && cursorIndex == 0) // Shop Back
	{
		setIndex(0);
	}
	else if (pageIndex == 4 && cursorIndex == 0) // Leaderboard Back
	{
		setIndex(0);
	}
	else if (pageIndex == 5 && cursorIndex == 0) // Winlose retry
	{
		setIndex(2);
	}
	else if (pageIndex == 5 && cursorIndex == 1) // Winlose Back
	{
		setIndex(0);
	}
	else if (pageIndex == 0 && cursorIndex == 0) // Main menu play
	{
		setIndex(1);
	}
	else if (pageIndex == 0 && cursorIndex == 1) // Main menu shop
	{
		setIndex(3);
	}
	else if (pageIndex == 0 && cursorIndex == 2) // Main menu leaderboard
	{
		setIndex(4);
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
	gameMode = index;
}

int Menu::getGameMode() const
{
	return gameMode;
}