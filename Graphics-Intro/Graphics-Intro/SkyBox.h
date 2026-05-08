#pragma once
#include "SceneObject.h"

class SkyBox : public SceneObject
{
private:
	Texture2D* skyboxTex[6];
	float size;

public:
	SkyBox(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	void LoadSkybox();
	Texture2D* MakeTexture(char* path);

	void Draw() override;
};

