#pragma once
#include "GameObject.h";

class Effect :public CGameObject
{
public:
	Effect();
	~Effect();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
private:
	bool ended;
	DWORD timer;
};
