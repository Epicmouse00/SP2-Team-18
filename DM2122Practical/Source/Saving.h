#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Saving
{
private:
	int		balance;
public:
			Saving();
			~Saving();
	void	setBalance(int amount);
	int		getBalance() const;
};