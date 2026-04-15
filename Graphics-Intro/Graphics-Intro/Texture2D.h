#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <iostream>
#include <fstream>
using namespace std;

class Texture2D
{
private:
	//texture id (use multiple ids for multiple textures on 1 obj)
	GLuint ID;
	int width, height;

public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return ID; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
};

