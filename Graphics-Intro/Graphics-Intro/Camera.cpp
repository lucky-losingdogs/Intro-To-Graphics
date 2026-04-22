#include "Camera.h"

Camera::Camera()
{
	camMoveX = 0.0f;
	camMoveY = 0.0f;
	camMoveZ = 0.0f;

	eye = Vector3::SetVector3(0, 0, -1);
	center = Vector3::SetVector3(0, 0, 0);
	up = Vector3::SetVector3(0, 1, 0);
	forward = Vector3::SetVector3(0, 0, -1);
}

Camera::~Camera()
{
	delete this;
}

void Camera::Update()
{
	center = Vector3::AddVector3(eye, forward);
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

void Camera::MoveCamera(unsigned char key, float delta)
{
	//moves the camera along X or Y axis depending on keyboard input
	switch (key)
	{
	case 'd':
		eye.x += delta;
		break;
	case 'a':
		eye.x -= delta;
		break;
	case 'w':
		eye.y += delta;
		break;
	case 's':
		eye.y -= delta;
		break;
	//moves the camera along Z axis if keyboard input is special keys (up and down arrow keys)
	case GLUT_KEY_UP:
		eye.z += forward.z * delta;
		break;
	case GLUT_KEY_DOWN:
		eye.z -= forward.z * delta;
		break;
	}
}