#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <iostream>
#include <string>

class Leaderboard
{
private:
	int versusCarIndex[5];
	int versusTimeTaken[5];
	int timeCarIndex[5];
	int timeTimeTaken[5];
public:
	Leaderboard();
	~Leaderboard();

	void setVersus(int carIndex, int timeTaken, int index);
	std::string getVersus(int index) const;
	std::string getVersusCar(int index) const;
	std::string getVersusRecord(int index) const;
	void setTime(int carIndex, int timeTaken, int index);
	std::string getTime(int index) const;
	std::string getTimeCar(int index) const;
	std::string getTimeRecord(int index) const;
	void addNewScore(int carIndex, int timeTaken, bool isVersus);
};
#endif