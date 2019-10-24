#pragma once
#include "Item.h"

class Heart :public Item
{
public:
	Heart(bool isBigHeart);
	~Heart();
private:
	bool bigHeart;
};
