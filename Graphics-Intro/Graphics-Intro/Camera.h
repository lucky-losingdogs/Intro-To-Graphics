#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Vector3.h"

class Camera
{
private:
	float camMoveX, camMoveY, camMoveZ;

public:
	Camera();
	~Camera();
	
	void Update();
	void MoveCamera(unsigned char key, float delta);

	Vector3 eye, center, up, forward;
};

