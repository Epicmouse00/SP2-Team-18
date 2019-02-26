#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <string>
#include "Highscore.h"

class Leaderboard
{
private:
	Highscore timeScores[5];
public:
	Leaderboard();
	~Leaderboard();

	void addTime(Highscore highscore);
	std::string getTime(int index) const;
	std::string getCar(int index) const;
	Highscore getHighscore(int index) const;
};

#endif