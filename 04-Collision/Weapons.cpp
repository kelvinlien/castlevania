#include "Weapons.h"
#include"Simon.h"



void Weapons::Update(DWORD time,vector<LPGAMEOBJECT>*colliable_object)
{
	if (Simon_clone->nx > 0)
	{
		if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 0)
		{
			this->x = Simon_clone->x - 7.2f;
			this->y = Simon_clone->y+5.0f;
		}
		else if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 1)
		{
			this->x = Simon_clone->x-11.0f;
			this->y = Simon_clone->y;
		}
		else if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 2)
	    {	
			this->x = Simon_clone->x + 18.0f;
			this->y = Simon_clone->y+5.5f;
		}
	}
	else if(Simon_clone->nx < 0)
	{
		if (animations[WHIP_ANI_LEFT]->GetCurrentFrame() == 0)
		{
			this->x = Simon_clone->x + 19.5f;
			this->y = Simon_clone->y+5.0f;
		}
		else if (animations[WHIP_ANI_LEFT]->GetCurrentFrame() == 1)
		{
			this->x = Simon_clone->x +11.2f;
			this->y = Simon_clone->y;
		}
		else if (animations[WHIP_ANI_LEFT]->GetCurrentFrame() == 2)
		{
			this->x = Simon_clone->x -18.5f;
			this->y = Simon_clone->y+5.5f;
		}
	}


}
void Weapons::Render()
{
	int ani;
	ani = WHIP_ANI_NOTHING;
	if (WhipAttack)
	{
		if (Simon_clone->nx > 0)
			ani = WHIP_ANI_RIGHT;
		else
			ani = WHIP_ANI_LEFT;
	}
	animations[ani]->Render(x,y,255);
	if (animations[ani]->GetCurrentFrame() == 3)
		WhipAttack = false;
		
}
void Weapons::SetState(int stat)
{
	CGameObject::SetState(stat);
	switch (state=WHIP_STATE_ATTACK)
	{
	case WHIP_STATE_ATTACK:
		WhipAttack = true;
		break;
	}
}
void Weapons::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (Simon_clone->nx > 0)
	{
		if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 0)
		{
			left = x;
			top = y;
			right = x + 9.0f;
			bottom = y + 24.0f;
		}
		else if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 1)
		{
			left = x;
			top = y;
			right = x + 17.0f;
			bottom = y + 19.0f;
		}
		else if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 2)
		{
			left = x;
			top = y;
			right = x + 23.0f;
			bottom = y + 8.0f;
		}
	}
	if (Simon_clone->nx > 0)
	{
		if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 0)
		{
			left = x;
			top = y;
			right = x + 9.0f;
			bottom = y + 24.0f;
		}
		else if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 1)
		{
			left = x;
			top = y;
			right = x + 17.0f;
			bottom = y + 19.0f;
		}
		else if (animations[WHIP_ANI_RIGHT]->GetCurrentFrame() == 2)
		{
			left = x;
			top = y;
			right = x + 23.0f;
			bottom = y + 8.0f;
		}
	}

}
