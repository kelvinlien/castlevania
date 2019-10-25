#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK			500
#define SIMON_STATE_SIT_IDLE		600
#define SIMON_STATE_STAND           700
#define SIMON_STATE_SIT_ATTACK_RIGHT 800
#define SIMON_STATE_SIT_ATTACK_LEFT 900

#define SIMON_ANI_BIG_IDLE_RIGHT		0
#define SIMON_ANI_BIG_IDLE_LEFT			1


#define SIMON_ANI_BIG_WALKING_RIGHT			2
#define SIMON_ANI_BIG_WALKING_LEFT			3
#define SIMON_ANI_ATTACK_RIGHT      4
#define SIMON_ANI_ATTACK_LEFT		5
#define SIMON_ANI_SIT_RIGHT			6
#define SIMON_ANI_SIT_LEFT			7
#define SIMON_ANI_DIE				8
#define SIMON_ANI_SIT_ATTACK_RIGHT	9
#define SIMON_ANI_SIT_ATTACK_LEFT	10

#define SIMON_BIG_BBOX_WIDTH  15
#define SIMON_BIG_BBOX_HEIGHT 27

//#define MARIO_SMALL_BBOX_WIDTH  13
//#define MARIO_SMALL_BBOX_HEIGHT 15

#define SIMON_UNTOUCHABLE_TIME 5000


class Simon : public CGameObject
{
	int level;
	bool IsAttacking; // dung de xet dieu kien attack
	bool IsSitting;
	bool IsJumping;
	int DaggerCount = 4;
	int untouchable;
	DWORD untouchable_start;
public:
	Simon() : CGameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool Get_IsAttack() { return IsAttacking; } 
	bool Get_IsSit() { return IsSitting; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int getSimonnx();
	int getDagger() { return DaggerCount; }
	void SetDagger(int n) { DaggerCount = n; }
	void setSimonnx(int _nx);
};