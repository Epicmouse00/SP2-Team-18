#include "Menu.h"

Menu::Menu()
{
	buttonIndex = 0;
}

Menu::~Menu()
{

}

void Menu::changeIndex(int direction)
{
	if (direction > 0 && buttonIndex > 0)
	{
		buttonIndex -= direction;
	}
	else if (direction < 0 && buttonIndex < 2)
	{
		buttonIndex += direction;
	}
}

int Menu::outputCursorPosition()
{
	return buttonIndex;
}