#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Object.h"
#include "MeshLoader.h"
#include "Vector3.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	//camera pointer
	Camera* camera;

	SceneObject* objects[100];
	Object* teapot;

	//constructor
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeyboard(int key, int x, int y);

	void InitCam();

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	
private:
	float camMoveX;
	float camMoveY;
	float camMoveZ;
	const float delta = 0.5f;
};

