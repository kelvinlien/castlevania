#include "Heart.h"

Heart::Heart(bool isBigHeart)
{
	if (isBigHeart)
	{
		bigHeart = true;
		width = 12;
		height = 10;
		this->AddAnimation(803);
	}
	else
	{
		bigHeart = false;
		width = 8;
		height = 8;
		this->AddAnimation(802);
	}
}

Heart::~Heart()
{
}

void Heart::setID(int ID)
{
	id = ID;
}

int Heart::getID()
{
	return id;
}
