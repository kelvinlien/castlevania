#pragma once
#include "GameObject.h"
#include"Simon.h"
#define  DAGGER_STATE_NORMAL 100   //trang thai binh thuong chua va cham
#define  DAGGER_STATE_COLLISION 200 
#define  DAGGER_ANI_RIGHT    0
#define  DAGGER_ANI_LEFT     1
#define DAGGER_BBOX_WIDTH    17
#define DAGGER_BBOX_HEIGHT   9
#define DAGGER_SPEED		 0.1f
class Dagger :public CGameObject
{
	DWORD timer = 0;
	Simon *Simon_clone;
	bool daggerAttack;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int stat);
	void Get_simon(Simon *simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

