#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"

#define REFRESHRATE 16

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye, center, up;
};

class HelloGL
{
public:
	enum Shape
	{
		Triangle, Rectangle, Pentagon
	};

	Camera* camera;
	
	//constructor
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeyboard(int key, int x, int y);

	void CamInit();
	Vector3 SetVector3(float x, float y, float z);

	void DrawPolygon();
	void DrawTriangle();
	void DrawPentagon();

	void RotateShape(float rotation, float direction, Shape drawShape);
	
private:
	float rotationTri;
	float rotationRect;
	float rotationPent;

	float camMoveX;
	float camMoveY;
	float camMoveZ;
	const float delta = 0.1f;
};

