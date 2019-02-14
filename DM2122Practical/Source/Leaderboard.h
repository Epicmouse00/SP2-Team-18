#ifndef LEADERBOARD_H
#define LEADERBOARD_H

class Leaderboard
{
private:
	float versusScores[5];
	float timeScores[5];

public:
	Leaderboard();
	~Leaderboard();

	void setVersus(int time);
	float getVersus(int index) const;
	void setTime(int time);
	float getTime(int index) const;

};

#endif