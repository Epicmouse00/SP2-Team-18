#include "Saving.h"

Saving::Saving()
{
	//open savedata and set balance from .txt
	fstream saveData("Save/Save.txt");

	if (saveData.is_open())
	{
		string line;
		getline(saveData, line, '>');
		balance = stoi(line);
		getline(saveData, line);
		getline(saveData, line, '>');
		equip = stoi(line);
		getline(saveData, line);
		for (int i = 0; i < 5; ++i)
		{
			getline(saveData, line, '>');
			if (line == "1")
				car[i] = true;
			else
				car[i] = false;
			getline(saveData, line);
		}
		for (int i = 0; i < 5; ++i)
		{
			getline(saveData, line);
			versusLeaderboard[i] = line;
		}
		for (int i = 0; i < 5; ++i)
		{
			getline(saveData, line);
			timeLeaderboard[i] = line;
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

void Saving::save()
{
	fstream saveData;
	int cars[5];
	for (int i = 0; i < 5; ++i)
	{
		if (car[i] == true)
			cars[i] = 1;
		else
			cars[i] = 0;
	}
	saveData.open("Save/Save.txt", fstream::in | fstream::out | fstream::trunc);
	saveData << balance << ">Money" << '\n';
	saveData << equip << ">Equipped" << '\n';
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
		saveData << cars[i] << colour << '\n';
	}
	saveData.close();
}