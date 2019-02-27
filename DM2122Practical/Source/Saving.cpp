#include "Saving.h"

Saving::Saving(Shop* shop, Leaderboard* leaderboard)
{
	loadShopData(shop);
	loadLeaderboardData(leaderboard);
}

Saving::~Saving()
{

}

void Saving::loadShopData(Shop* shop)
{
	//open savedata and set values from .txt
	fstream saveData("Save/Save.txt");

	string balance;
	string equip;
	string temp;

	getline(saveData, balance, '>');
	getline(saveData, temp);

	getline(saveData, equip, '>');
	getline(saveData, temp);

	shop->loadNumberData(stoi(equip), stoi(balance));

	for (int i = 0; i < 5; ++i)
	{
		getline(saveData, temp, '>');
		if (temp == "1")
		{
			shop->loadCarData(true, i);
		}
		else
		{
			shop->loadCarData(false, i);
		}
		getline(saveData, temp);
	}
	saveData.close();
}

void Saving::loadLeaderboardData(Leaderboard* leaderboard)
{
	fstream saveData("Save/Save.txt");
	string temp;
	string carIndex;
	string timeTaken;
	for (int i = 0; i < 7; i++)
	{
		getline(saveData, temp);
	}

	for (int i = 0; i < 5; i++)
	{
		getline(saveData, carIndex, ',');
		getline(saveData, timeTaken, ',');
		getline(saveData, temp);
		leaderboard->setVersus(stoi(carIndex), stoi(timeTaken), i);
	}
	
	for (int i = 0; i < 5; i++)
	{
		getline(saveData, carIndex, ',');
		getline(saveData, timeTaken, ',');
		leaderboard->setTime(stoi(carIndex), stoi(timeTaken), i);
	}
}

void Saving::saveData(Shop* shop, Leaderboard* leaderboard)
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
	for (int i = 0; i < 5; i++)
	{
		saveData << leaderboard->getVersus(i) << ',' << '\n';
	}
	for (int i = 0; i < 5; i++)
	{
		saveData << leaderboard->getTime(i) << ',' << '\n';
	}
	saveData.close();
}