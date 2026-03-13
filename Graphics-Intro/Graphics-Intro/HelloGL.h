#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	enum Shape
	{
		Triangle, Rectangle, Pentagon
	};
	
	//constructor
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void DrawPolygon();
	void DrawTriangle();
	void DrawPentagon();

	void RotateShape(float rotation, float direction, Shape drawShape);
	
private:
	float rotationTri;
	float rotationRect;
	float rotationPent;
};

