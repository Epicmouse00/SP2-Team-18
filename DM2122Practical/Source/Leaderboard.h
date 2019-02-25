#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <iostream>
#include <string>

class Leaderboard
{
private:
	std::string versusScores[5];
	std::string timeScores[5];
public:
	Leaderboard();
	~Leaderboard();

	void setVersus(std::string record, int index);
	std::string getVersus(int index) const;
	void setTime(std::string record, int index);
	std::string getTime(int index) const;

};

#endif