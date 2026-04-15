#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Vector3.h"

class SceneObject
{
protected:
	Mesh* _mesh;

	Vector3 position;
	GLfloat rotation;

public:
	SceneObject(Mesh* mesh, float x, float y, float z);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();
};

