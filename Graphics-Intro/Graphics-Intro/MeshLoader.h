#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <iostream>
#include <fstream>

namespace MeshLoader
{
	Mesh* Load(char* path);
};

