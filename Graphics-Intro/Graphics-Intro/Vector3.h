#pragma once
#include <cmath>

class Vector3
{
public:
	float x, y, z;

	static Vector3 SetVector3(float x, float y, float z);
	static Vector3 AddVector3(Vector3 a, Vector3 b);
	static Vector3 NormalizeVector3(Vector3 v);
};