#include "Saving.h"

Saving::Saving()
{
	//open savedata and set balance from .txt
	std::fstream saveData("Save/Save.txt");

	if (saveData.is_open())
	{
		std::string line;
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
			nameLeaderboard[i] = stoi(line); // Car
			getline(saveData, line);
			timeLeaderboard[i] = (float)stoi(line); // Time
		}
		saveData.close();
	}
}

Saving::~Saving()
{
}

int Saving::getNameLeaderboard(int index)
{
	return nameLeaderboard[index];
}

float Saving::getTimeLeaderboard(int index)
{
	return timeLeaderboard[index];
}

void Saving::setNameLeaderboard(int index, int car)
{
	nameLeaderboard[index] = car;
}

void Saving::setTimeLeaderboard(int index, float time)
{
	timeLeaderboard[index] = time;
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

Highscore Saving::getHighscore(int index)
{
	Highscore temp;
	temp.setCar(nameLeaderboard[index]);
	temp.setTimeTaken(timeLeaderboard[index]);
	return temp;
}

void Saving::setHighscore(Highscore highscore, int index)
{
	nameLeaderboard[index] = highscore.getCar();
	timeLeaderboard[index] = highscore.getTimeTaken();
}

void Saving::save()
{
	std::fstream saveData;
	int cars[5];
	for (int i = 0; i < 5; ++i)
	{
		if (car[i] == true)
			cars[i] = 1;
		else
			cars[i] = 0;
	}
	saveData.open("Save/Save.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
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
	for (int i = 0; i < 5; ++i)
	{
		saveData << nameLeaderboard[i] << '\n' << timeLeaderboard[i] << '\n';
	}
	saveData.close();
}