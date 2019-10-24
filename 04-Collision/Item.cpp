#include "Item.h"
#include "Simon.h"

Item::Item()
{
	picked = false;
	onGround = false;
	disappear = false;
	pickUpTimer = 0;
	actionTimer = 0;
}

Item::~Item()
{
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (disappear || picked)
	{
		if (!picked)
		{
			if (onGround)
			{
				if (pickUpTimer < 2500)
				{
					pickUpTimer += dt;
				}
				else
				{
					pickUpTimer = 0;
					disappear = true;
				}
			}
			else
			{
				if (y < 115)
				{
					vy += 0.7 * dt;
					y += dy;
				}
				else
				{
					y = 115;
					onGround = true;
				}
			}
		}

	}
	for (UINT i = 0; i < coObjects->size(); i++)
	{

		if (dynamic_cast<Simon*>(coObjects->at(i)))//is simon
		{
			Simon* simon = dynamic_cast<Simon*>(coObjects->at(i));
			float l, t, r, b, l1, t1, r1, b1;
			GetBoundingBox(l, t, r, b);
			simon->GetBoundingBox(l1, t1, r1, b1);
			if (t < b1 && b>t1 && r > l1 && l < r1)
			{
				if (!disappear && !picked)
					picked = true;
			}
		}
	}
}

void Item::Render()
{
	if (!picked && !disappear)
	{
		animations[0]->Render(x, y);
		RenderBoundingBox();
	}
	else
		return;
}

void Item::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = top + height;
}

bool Item::getPicked()
{
	return picked;
}

void Item::setPicked(bool _picked)
{
	if (!disappear)
		picked = _picked;
}
