#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Saving
{
private:
	int		balance;
	bool grey;
	bool cyan;
	bool orange;
	bool red;
	bool green;
public:
			Saving();
			~Saving();
	void	setBalance(int amount);
	int		getBalance() const;
	bool getGrey();
	bool getCyan();
	bool getOrange();
	bool getRed();
	bool getGreen();
};