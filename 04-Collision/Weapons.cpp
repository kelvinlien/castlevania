#include "Weapons.h"
#include"Simon.h"
#include "FirePots.h"
#include<iostream>

void Weapon::Update(DWORD time,vector<LPGAMEOBJECT>*coObjects)
{
	int ani_left, ani_right;
	switch (level)
	{
	case 1:
		ani_left = WHIP_ANI_LV1_LEFT;
		ani_right = WHIP_ANI_LV1_RIGHT;
		break;
	case 2:
		ani_left = WHIP_ANI_LV2_LEFT;
		ani_right = WHIP_ANI_LV2_RIGHT;
		break;
	default:
		ani_left = WHIP_ANI_LV3_LEFT;
		ani_right = WHIP_ANI_LV3_RIGHT;
	}
	if (Simon_clone->nx > 0)
	{
		if (animations[ani_right]->GetCurrentFrame() == 0)
		{
			this->x = Simon_clone->x - 7.2f;
			this->y = Simon_clone->y+5.0f;
		}
		else if (animations[ani_right]->GetCurrentFrame() == 1)
		{
			this->x = Simon_clone->x-11.0f;
			this->y = Simon_clone->y;
		}
		else if (animations[ani_right]->GetCurrentFrame() == 2)
	    {	
			this->x = Simon_clone->x + 18.0f;
			this->y = Simon_clone->y+5.5f;
		}
		else
		{
			this->x = Simon_clone->x - 7.2f;
			this->y = Simon_clone->y + 5.0f;
		}
	}
	else if (Simon_clone->nx < 0)
	{
		if (animations[ani_left]->GetCurrentFrame() == 0)
		{
			this->x = Simon_clone->x + 19.5f;
			this->y = Simon_clone->y + 5.0f;
		}
		else if (animations[ani_left]->GetCurrentFrame() == 1)
		{
			this->x = Simon_clone->x + 14.5f;
			this->y = Simon_clone->y;
		}
		else if (animations[ani_left]->GetCurrentFrame() == 2)
		{
			if (ani_left != WHIP_ANI_LV3_LEFT)
				this->x = Simon_clone->x - 20.5f;
			else
				this->x = Simon_clone->x - 20.5f - 20.5f;
			this->y = Simon_clone->y + 5.5f;
		}
		else
		{
			this->x = Simon_clone->x + 19.5f;
			this->y = Simon_clone->y + 5.0f;
		}
	}
	for (UINT i = 0; i < coObjects->size(); i++)
	{

		if (dynamic_cast<FirePots *>(coObjects->at(i)))//is firepots
		{
			FirePots * firepots = dynamic_cast<FirePots *>(coObjects->at(i));
			float l, t, r, b, l1, t1, r1, b1;
			GetBoundingBox(l, t, r, b);
			firepots->GetBoundingBox(l1, t1, r1, b1);
			if (t < b1 && b>t1 && r>l1 && l<r1 )
			{
				if (firepots->GetState()!= FIREPOTS_STATE_BREAK)
					firepots->SetState(FIREPOTS_STATE_BREAK);
			}
		}
	}
}
void Weapon::Render()
{
	int ani_left, ani_right;
	switch (level)
	{
	case 1:
		ani_left = WHIP_ANI_LV1_LEFT;
		ani_right = WHIP_ANI_LV1_RIGHT;
		break;
	case 2:
		ani_left = WHIP_ANI_LV2_LEFT;
		ani_right = WHIP_ANI_LV2_RIGHT;
		break;
	default:
		ani_left = WHIP_ANI_LV3_LEFT;
		ani_right = WHIP_ANI_LV3_RIGHT;
	}
	int ani;
	ani = WHIP_ANI_NOTHING;
	if (WhipAttack)
	{
		if (Simon_clone->nx > 0)
			ani = ani_right;
		else
			ani = ani_left;
	}
	animations[ani]->Render(x,y,255);
	RenderBoundingBox();
	if (animations[ani]->GetCurrentFrame() == 3)
		WhipAttack = false;
		
}
void Weapon::SetState(int stat)
{
	CGameObject::SetState(stat);
	switch (state=WHIP_STATE_ATTACK)
	{
	case WHIP_STATE_ATTACK:
		WhipAttack = true;
		break;
	}
}
void Weapon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	int ani_left, ani_right;
	float fullLength = SHORT_WHIP_FULL_LENGTH;
	switch (level)
	{
	case 1:
		ani_left = WHIP_ANI_LV1_LEFT;
		ani_right = WHIP_ANI_LV1_RIGHT;
		break;
	case 2:
		ani_left = WHIP_ANI_LV2_LEFT;
		ani_right = WHIP_ANI_LV2_RIGHT;
		break;
	default:
		ani_left = WHIP_ANI_LV3_LEFT;
		ani_right = WHIP_ANI_LV3_RIGHT;
		fullLength = LONG_WHIP_FULL_LENGTH;
	}
	if (Simon_clone->nx > 0)
	{
		if (animations[ani_right]->GetCurrentFrame() == 0)
		{
			left = x;
			top = y;
			right = x + 9.0f;
			bottom = y + 24.0f;
		}
		else if (animations[ani_right]->GetCurrentFrame() == 1)
		{
			left = x;
			top = y;
			right = x + 17.0f;
			bottom = y + 19.0f;
		}
		else if (animations[ani_right]->GetCurrentFrame() == 2)
		{
			left = x;
			top = y;
			right = x + fullLength;
			bottom = y + 8.0f;
		}
	}
	if (Simon_clone->nx < 0)
	{
		if (animations[ani_left]->GetCurrentFrame() == 0)
		{
			left = x;
			top = y;
			right = x + 9.0f;
			bottom = y + 24.0f;
		}
		else if (animations[ani_left]->GetCurrentFrame() == 1)
		{
			left = x;
			top = y;
			right = x + 17.0f;
			bottom = y + 19.0f;
		}
		else if (animations[ani_left]->GetCurrentFrame() == 2)
		{
			left = x;
			top = y;
			right = x + fullLength;
			bottom = y + 8.0f;
		}
	}

}

void Weapons::setLevel()
{
	level += 1;
	if (level > 3)
	{
		level = 1;
	}
}

int Weapons::getLevel()
{
	return level;
}
