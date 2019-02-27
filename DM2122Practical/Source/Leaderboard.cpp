#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	for (int i = 0; i < 5; i++)
	{
		versusScores[i] = "Error";
		timeScores[i] = "Error";
	}
}

Leaderboard::~Leaderboard()
{

}

void Leaderboard::setVersus(std::string carName, std::string record, int timeTaken, int index)
{
	carName += ",";
	carName += record;
	carName += ",";
	carName += std::to_string(timeTaken);
	carName += ",";
	carName += std::to_string(index);
	versusScores[index] = carName;
}

void Leaderboard::setTime(std::string carName, std::string record, int timeTaken, int index)
{
	carName += ",";
	carName += record;
	carName += ",";
	carName += std::to_string(timeTaken);
	carName += ",";
	carName += std::to_string(index);
	timeScores[index] = carName;
}

std::string Leaderboard::getVersusName(int index) const
{
	return versusScores[index];
}

std::string Leaderboard::getVersusName(int index) const
{

}

std::string Leaderboard::getTimeName(int index) const
{
	return timeScores[index];
}

std::string Leaderboard::getTimeRecord(int index) const
{

}

void Leaderboard::addNewScore(std::string carName, std::string record, int timeTaken, int index, bool isVersus)
{
	std::string recordTimeTaken;
	if (isVersus)
	{
		for (int i = 0; i < 5; i++)
		{
			int dataPosition;
			for (int t = 0; t < versusScores[i].size(); t++)
			{
				if (versusScores[i][t] == ',')
				{
					dataPosition++;
					if (dataPosition == 2)
					{
						recordTimeTaken += versusScores[i][t];
					}
				}
			}
			if (std::stoi(recordTimeTaken) < timeTaken)
			{

			}
		}
	}
	else
	{

	}

}