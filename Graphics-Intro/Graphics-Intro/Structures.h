#pragma once
#include "Vector3.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"

struct Vector2
{
	float x, y;
};

struct Colour
{
	GLfloat r, g, b;
};

struct Normal
{
	GLfloat x, y, z;
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
	Normal* normals;
	GLushort* indices;
	TexCoord* texCoords;
	int vertexCount, normalsCount, indexCount, texCoordCount;
};

struct Vector4
{
	GLfloat x, y, z, w;
};

struct Lighting
{
	Vector4 ambient, diffuse, specular;
};

struct Material
{
	Vector4 ambient, diffuse, specular;
	GLfloat shininess;
};