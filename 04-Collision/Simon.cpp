#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	int ani;
	int lastFrame = 0;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	if (IsAttacking && IsSitting)
	{
		lastFrame = 2;
		if (nx > 0)
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_SIT_ATTACK_LEFT;

	}
	else if (IsSitting )
	{
		lastFrame = 1;
		if (nx > 0)
			ani = SIMON_ANI_SIT_RIGHT;
		else
			ani = SIMON_ANI_SIT_LEFT;

	}
	else if (IsAttacking)
	{
		lastFrame = 2;
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
	}
	else
		if (vx == 0)
		{
			if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
			else ani = SIMON_ANI_BIG_IDLE_LEFT;
		}
		else if (vx > 0)
		{
			ani = SIMON_ANI_BIG_WALKING_RIGHT;
			lastFrame = 2;
		}
		else
		{
			ani = SIMON_ANI_BIG_WALKING_LEFT;
			lastFrame = 2;
		}


	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);
	RenderBoundingBox();
	if (animations[ani]->GetCurrentFrame() == lastFrame)
	{
		if (IsAttacking)
			IsAttacking = false;
		if (IsSitting) {
			IsSitting = false;
		}
		if (IsJumping)
			IsJumping = false;
	}

	
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		if (IsJumping)
			break;
		IsJumping = true;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		IsJumping = false;
		break;
	case SIMON_STATE_ATTACK:
		vx = 0;
		IsAttacking = true;
		break;
	case SIMON_STATE_SIT_IDLE:
		vx = 0;
		/*y+=4;*/
		IsSitting = true;
		IsJumping = false;
		break;
	case SIMON_STATE_SIT_ATTACK_LEFT:
		vx = 0;
		nx = -1;
		IsSitting = true;
		IsAttacking = true;
		break;
	case SIMON_STATE_SIT_ATTACK_RIGHT:
		vx = 0;
		nx = 1;
		IsSitting = true;
		IsAttacking = true;
		break;
	case SIMON_STATE_STAND:
		y -= 5;
		IsSitting = false;
		IsJumping = false;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y;
	right = x + SIMON_BIG_BBOX_WIDTH;
	bottom = y + SIMON_BIG_BBOX_HEIGHT;
	if (IsSitting)
	{
		bottom -= 5;
	}

}

int Simon::getSimonnx()
{
	return nx;
}

void Simon::setSimonnx(int _nx)
{
	nx = _nx;
}

bool Simon::Get_IsJumping()
{
	return IsJumping;
}

