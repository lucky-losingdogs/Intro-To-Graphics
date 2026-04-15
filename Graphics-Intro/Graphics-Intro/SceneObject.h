#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Vector3.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* mesh;
	Texture2D* texture;

	Vector3 position;
	GLfloat rotation;

public:
	SceneObject(Mesh* _mesh, Texture2D* _texture, float x, float y, float z);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();
};

