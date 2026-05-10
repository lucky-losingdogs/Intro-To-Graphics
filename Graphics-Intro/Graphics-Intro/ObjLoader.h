#pragma once
#include <Windows.h>
#include "Structures.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>

namespace ObjLoader
{
	ObjMesh* Load(char* path);
};