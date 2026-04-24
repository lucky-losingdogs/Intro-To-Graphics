#pragma once
#include "Collider.h"
#include <iostream>
using namespace std;

class Ray
{
private:
	Vector3 origin;
	Vector3 direction;

public:
	Ray(float x, float y);
	bool RayIntersectsAABB(const Ray& ray, const AABBCollider& bounds, float& closestDistance);
};

