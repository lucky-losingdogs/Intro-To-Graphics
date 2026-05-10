#pragma once
#include "SceneObject.h"

class SkyBox : public SceneObject
{
private:
	Texture2D* skyboxTex[6];
	Vector3 camCentre;

	void LoadSkybox();
	Texture2D* MakeTexture(char* path);

public:
	SkyBox(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	void SetCentre(Vector3 newCentre);

	void Draw() override;
};

