#include "Saving.h"

Saving::Saving()
{
	//open savedata and set balance from .txt
	fstream saveData("Save/Balance.txt");

	if (saveData.is_open())
	{
		string line;

		while (getline(cin, line))
		{
			balance = stoi(line);
		}
		saveData.close();
	}
	else cout << "Unable to open file";
}

Saving::~Saving()
{
}

void Saving::setBalance(int amount) 
{
	//save balance in .txt
	fstream saveData;

	saveData.open("Save/Balance.txt", fstream::in | fstream::out | fstream::trunc);
	saveData << to_string(balance);
	saveData.close();
}

int Saving::getBalance()
{
	//get balance from .txt
	return balance;
}