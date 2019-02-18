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
	balance = amount;

	saveData.open("Save/Balance.txt", fstream::in | fstream::out | fstream::trunc);
	saveData << to_string(balance);
	saveData << '\n';
	saveData.close();
}

int Saving::getBalance() const
{
	//get balance from .txt
	return balance;
}

void Saving::setCars()
{
	fstream carData;
	int cars[5];

	if (grey == true)
	{
		cars[0] = 1;
	}
	else
	{
		cars[0] = 0;
	}
	if (cyan == true)
	{
		cars[1] = 1;
	}
	else
	{
		cars[1] = 0;
	}
	if (orange == true)
	{
		cars[2] = 1;
	}
	else
	{
		cars[2] = 0;
	}
	if (red == true)
	{
		cars[3] = 1;
	}
	else
	{
		cars[3] = 0;
	}
	if (green == true)
	{
		cars[4] = 1;
	}
	else
	{
		cars[4] = 0;
	}

	carData.open("Save/Cars.txt", fstream::in | fstream::out | fstream::trunc);
	carData << to_string(cars[0]);
	carData << '\n';
	carData << to_string(cars[1]);
	carData << '\n';
	carData << to_string(cars[2]);
	carData << '\n';
	carData << to_string(cars[3]);
	carData << '\n';
	carData << to_string(cars[4]);
	carData.close();
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

void Saving::setColour(bool isOwned, int carIndex)
{
	if (isOwned == true)
	{
		switch (carIndex)
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
	else
	{
		switch (carIndex)
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
}