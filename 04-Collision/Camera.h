#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
public:
	Camera();
	~Camera();
	static Camera *getInstance();
	D3DXVECTOR2 getPosition();
	void setPosition(float x, float y);

private:
	static Camera *cam;
	float cam_x;
	float cam_y;
};