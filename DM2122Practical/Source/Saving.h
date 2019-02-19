#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Saving
{
private:
	int		balance;
	int		equip;
	bool	car[5];
public:
			Saving();
			~Saving();
	bool	getCar(int carIndex) const;
	int		getBalance() const;
	void	setBalance(int amount);
	int		getEquip() const;
	void	setEquip(int equip);
	void	setColour(int carIndex);
	void	save();
};