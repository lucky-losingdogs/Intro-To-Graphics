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

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* vertices;
	Colour* colours;
	GLushort* indices;
	TexCoord* texCoords;
	int vertexCount, colourCount, indexCount, texCoordCount;
};