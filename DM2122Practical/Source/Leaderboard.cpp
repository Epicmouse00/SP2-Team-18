#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	for (int i = 0; i < 5; i++)
	{
		versusScores[i] = "Player:                              0";
		timeScores[i] = "Player:                              0";
	}
}

Leaderboard::~Leaderboard()
{

}

void Leaderboard::setVersus(string record)
{
	float temp = 0.f;
	for (int i = 0; i < 5; i++)
	{
		if (record > versusScores[i])
		{
			if (i == 4)
			{
				versusScores[i] = record;
				break;
			}
			else
			{
				for (int t = 3; t > i; t--)
				{
					versusScores[t + 1] = versusScores[t];
				}
				versusScores[i] = record;
			}
		}
	}
}

void Leaderboard::setTime(string record)
{
	for (int i = 0; i < 5; i++)
	{
		if (record > timeScores[i])
		{
			if (i == 4)
			{
				timeScores[i] = record;
				break;
			}
			else
			{
				for (int t = 3; t > i; t--)
				{
					timeScores[t + 1] = timeScores[t];
				}
				timeScores[i] = record;
			}
		}
	}
}

string Leaderboard::getVersus(int index) const
{
	return versusScores[index];
}

string Leaderboard::getTime(int index) const
{
	return timeScores[index];
}