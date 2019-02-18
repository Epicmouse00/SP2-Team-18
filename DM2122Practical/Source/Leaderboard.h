#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "Saving.h"
#include <string>

class Leaderboard
{
private:
	string versusScores[5];
	string timeScores[5];
	Saving save;

public:
	Leaderboard();
	~Leaderboard();

	void setVersus(string record);
	string getVersus(int index) const;
	void setTime(string record);
	string getTime(int index) const;

};

#endif