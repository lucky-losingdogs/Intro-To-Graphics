#pragma once
#include <Windows.h>
#include "Structures.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

namespace MeshLoader
{
	Mesh* Load(char* path);
};

