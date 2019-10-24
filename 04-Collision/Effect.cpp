#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (ended)
	{
		return;
	}
	if (timer < 1500)
	{
		timer += dt;
	}
	else
	{
		timer = 0;
		ended = true;
	}
}

void Effect::Render()
{
	if (!ended)
	{
		this->AddAnimation(1001);
		animations[0]->Render(x, y);
		RenderBoundingBox();
	}


}

void Effect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 3;
	bottom = y + 3;
}
