#include "Saving.h"

Saving::Saving(Shop* shop, Leaderboard* leaderboard)
{
	//open savedata and set balance from .txt
	fstream saveData("Save/Save.txt");

	if (saveData.is_open())
	{
		loadShopData(shop);
		string line;

		getline(saveData, line);
		for (int i = 0; i < 5; ++i)
		{
			getline(saveData, line);
			if (line != "")
			{
				versusLeaderboard[i] = line;
			}
		}
		for (int i = 0; i < 5; ++i)
		{
			getline(saveData, line);
			if (line != "")
			{
				timeLeaderboard[i] = line;
			}
		}
		saveData.close();
	}
	else cout << "Unable to open file";
}

Saving::~Saving()
{
}

string Saving::getVersusLeaderboard(int index)
{
	return versusLeaderboard[index];
}

string Saving::getTimeLeaderboard(int index)
{
	return timeLeaderboard[index];
}

void Saving::setVersusLeaderboard(int index, string record)
{
	versusLeaderboard[index] = record;
}

void Saving::setTimeLeaderboard(int index, string record)
{
	timeLeaderboard[index] = record;
}

bool Saving::getCar(int carIndex) const
{
	return car[carIndex];
}

void Saving::setBalance(int amount)
{
	balance = amount;
}

int Saving::getBalance() const
{
	return balance;
}

int Saving::getEquip() const
{
	return equip;
}

void Saving::setEquip(int equip)
{
	this->equip = equip;
}

void Saving::setColour(int carIndex)
{
	car[carIndex] = true;
}

void Saving::loadShopData(Shop* shop)
{
	//open savedata and set values from .txt
	fstream saveData("Save/Save.txt");

	string balance;
	string equip;
	string temp;

	getline(saveData, balance);
	getline(saveData, temp, '>');

	getline(saveData, equip, '>');
	getline(saveData, temp, '>');

	shop->loadNumberData(stoi(equip), stoi(balance));

	for (int i = 0; i < 5; ++i)
	{
		getline(saveData, temp);
		if (temp == "1")
		{
			shop->loadCarData(true, i);
		}
		else
		{
			shop->loadCarData(false, i);
		}
		getline(saveData, temp, '>');
	}
	saveData.close();
}

void Saving::loadLeaderboardData(Leaderboard* leaderboard)
{
	fstream saveData("Save/Save.txt");
	string temp;
	string carName;
	string record;
	string timeTaken;
	string index;
	for (int i = 0; i < 7; i++)
	{
		getline(saveData, temp);
	}

	for (int i = 0; i < 5; i++)
	{
		getline(saveData, carName, ',');
		getline(saveData, record, ',');
		getline(saveData, timeTaken, ',');
		getline(saveData, index, '\n');
		leaderboard->setVersus(carName, record, stoi(timeTaken), stoi(index));
	}
	
	for (int i = 0; i < 5; i++)
	{
		getline(saveData, carName, ',');
		getline(saveData, record, ',');
		getline(saveData, timeTaken, ',');
		getline(saveData, index, '\n');
		leaderboard->setTime(carName, record, stoi(timeTaken), stoi(index));
	}
}

void Saving::saveShopData(Shop* shop)
{
	fstream saveData;
	saveData.open("Save/Save.txt", fstream::in | fstream::out | fstream::trunc);
	saveData << shop->getBalance() << ">Money" << '\n';
	saveData << shop->getEquip() << ">Equipped" << '\n';
	for (int i = 0; i < 5; ++i)
	{
		std::string colour = ">";
		switch (i)
		{
		case 0:
			colour += "Grey";
			break;
		case 1:
			colour += "Cyan";
			break;
		case 2:
			colour += "Orange";
			break;
		case 3:
			colour += "Red";
			break;
		case 4:
			colour += "Monster";
			break;
		}
		saveData << shop->isOwned(i) << colour << '\n';
	}
	saveData.close();
}