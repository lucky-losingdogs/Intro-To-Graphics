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
#include "Ray.h"
#include <vector>

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
	void MouseClick(int button, int state, int x, int y);

	SceneObject* GetObjectBounds(Vector3 cursor);
	SceneObject* CheckClickObject();

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();
	void InitCam();
	void InitMouse();
	void NewText(const char* text, Vector3 position, Colour colour);
	
private:
	const int windowHeight = 800, windowWidth = 800;
	const float delta = 0.5f;

	//camera pointer
	Camera* camera;

	Vector2* mousePos;

	vector<SceneObject*> objects;
	Object* teapot;

	Vector4* lightPosition;
	Lighting* lightData;
};

