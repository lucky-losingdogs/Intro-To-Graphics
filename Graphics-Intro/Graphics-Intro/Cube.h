#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
private:
	static Vertex indexedVertices[];
	static Colour indexedColors[];
	static GLushort indices[];

	Vector3 position;
	GLfloat rotation;

public:
	Cube(float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

};