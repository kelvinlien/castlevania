#include "Whip.h"

Whip::Whip()
{
	whipLevel = 1;
	isHidden = true;
}

Whip::~Whip()
{
}

void Whip::setWhipLevel(int level)
{
	whipLevel = level;
}

int Whip::getWhipLevel()
{
	return whipLevel;
}

void Whip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (whipLevel = 1)
	{
		right = left + level1WhipWidth;
		bottom = top + level1WhipHeight;
	}
}
