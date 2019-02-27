#ifndef SHOP_H
#define SHOP_H

class Shop
{
private:
	int index;
	int equip;
	int balance;
	bool car[5];
public:
	Shop();
	~Shop();

	void loadCarData(bool ownedCar, int index);
	void loadNumberData(int equip, int balance);
	int getCost() const;
	int getIndex() const;
	void nextIndex();
	void previousIndex();
	void resetIndex();
	bool isOwned(int index) const;
	void setOwned(int index);
	void setEquip();
	bool isEquip() const;
	int	getEquip() const;
	int getBalance() const;
	void setBalance(int balance);
};
#endif