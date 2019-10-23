#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	dx = vx * dt;
	dy = vy * dt;
}
