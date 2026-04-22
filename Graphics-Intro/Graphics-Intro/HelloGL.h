#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Object.h"
#include "MeshLoader.h"
#include "Text.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	//constructor
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeyboard(int key, int x, int y);

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();
	void InitCam();
	void NewText(const char* text, Vector3 position, Colour colour);

	struct Sphere
	{
		float radius;
		Vector3 position;
	};

	Sphere sphere1;
	Sphere sphere2;

	void initSpheres();
	void drawSpheres(float distance, bool distanceSquared);
	float calculateDistanceSquared(Sphere s1, Sphere s2);
	
private:
	const float delta = 0.5f;

	//camera pointer
	Camera* camera;

	SceneObject* objects[100];
	Object* teapot;

	Vector4* lightPosition;
	Lighting* lightData;
};

