#pragma once
#include <string>
#include <fstream>
#include "Leaderboard.h"
#include "Highscore.h"

class Saving
{
private:
	int		balance;
	int		equip;
	bool	car[5];
	int		nameLeaderboard[5];
	float	timeLeaderboard[5];
public:
			Saving();
			~Saving();
	bool	getCar(int carIndex) const;
	int		getBalance() const;

	int			getNameLeaderboard(int index);
	float		getTimeLeaderboard(int index);
	void		setNameLeaderboard(int index, int car);
	void		setTimeLeaderboard(int index, float time);
	void		setBalance(int amount);
	int			getEquip() const;
	void		setEquip(int equip);
	void		setColour(int carIndex);
	Highscore	getHighscore(int index);
	void		setHighscore(Highscore highscore, int index);
	void		save();
};