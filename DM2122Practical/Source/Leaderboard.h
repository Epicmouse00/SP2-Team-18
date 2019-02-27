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

	void setVersus(std::string carName, std::string record, int timeTaken, int index);
	std::string getVersusName(int index) const;
	std::string getVersusRecord(int index) const;
	void setTime(std::string carName,std::string record, int timeTaken, int index);
	std::string getTimeName(int index) const;
	std::string getTimeRecord(int index) const;
	void addNewScore(std::string carName, std::string record, int timeTaken, int index, bool isVersus);

};

#endif