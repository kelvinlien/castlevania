#pragma once
#include "GameObject.h"
#include "Effect.h"
#include "Heart.h"

#define FIREPOTS_BBOX_WIDTH  16
#define FIREPOTS_BBOX_HEIGHT 32
#define FIREPOTS_STATE_BURN  100
#define FIREPOTS_STATE_BREAK 200
#define FIREPOTS_STATE_ITEM 300
#define FIREPOTS_STATE_REWARDED	400
#define FIREPOTS_STATE_TIMEOUT 500
#define FIREPOTS_ANI_NOTHING 0
#define FIREPOTS_ANI_BURN    1
#define EFFECT_ANI_BROKEN	 2
#define HEART_ANI_BIG		 3
class FirePots : public CGameObject		//firepot lifecycle: burn -> break -> effect -> item -> disappear/picked
										//variable lifecycle: ""
{
	enum type;
	bool IsBreak;
	bool itemExist = false;
	DWORD timer = 0;	//timer to track item exist time
	bool disappear = false;		//item timeout
	bool picked = false;		//item picked
	int id;
public:
	FirePots();
	~FirePots();
	virtual void Render();
	void SetState(int stat);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	bool isBreak();
	void setID(int ID);
	int getID();
	
};
