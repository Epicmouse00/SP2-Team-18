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