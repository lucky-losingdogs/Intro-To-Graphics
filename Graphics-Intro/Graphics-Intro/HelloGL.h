#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Object.h"
#include "Vector3.h"

#define REFRESHRATE 16

class HelloGL
{
private:
	static Vertex pyramidVertices[];
	static Colour pyramidColours[];
	static GLushort pyramidIndices[];

public:
	enum Shape
	{
		Triangle, Rectangle, Pentagon
	};

	//camera pointer
	Camera* camera;

	Cube* cube[100];
	Object* teapot;

	//constructor
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeyboard(int key, int x, int y);

	void CamInit();

	void ShapeInit();
	void DrawPyramid();
	
private:
	float camMoveX;
	float camMoveY;
	float camMoveZ;
	const float delta = 0.5f;
};

