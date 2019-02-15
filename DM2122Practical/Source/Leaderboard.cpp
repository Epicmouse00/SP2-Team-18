#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	for (int i = 0; i < 5; i++)
	{
		versusScores[i] = 0.f;
		timeScores[i] = 0.f;
	}
}

Leaderboard::~Leaderboard()
{

}

void Leaderboard::setVersus(float time)
{
	float temp = 0.f;
	for (int i = 0; i < 5; i++)
	{
		if (time > versusScores[i])
		{
			if (i == 4)
			{
				versusScores[i] = time;
				break;
			}
			else
			{
				for (int t = 3; t > i; t--)
				{
					versusScores[t + 1] = versusScores[t];
				}
				versusScores[i] = time;
			}
		}
	}
}

void Leaderboard::setTime(float time)
{
	for (int i = 0; i < 5; i++)
	{
		if (time > timeScores[i])
		{
			if (i == 4)
			{
				timeScores[i] = time;
				break;
			}
			else
			{
				for (int t = 3; t > i; t--)
				{
					timeScores[t + 1] = timeScores[t];
				}
				timeScores[i] = time;
			}
		}
	}
}

float Leaderboard::getVersus(int index) const
{
	return versusScores[index];
}

float Leaderboard::getTime(int index) const
{
	return timeScores[index];
}