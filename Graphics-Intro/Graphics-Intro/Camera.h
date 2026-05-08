#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "structures.h"

class Camera
{
public:
	Camera();
	~Camera();
	
	void Update();
	void MoveCamera(unsigned char key, float delta);
	void RotateCamera(Vector2* mouseDelta);

	Vector3 eye, center, up, forward;
	float yaw, pitch;
};

