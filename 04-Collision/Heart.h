#pragma once
#include "Item.h"

class Heart :public Item
{
public:
	Heart(bool isBigHeart);
	~Heart();
	void setID(int ID);
	int getID();
private:
	bool bigHeart;
	int id;
};
