#include "Collider.h"
#include <iostream>

AABBCollider::AABBCollider(Mesh* mesh, Vector3 position)
{
    Vertex* vertices = mesh->vertices;
    min = vertices[0];
    max = vertices[0];
    
    //set the min and max vertices by comparing all of the vertices of the mesh
    for (int i = 0; i < mesh->vertexCount; i++)
    {
        if (vertices[i].x < min.x)
            min.x = vertices[i].x;
        if (vertices[i].y < min.y)
            min.y = vertices[i].y;
        if (vertices[i].z < min.z)
            min.z = vertices[i].z;

        if (vertices[i].x > max.x)
            max.x = vertices[i].x;
        if (vertices[i].y > max.y)
            max.y = vertices[i].y;
        if (vertices[i].z > max.z)
            max.z = vertices[i].z;
    }

    min = Vector3::AddVector3(min, position);
    max = Vector3::AddVector3(max, position);
}

//check if the min/max vector values collide with the other min/max vectors
bool AABBCollider::Intersects(const Collider &other) const
{
    //try to convert from parent Collider to AABB
    const AABBCollider* aabb = dynamic_cast<const AABBCollider*>(&other);
    if (!aabb)
        return false;

    return (max.x >= aabb->min.x && min.x <= aabb->max.x) && (max.y >= aabb->min.y && min.y <= aabb->max.y) && (max.z >= aabb->min.z && min.z <= aabb->max.z);
}

SphereCollider::SphereCollider(float _radius, Vector3 _position)
{
    radius = _radius;
    position = _position;
}

bool SphereCollider::Intersects(const Collider& other) const
{
    //try to convert from parent Collider to sphere
    const SphereCollider* otherSphere = dynamic_cast<const SphereCollider*>(&other);
    if (!otherSphere)
        return false;

    float radiusDistance = pow(radius + otherSphere->radius, 2);
    float radiusSqr = radiusDistance * radiusDistance;
    float distanceSqr = CalculateDistanceSquared(position, otherSphere->position);

    if (distanceSqr <= radiusDistance)
    {
        return true;
    }
    else
    {
        return false;
    }

    //return distSqr <= radiusSqr;
}

float SphereCollider::CalculateDistanceSquared(Vector3 pos1, Vector3 pos2)
{
    float distance = ((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y)) + ((pos1.z - pos2.z) * (pos1.z - pos2.z));
    return distance;
}