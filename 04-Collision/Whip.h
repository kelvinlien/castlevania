#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Weapon.h";
#include "Simon.h";

#define level1WhipWidth 23
#define level1WhipHeight 8

class Whip : public Weapon
{
public:
	Whip();
	~Whip();
	void setWhipLevel(int level);
	int getWhipLevel();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render(Simon *s);
protected:
	int whipLevel;
	int isHidden;
};