#include "Shop.h"

Shop::Shop()
{
	index = 0;

	Saving save;

	if (save.getGrey() == true)
	{
		grey = true;
	}
	else
	{
		grey = false;
	}

	if (save.getCyan() == true)
	{
		cyan = true;
	}
	else
	{
		cyan = false;
	}

	if (save.getOrange() == true)
	{
		orange = true;
	}
	else
	{
		orange = false;
	}

	if (save.getRed() == true)
	{
		red = true;
	}
	else
	{
		red = false;
	}

	if (save.getGreen() == true)
	{
		green = true;
	}
	else
	{
		green = false;
	}
}

Shop::~Shop()
{
}

int Shop::getCost()
{
	switch (index)
	{
	case 0:
		return 10;
		break;
	case 1:
		return 20;
		break;
	case 2:
		return 30;
		break;
	case 3:
		return 40;
		break;
	case 4:
		return 50;
		break;
	}
}

int Shop::getColour()
{
	return index;
}

void Shop::nextIndex()
{
	if (index < 4)
	{
		index++;
	}
}

void Shop::previousIndex()
{
	if (index > 0)
	{
		index--;
	}
}

void Shop::resetIndex()
{
	index = 0;
}

bool Shop::isOwned()
{
	switch (index)
	{
	case 0:
		if (grey == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 1:
		if (cyan == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 2:
		if (orange == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 3:
		if (red == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 4:
		if (green == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
}

void Shop::setOwned()
{
	switch (index)
	{
	case 0:
		grey = true;
		break;
	case 1:
		cyan = true;
		break;
	case 2:
		orange = true;
		break;
	case 3:
		red = true;
		break;
	case 4:
		green = true;
		break;
	}
}

bool Shop::getColour(int colourIndex)
{
	switch (colourIndex)
	{
	case 0:
		if (grey == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 1:
		if (cyan == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 2:
		if (orange == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 3:
		if (red == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 4:
		if (green == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
}