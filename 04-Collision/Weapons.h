#pragma once
#include "GameObject.h"
#include"Simon.h"
#define  WHIP_STATE_ATTACK 100
#define  WHIP_ANI_NOTHING  0
#define  WHIP_ANI_LV1_RIGHT    1
#define  WHIP_ANI_LV1_LEFT     2
#define  WHIP_ANI_LV2_RIGHT    3
#define  WHIP_ANI_LV2_LEFT     4
#define  WHIP_ANI_LV3_RIGHT    5
#define  WHIP_ANI_LV3_LEFT     6
#define WHIP_BBOX_WIDTH    23
#define WHIP_BBOX_HEIGHT   8
class Weapons :public CGameObject
{
	DWORD timer = 0;
	Simon *Simon_clone;
	bool WhipAttack;
	int level = 1;
public:
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int stat);
	void Get_simon(Simon *simon) { Simon_clone = simon; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void setLevel();
	int getLevel();
};

