#ifndef SAVING_H
#define SAVING_H
#include <iostream>
#include <fstream>
#include <string>
#include "Shop.h"
#include "Leaderboard.h"
using namespace std;

class Saving
{
public:
			Saving(Shop* shop, Leaderboard* leaderboard);
			~Saving();
	void	loadShopData(Shop* shop);
	void	loadLeaderboardData(Leaderboard* leaderboard);
	void	saveData(Shop* shop, Leaderboard* leaderboard);
};
#endif