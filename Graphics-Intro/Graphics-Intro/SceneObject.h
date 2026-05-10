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

	float rotation;
	Vector3 rotationAxis = Vector3{ 1, 0, 0 };
	Vector3 scale = Vector3{ 1, 1, 1 };
	Vector3 position = Vector3{ 0, 0, 0 };

	Collider* collider;

	string name = "";

public:
	SceneObject(Mesh* _mesh, Texture2D* _texture, float x, float y, float z);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();
	virtual void DefineMaterial();
	virtual void UpdateTexture(Texture2D* newTex);

	virtual void Scale(Vector3 newScale);
	virtual void Rotate(float rotationScale, Vector3 axis);
	virtual void Translate(Vector3 newPosition);

	virtual void CheckCollision(SceneObject* other);
	virtual AABBCollider DefineBounds();
	void ScaleVertex(Vertex& vertex);
	void TranslateVertex(Vertex& vertex);
	void RotateVertex(Vertex& vertex);
	Vertex HandleRotateVertex(Vertex vertex, float angleDegrees, Vector3 axis);

	virtual void OnClick();

	string GetName();
};