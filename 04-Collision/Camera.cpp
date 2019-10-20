#include "Camera.h"

Camera::Camera()
{
	cam_x = 0;
	cam_y = 0;
}

Camera::~Camera()
{
}

Camera* Camera::cam = NULL;

Camera *Camera::getInstance()	//singleton design pattern
{
	if (cam == NULL)
	{
		cam = new Camera();
	}
	return cam;
}

D3DXVECTOR2 Camera::getPosition()	//get the current position of the camera
{
	return D3DXVECTOR2(cam_x,cam_y);
}

void Camera::setPosition(float x, float y)	//set the camera position
{
	cam_x = x;
	cam_y = y;
}
