#pragma once
#include "Vector3.h"

struct Camera
{
	Vector3 eye, center, up, forward;
};

struct Colour
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct Face
{
	GLfloat x, y, z;
};