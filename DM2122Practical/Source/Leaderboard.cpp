#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	for (int i = 0; i < 5; i++)
	{
		versusScores[i] = "test";
		timeScores[i] = "test";
	}
}

Leaderboard::~Leaderboard()
{

}

void Leaderboard::setVersus(std::string record, int index)
{
	versusScores[index] = record;
}

void Leaderboard::setTime(std::string record, int index)
{
	timeScores[index] = record;
}

std::string Leaderboard::getVersus(int index) const
{
	return versusScores[index];
}

std::string Leaderboard::getTime(int index) const
{
	return timeScores[index];
}