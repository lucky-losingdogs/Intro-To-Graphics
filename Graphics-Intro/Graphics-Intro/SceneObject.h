#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Texture2D.h"
#include "Collider.h"
#include <vector>

class SceneObject
{
protected:
	Mesh* mesh;
	Texture2D* texture;
	Material* material;

	GLfloat rotation;

public:
	SceneObject(Mesh* _mesh, Texture2D* _texture, float x, float y, float z);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();
	virtual void DefineMaterial();

	virtual void CheckCollision(SceneObject* other);
	virtual AABBCollider DefineBounds();

	Collider* collider;
	Vector3 position;
};

