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
#include "Cat.h"
#include "MeshLoader.h"
#include "ObjLoader.h"
#include "Text.h"
#include "Ray.h"
#include <vector>
#include "LinkedList.h"
#include "BinaryTree.h"
#include "SkyBox.h"
#include "Camera.h"

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
	void MouseClick(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	void CreateMenu();
	void MenuHandler(int option);

	SceneObject* GetObjectBounds(LinkedNode<SceneObject*>* node, Vector3 cursor);
	SceneObject* CheckClickObject(LinkedNode<SceneObject*>* node);

	void InitSkyBox(Mesh* cubeMesh);
	void InitMesh();
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();
	void InitCam();
	void InitMouse();
	void InitText();

	void DisplayData();
	Text* NewText(const char* text, Vector3 position, Colour colour);

	void DrawList(LinkedNode<SceneObject*>* node);
	void UpdateList(LinkedNode<SceneObject*>* node);
	
private:
	const int windowHeight = 800, windowWidth = 800;
	const float delta = 0.5f;

	//camera pointer
	Camera* camera;

	Vector2* mousePos;
	Vector2* mouseDelta;
	float mouseSensitivity = 0.1f;
	bool moveMouse = false;
	bool firstClick = true;

	Vector4* lightPosition;
	Lighting* lightData;

	LinkedList<SceneObject*>* objects;
	LinkedNode<SceneObject*>* listHead = nullptr;

	BinaryTree<int>* tree = new BinaryTree<int>();
	TreeNode<int>* treeHead = nullptr;

	SkyBox* skyBox;
	void SpawnPawn(int count, ObjMesh* mesh, Texture2D* texture);
	void SpawnCat(int count, ObjMesh* mesh, Texture2D* texture);

	Text* totalObjText;

	bool openMenu = false;
	int mainMenu;
	vector<int> textureMenus;

	Mesh* cubeMesh;
	ObjMesh* pawnMesh;
	ObjMesh* catMesh;
	Texture2D* chessTex;
	Texture2D* pawnTex;
	Texture2D* catTex;
	vector<pair<Texture2D*, string>> allTextures;
};