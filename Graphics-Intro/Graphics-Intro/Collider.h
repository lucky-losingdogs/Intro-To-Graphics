#pragma once
#include "Structures.h"
#include <vector>
using namespace std;

class Collider
{
public:
    virtual bool Intersects(const Collider &other) const = 0;
    Vector3 position;
};

class AABBCollider : public Collider
{
public:
    AABBCollider(vector<Vertex> vertices, Vector3 position);
    bool Intersects(const Collider &other) const override;

    Vertex min;
    Vertex max;
};

class SphereCollider : public Collider
{
public:
    SphereCollider(float radius, Vector3 position);

    bool Intersects(const Collider& other) const override;
    static float CalculateDistanceSquared(Vector3 pos1, Vector3 pos2);

private:
    float radius;
};