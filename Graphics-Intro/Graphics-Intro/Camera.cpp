#include "Camera.h"

Camera::Camera()
{
	eye = Vector3::SetVector3(0, 0, -1);
	center = Vector3::SetVector3(0, 0, 0);
	up = Vector3::SetVector3(0, 1, 0);
	forward = Vector3::SetVector3(0, 0, -1);
	yaw = 0;
	pitch = 0;
}

Camera::~Camera()
{
	delete this;
}

void Camera::Update()
{
	center = Vector3::Add(eye, forward);
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

void Camera::MoveCamera(unsigned char key, float delta)
{
	Vector3 right = Vector3::CrossProduct(forward, up);
	right = Vector3::Normalise(right);
	
	//moves the camera along X axis
	switch (key)
	{
	case 'd':
		eye = Vector3::Add(eye, Vector3::Multiply(right, delta));
		break;
	case 'a':
		eye = Vector3::Subtract(eye, Vector3::Multiply(right, delta));
		break;
	//moves the camera along Z axis
	case 'w':
		eye = Vector3::Add(eye, Vector3::Multiply(forward, delta));
		break;
	case 's':
		eye = Vector3::Subtract(eye, Vector3::Multiply(forward, delta));
		break;
	}
}

void Camera::RotateCamera(Vector2* mouseDelta)
{
	yaw += mouseDelta->x;
	pitch += mouseDelta->y;

	//clamp yaw
	if (yaw > 360)
		yaw -= 360;
	if (yaw < -360)
		yaw += 360;

	//clamp pitch
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	//convert to radians
	float radYaw = yaw * 3.14159265f / 180.0f;
	float radPitch = pitch * 3.14159265f / 180.0f;

	Vector3 direction = Vector3::SetVector3(cosf(radYaw) * cosf(radPitch), sinf(radPitch), sinf(radYaw) * (cosf(radPitch)));
	forward = Vector3::Normalise(direction);
}
