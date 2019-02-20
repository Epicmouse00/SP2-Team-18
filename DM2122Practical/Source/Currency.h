#pragma once
class Currency
{
private:
	int		balance;
public:
			Currency();
			~Currency();
	void	addBalance(int amount);
	void	deductBalance(int amount);
	int		getBalance() const;
	void	setBalance(int amount);
};