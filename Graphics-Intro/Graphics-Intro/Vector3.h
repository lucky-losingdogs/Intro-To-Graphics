#pragma once
#include <cmath>
struct Vertex;

class Vector3
{
public:
	float x, y, z;

	static Vector3 SetVector3(float x, float y, float z);
	static Vector3 Add(Vector3 a, Vector3 b);
	static Vertex Add(Vertex a, Vector3 b);
	static Vector3 Subtract(Vector3 a, Vector3 b);
	static Vector3 Multiply(Vector3 a, Vector3 b);
	static Vector3 Multiply(Vector3 a, float b);
	static Vector3 Normalise(Vector3 v);
	static Vector3 CrossProduct(Vector3 a, Vector3 b);
};