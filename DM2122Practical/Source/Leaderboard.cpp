#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	Highscore temp;
	temp.setCar(0);
	temp.setTimeTaken(-1.f);
	for (int i = 0; i < 5; i++)
	{
		timeScores[i] = temp;
	}
}

Leaderboard::~Leaderboard()
{

}

void Leaderboard::addTime(Highscore highscore)
{
	for (int i = 0; i < 5; ++i) // Starts checking from first element
	{
		if (timeScores[i].getTimeTaken() == -1.f) // If default
		{
			timeScores[i] = highscore; // Set the new score
			break;
		}
		else if (highscore.getTimeTaken() < timeScores[i].getTimeTaken()) // if new score is faster
		{
			for (int j = 5 - i; j > 0; --j) // Push back the rest
			{
					timeScores[j] = timeScores[j - 1];
			}
			timeScores[i] = highscore; // Set the new score
			break;
		}
	}
}

std::string Leaderboard::getTime(int index) const
{
	return timeScores[index].getTime();
}

std::string Leaderboard::getCar(int index) const
{
	std::string temp;
	switch (timeScores[index].getCar())
	{
	case 0:
		temp = "Grey";
		break;
	case 1:
		temp = "Cyan";
		break;
	case 2:
		temp = "Orange";
		break;
	case 3:
		temp = "Red";
		break;
	case 4:
		temp = "Monster";
		break;
	default:
		temp = "Kitsune";
		break;
	}
	return temp;
}

Highscore Leaderboard::getHighscore(int index) const
{
	return timeScores[index];
}

