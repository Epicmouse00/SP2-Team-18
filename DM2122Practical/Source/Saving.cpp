#include "Saving.h"

Saving::Saving()
{
	string line;
	int i = 0;

	ifstream myfile("Save/SaveData.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			balance = stoi(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

Saving::~Saving()
{
}

void Saving::setBalance(int amount)
{
	//set balance in .txt
}

int Saving::getBalance()
{
	//get balance from .txt
	return balance;
}