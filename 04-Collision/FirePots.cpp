#include "FirePots.h"


FirePots::FirePots()
{
	IsBreak = false;

}

FirePots::~FirePots()
{
}

void FirePots::Render()
{
	int ani;
	if (!IsBreak)
	{
		ani = FIREPOTS_ANI_BURN;
		animations[ani]->Render(x, y);
		RenderBoundingBox();
	}
	else
	{
		return;
	}
}
void FirePots::SetState(int stat)
{
	CGameObject::SetState(stat);
	if (state = FIREPOTS_STATE_BREAK)
	{
		IsBreak = true;
	}
	else if (state != FIREPOTS_STATE_BREAK)
		IsBreak = false;
}
void FirePots::GetBoundingBox(float &l, float &t, float &r, float &b)
{ 
	l = x;
	t = y;
	r = x + FIREPOTS_BBOX_WIDTH;
	b = y + FIREPOTS_BBOX_HEIGHT;
}

void FirePots::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	return;
}

bool FirePots::isBreak()
{
	return IsBreak;
}

void FirePots::setID(int ID)
{
	id = ID;
}

int FirePots::getID()
{
	return id;
}
