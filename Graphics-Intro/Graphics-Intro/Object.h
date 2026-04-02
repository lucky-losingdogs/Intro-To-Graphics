#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Object
{
private:
	static Vertex* indexedVertices;
	static Face* indexedFaces;
	static Colour* indexedColours;
	static GLushort* indices;
	static int numVertices, numFaces, numColours, numIndices;

	Vector3 position;
	GLfloat rotation;

	void ParseFaceToken();

public:
	Object(float x, float y, float z);
	~Object();

	void Draw();
	void Update();
	static bool Load(char* path);
};

