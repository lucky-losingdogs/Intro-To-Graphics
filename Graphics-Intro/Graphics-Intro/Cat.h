#pragma once
#include "Object.h"

class Cat : public Object
{
private:
	float delta = 0.8f;

public:
	Cat(ObjMesh* _mesh, Texture2D* _texture, float x, float y, float z);
	~Cat();
	
	void OnClick() override;
	void Update() override;
};

