#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	for (int i = 0; i < 5; i++)
	{
		versusCarIndex[i] = 0;
		versusTimeTaken[i] = 0;
		timeCarIndex[i] = 0;
		timeTimeTaken[i] = 0;
	}
}

Leaderboard::~Leaderboard()
{

}

void Leaderboard::setVersus(int carIndex, int timeTaken, int index)
{
	versusCarIndex[index] = carIndex;
	versusTimeTaken[index] = timeTaken;
}

void Leaderboard::setTime(int carIndex, int timeTaken, int index)
{
	timeCarIndex[index] = carIndex;
	timeTimeTaken[index] = timeTaken;
}

std::string Leaderboard::getVersus(int index) const
{
	std::string record;
	record += std::to_string(versusCarIndex[index]);
	record += ',';
	record += std::to_string(versusTimeTaken[index]);
	return record;
}

std::string Leaderboard::getVersusCar(int index) const
{
	std::string carName;
	switch (versusCarIndex[index])
	{
	case 0:
		carName = "Grey";
		break;
	case 1:
		carName = "Cyan";
		break;
	case 2:
		carName = "Orange";
		break;
	case 3:
		carName = "Red";
		break;
	case 4:
		carName = "Monster";
		break;
	default:
		carName = "Raceholder";
		break;
	}
	return carName;
}

std::string Leaderboard::getVersusRecord(int index) const
{
	std::string stringRecord;
	stringRecord += std::to_string(((int)versusTimeTaken[index] / 100) / 60);
	stringRecord += ":";
	stringRecord += std::to_string(((int)versusTimeTaken[index] / 100) % 60);
	stringRecord += ":";
	stringRecord += std::to_string((int)versusTimeTaken[index] % 100);
	return stringRecord;
}

std::string Leaderboard::getTime(int index) const
{
	std::string record;
	record += std::to_string(timeCarIndex[index]);
	record += ',';
	record += std::to_string(timeTimeTaken[index]);
	return record;
}
std::string Leaderboard::getTimeCar(int index) const
{
	std::string carName;
	switch (timeCarIndex[index])
	{
	case 0:
		carName = "Grey";
		break;
	case 1:
		carName = "Cyan";
		break;
	case 2:
		carName = "Orange";
		break;
	case 3:
		carName = "Red";
		break;
	case 4:
		carName = "Monster";
		break;
	default:
		carName = "Raceholder";
		break;
	}
	return carName;
}

std::string Leaderboard::getTimeRecord(int index) const
{
	std::string stringRecord;
	stringRecord += std::to_string(((int)timeTimeTaken[index] / 100) / 60);
	stringRecord += ":";
	stringRecord += std::to_string(((int)timeTimeTaken[index] / 100) % 60);
	stringRecord += ":";
	stringRecord += std::to_string((int)timeTimeTaken[index] % 100);
	return stringRecord;
}

void Leaderboard::addNewScore(int carIndex, int timeTaken, bool isVersus)
{
	if (isVersus)
	{
		for (int i = 0; i < 5; i++)
		{
			if (timeTaken < versusTimeTaken[i])
			{
				if (i != 4)
				{
					for (int t = 3; t > (i - 1); t--)
					{
						versusCarIndex[t + 1] = versusCarIndex[t];
						versusTimeTaken[t + 1] = versusTimeTaken[t];
					}
					versusCarIndex[i] = carIndex;
					versusTimeTaken[i] = timeTaken;
					break;
				}
				else
				{
					versusCarIndex[i] = carIndex;
					versusTimeTaken[i] = timeTaken;
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (timeTaken < timeTimeTaken[i])
			{
				if (i != 4)
				{
					for (int t = 3; t > (i - 1); t--)
					{
						timeCarIndex[t + 1] = timeCarIndex[t];
						timeTimeTaken[t + 1] = timeTimeTaken[t];
					}
					timeCarIndex[i] = carIndex;
					timeTimeTaken[i] = timeTaken;
					break;
				}
				else
				{
					timeCarIndex[i] = carIndex;
					timeTimeTaken[i] = timeTaken;
					break;
				}
			}
		}
	}
}