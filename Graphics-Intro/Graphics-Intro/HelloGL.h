#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"

class HelloGL
{
public:
	//constructor
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	void Display();

	void DrawPolygon();
	void DrawTriangle();
	void DrawPentagon();
};

