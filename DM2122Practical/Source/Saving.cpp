#include "Saving.h"

Saving::Saving()
{
	//open savedata and set balance from .txt
	fstream saveData("Save/Balance.txt");

	if (saveData.is_open())
	{
		string line;

		while (getline(saveData, line))
		{
			balance = stoi(line);
		}
		saveData.close();
	}
	else cout << "Unable to open file";

	fstream carData("Save/Cars.txt");

	if (carData.is_open())
	{
		string line;
		int i = 0;
		
		while (getline(carData, line))
		{
			if (line[0] == '0')
			{
				switch (i)
				{
				case 0:
					grey = false;
					break;
				case 1:
					cyan = false;
					break;
				case 2:
					orange = false;
					break;
				case 3:
					red = false;
					break;
				case 4:
					green = false;
					break;
				}
			}
			else if (line[0] == '1')
			{
				switch (i)
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
			i++;
		}
		carData.close();
	}
	else cout << "Unable to open file";
}

Saving::~Saving()
{
}

void Saving::setBalance(int amount) 
{
	//save balance in .txt
	fstream saveData;

	saveData.open("Save/Balance.txt", fstream::in | fstream::out | fstream::trunc);
	saveData << to_string(balance);
	saveData.close();
}

int Saving::getBalance() const
{
	//get balance from .txt
	return balance;
}

bool Saving::getGrey()
{
	if (grey == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Saving::getCyan()
{
	if (cyan == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Saving::getOrange()
{
	if (orange == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Saving::getRed()
{
	if (red == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Saving::getGreen()
{
	if (green == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}