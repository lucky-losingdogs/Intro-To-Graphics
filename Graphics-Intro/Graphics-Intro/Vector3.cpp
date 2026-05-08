#include "Vector3.h"
#include "Structures.h"

Vector3 Vector3::SetVector3(float x, float y, float z)
{
	Vector3 vector3 = { x, y, z };
	return vector3;
}

Vector3 Vector3::Add(Vector3 a, Vector3 b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vertex Vector3::Add(Vertex a, Vector3 b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 Vector3::Subtract(Vector3 a, Vector3 b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 Vector3::Multiply(Vector3 a, Vector3 b)
{
	return { a.x * b.x, a.y * b.y, a.z * b.z };
}

Vector3 Vector3::Multiply(Vector3 a, float b)
{
	return { a.x * b, a.y * b, a.z * b };
}

Vector3 Vector3::Normalise(Vector3 v)
{
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return { v.x / length, v.y / length, v.z / length };
}

Vector3 Vector3::CrossProduct(Vector3 a, Vector3 b)
{
	return { ((a.y * b.z) - (a.z * b.y)) - ((a.x * b.z) - (a.z * b.x)) + ((a.x * b.y) - (a.y * b.x))};
}
