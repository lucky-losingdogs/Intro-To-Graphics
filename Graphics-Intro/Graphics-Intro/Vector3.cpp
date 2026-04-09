#include "Vector3.h"

Vector3 Vector3::SetVector3(float x, float y, float z)
{
	Vector3 vector3 = { x, y, z };
	return vector3;
}

Vector3 Vector3::AddVector3(Vector3 a, Vector3 b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 Vector3::NormalizeVector3(Vector3 v)
{
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return { v.x / length, v.y / length, v.z / length };
}