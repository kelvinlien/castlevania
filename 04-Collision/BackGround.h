#pragma once
#include"GameObject.h"
class BackGround:public CGameObject
{
public:
	BackGround();
	void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~BackGround();
};

