#pragma once
#include "SceneObject.h"

class Object : public SceneObject
{
protected:
	ObjMesh* objMesh;

private:
	float clickMovement = 6.5f;

public:
	Object(ObjMesh* _mesh, Texture2D* _texture, float x, float y, float z);
	~Object();

	void Draw() override;
	AABBCollider DefineBounds() override;
	void OnClick() override;
};

