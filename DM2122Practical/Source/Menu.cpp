#include "Menu.h"

Menu::Menu()
{
	pageIndex = 0;
}

Menu::~Menu()
{

}

void Menu::changeIndex(int newPageIndex)
{
	pageIndex = newPageIndex;
}

int Menu::menuChange(int cursorIndex)
{
	if (pageIndex == 1)
	{

		/*switch (gameChooseCursor.getIndex())
		{
		case 0:
			//vs
			gameState = E_GAME;
			gameMode = MODE_VS;
			break;
		case 1:
			//time
			gameState = E_GAME;
			gameMode = MODE_TIME;
			break;
		case 2:
			//back
			gameState = E_MAINMENU;
			break;
		default:
			break;
		}*/
		//return
	}
	return cursorIndex;
}

void Menu::setIndex(int index)
{
	pageIndex = index;
}

int Menu::getIndex()
{
	return pageIndex;
}