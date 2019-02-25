#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Shop.h"
#include "Leaderboard.h"
using namespace std;

class Saving
{
private:
	int		balance;
	int		equip;
	bool	car[5];
	string	versusLeaderboard[5];
	string	timeLeaderboard[5];
public:
			Saving(Shop* shop, Leaderboard* leaderboard);
			~Saving();
	bool	getCar(int carIndex) const;
	int		getBalance() const;

	/*
	string	getVersusLeaderboard(int index);
	string	getTimeLeaderboard(int index);
	void	setVersusLeaderboard(int index, string record);
	void	setTimeLeaderboard(int index, string record);
	void	setBalance(int amount);
	int		getEquip() const;
	void	setEquip(int equip);
	void	setColour(int carIndex);
	*/
	void	loadShopData(Shop* shop);
	void	loadLeaderboardData(Leaderboard* leaderboard);
	void	saveShopData(Shop* shop);
	void	saveLeaderboard();

};