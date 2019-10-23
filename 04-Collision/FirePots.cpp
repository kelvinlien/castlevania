#include "FirePots.h"


FirePots::FirePots()
{
	IsBreak = false;
	ended = false;
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
		float efx = this->x + FIREPOTS_BBOX_WIDTH / 2;
		float efy = this->y + 7;
		ef->AddAnimation(901);
		ef->SetPosition(efx, efy);
		ef->Render();
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
	if (IsBreak)
	{
		if (!ended)
		{
			ef->Update(dt, NULL);
		}
	}
	return;
}
