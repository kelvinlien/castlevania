#include "FirePots.h"
#include "Brick.h"


FirePots::FirePots()
{
	IsBreak = false;
	state = FIREPOTS_STATE_BURN;
}

FirePots::~FirePots()
{
}

void FirePots::Render()
{
	int ani;
	if (disappear || picked)		//check and stop rendering if either is true
	{
		return;
	}
	if (state == FIREPOTS_STATE_ITEM)
	{
		ani = HEART_ANI_BIG;
		RenderBoundingBox();
	}
	else if (state == FIREPOTS_STATE_BREAK)
	{
		ani = EFFECT_ANI_BROKEN;
	}
	else
	{
		ani = FIREPOTS_ANI_BURN;
		RenderBoundingBox();
	}
	animations[ani]->Render(x, y);
}
void FirePots::SetState(int stat)
{
	CGameObject::SetState(stat);
	if (state == FIREPOTS_STATE_BREAK)
	{
		IsBreak = true;
	}
	else if (state == FIREPOTS_STATE_BURN)
	{
		IsBreak = false;
	}
	else if (state == FIREPOTS_STATE_REWARDED)
	{
		picked = true;
	}
}
void FirePots::GetBoundingBox(float &l, float &t, float &r, float &b)
{ 
	int width, height;
	width = FIREPOTS_BBOX_WIDTH;
	height = FIREPOTS_BBOX_HEIGHT;
	if (state == FIREPOTS_STATE_ITEM)
	{
		//x += width / 3;
		//y += height / 3;
		width = 12;
		height = 10;
	}
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void FirePots::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	dy = dt * vy;
	if (state != FIREPOTS_STATE_BURN)
	{
		if (timer <= 300)			//effect time
		{
			timer += dt;
		}
		else if (timer <= 3000)		//item exist time
		{
			vy = 0.01f;
			state = FIREPOTS_STATE_ITEM;
			timer += dt;
		}
		else
		{
			timer = 0;
			disappear = true;
			state = FIREPOTS_STATE_TIMEOUT;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (!picked || !disappear)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}

	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				vy = 0;
			}
		}
	}



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
