#include "BackGround.h"

BackGround::BackGround(){}
void BackGround::Render() {
	animations[0]->Render(x, y);
}

void BackGround::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	return;

}

BackGround::~BackGround() {}

