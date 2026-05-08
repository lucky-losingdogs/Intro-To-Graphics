#include "Ray.h"

Ray::Ray(float x, float y)
{
	//get the screen size
	GLint viewport[4];

	//getting the camera and objects in scene
	GLdouble modelview[16];

	//getting the perspective
	GLdouble projection[16];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	//set mouse coordinates
	float winX = x;
	//flip y bc opengl expects y to start at bottom left instead of top left
	float winY = viewport[3] - y;

	GLdouble nearX, nearY, nearZ;
	GLdouble farX, farY, farZ;

	//converts the specified window coordinates into object/world coordinates
	//near the camera
	gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &nearX, &nearY, &nearZ);

	//far points in scene
	gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &farX, &farY, &farZ);

	Vector3 _origin = Vector3::SetVector3((float)nearX, (float)nearY, (float)nearZ);
	Vector3 _direction = Vector3::SetVector3((float)(farX - nearX), (float)(farY - nearY), (float)(farZ - nearZ));
	//normalise for a unit direction
	_direction = Vector3::Normalise(_direction);

	origin = _origin;
	direction = _direction;
}

bool Ray::RayIntersectsAABB(const Ray& ray, const AABBCollider& bounds, float& closestDistance)
{
	//first check for if ray is within bounds x and y
	//check how far along the ray the hit happens
	float xMin = (bounds.min.x - ray.origin.x) / ray.direction.x;
	float xMax = (bounds.max.x - ray.origin.x) / ray.direction.x;
	if (xMin > xMax)
		swap(xMin, xMax);

	float yMin = (bounds.min.y - ray.origin.y) / ray.direction.y;
	float yMax = (bounds.max.y - ray.origin.y) / ray.direction.y;
	if (yMin > yMax)
		swap(yMin, yMax);

	if ((xMin > yMax) || (yMin > xMax))
		return false;

	//get the largest min
	if (yMin > xMin)
		xMin = yMin;
	//get the smallest max
	if (yMax < xMax)
		xMax = yMax;

	//then check z for depth
	float zMin = (bounds.min.z - ray.origin.z) / ray.direction.z;
	float zMax = (bounds.max.z - ray.origin.z) / ray.direction.z;
	if (zMin > zMax) swap(zMin, zMax);

	if ((xMin > zMax) || (zMin > xMax))
		return false;

	closestDistance = xMin;
	return true;
}