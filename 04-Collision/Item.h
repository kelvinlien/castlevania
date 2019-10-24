#pragma once
#include "GameObject.h";

class Item :public CGameObject
{
public:
	Item();
	~Item();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool getPicked();
	void setPicked(bool _picked);
protected:
	bool picked;
	bool onGround;
	bool disappear;
	DWORD pickUpTimer;
	DWORD actionTimer;
	int type;
	float width;
	float height;
};
