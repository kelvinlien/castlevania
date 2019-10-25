#include "dagger.h"
#include"Simon.h"
#include "FirePots.h"
#include<iostream>

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects)
{
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (daggerAttack)
	{
		if (nx > 0)
			vx = DAGGER_SPEED;
		if (nx < 0)
			vx = -DAGGER_SPEED;
		CalcPotentialCollisions(coObjects, coEvents);

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += vx * dt;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			// Collision logic with firepots
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<FirePots *>(e->obj)) // if e->obj is Firepots
				{
					FirePots *firepots = dynamic_cast<FirePots *>(e->obj);

					// va cham ben phai 
					if (firepots->nx < 0 || firepots->nx >0)
					{
						this->SetState(DAGGER_STATE_COLLISION);
						firepots->SetState(FIREPOTS_STATE_BREAK);
					}
					
				}
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else return;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	//	// block 
	//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty * dy + ny * 0.4f;
	//	if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;
	//}
	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Dagger::Render()
{
	int ani;
	if (daggerAttack)
	{
		if (nx > 0)
			ani = DAGGER_ANI_RIGHT;
		else 
			ani = DAGGER_ANI_LEFT;
	}
	else return;
	animations[ani]->Render(x, y, 255);
	RenderBoundingBox();
}
void Dagger::SetState(int stat)
{
	CGameObject::SetState(stat);
	if (state == DAGGER_STATE_NORMAL)
	{
		daggerAttack = true;
	}
	else if (state == DAGGER_STATE_COLLISION)
		daggerAttack = false;
	else false;
}
void Dagger::Get_simon(Simon *simon) { 
	Simon_clone = simon;
	x = Simon_clone->x+ 8.0f;
	y = Simon_clone->y + 9.0f; 
	nx = Simon_clone->nx; 
}
void Dagger::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 10.0f;
	bottom = y + DAGGER_BBOX_HEIGHT;
}
