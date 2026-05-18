#include "HelloGL.h"
#include "Cube.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitCam();
	InitMouse();
	InitLighting();
	InitObjects();
	InitText();

	CreateMenu();
	
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::Display()
{
	//clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw skybox
	skyBox->SetCentre(Vector3(camera->center.x, camera->center.y, camera->center.z));
	skyBox->Draw();

	DrawList(listHead);

	DisplayData();

	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	//reset model view matrix so previous transformations aren't included
	glLoadIdentity();

	camera->Update();
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(lightPosition->x));

	UpdateList(listHead);

	//marks the current window as needing to be redisplayed
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//changes the key input to lower case to stop caps not working 
	key = (char)tolower(key);

	if (key == 'm')
	{
		//close menu and deattach
		if (openMenu)
		{
			glutDetachMenu(GLUT_LEFT_BUTTON);
			openMenu = false;
		}
		//open menu by attaching menu to LMB
		else
		{
			glutAttachMenu(GLUT_LEFT_BUTTON);
			openMenu = true;
		}
	}

	camera->MoveCamera(key, delta);
}

void HelloGL::MouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		moveMouse = false;

		system("CLS");
		//getting cursor position
		mousePos->x = x;
		mousePos->y = y;

		SceneObject* clickedObj = CheckClickObject(listHead);
		if (clickedObj != nullptr)
		{
			clickedObj->OnClick();
		}
	}
	//allow cam movement when right button pressed down
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		moveMouse = true;
		firstClick = true;
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
	else if (state == GLUT_UP)
	{
		moveMouse = false;
	}
}

void HelloGL::MouseMove(int x, int y)
{
	//only allow camera movement if RMB held down
	if (!moveMouse)
		return;

	//get screen center
	Vector2 center;
	center.x = windowWidth / 2;
	center.y = windowHeight / 2;

	//avoid snapping when warping to centre
	if (firstClick)
	{
		firstClick = false;
		return;
	}

	mouseDelta->x = x - center.x;
	mouseDelta->y = center.y - y;

	mouseDelta->x *= mouseSensitivity;
	mouseDelta->y *= mouseSensitivity;

	camera->RotateCamera(mouseDelta);

	//set cursor to center of screen
	glutWarpPointer(windowWidth / 2, windowHeight / 2);
}

void HelloGL::CreateMenu()
{
	//create main menu
	mainMenu = glutCreateMenu(GLUTCallbacks::MenuHandler);


	int objectCount = objects->GetListSize(listHead);
	for (int i = 0; i < objectCount; i++)
	{
		//create sub menu for each obj in the world
		LinkedNode<SceneObject*>* currentNode = objects->GetNode(listHead, i);
		int subMenu = glutCreateMenu(GLUTCallbacks::MenuHandler);
		textureMenus.push_back(subMenu);

		for (int j = 0; j < allTextures.size(); j++)
		{
			//add current obj index + texture index together to access both
			int menuValue = i * 1000 + j;

			//add an entry for each texture
			glutAddMenuEntry(allTextures[j].second.c_str(), menuValue);
		}

		//switch back to main menu and add submenu
		glutSetMenu(mainMenu);
		glutAddSubMenu(currentNode->data->GetName().c_str(), textureMenus[i]);
	}
}

//update the texture of the node selected with the texture selected
void HelloGL::MenuHandler(int option)
{
	//decode option value to get the obj index and texture index
	int objIndex = option / 1000;
	int texIndex = option % 1000;
	
	LinkedNode<SceneObject*>* node = objects->GetNode(listHead, objIndex);
	node->data->UpdateTexture(allTextures[texIndex].first);
}

void HelloGL::InitGL(int argc, char* argv[])
{
	srand((unsigned int)time(nullptr));
	
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Best OpenGL In The World");
	glutDisplayFunc(GLUTCallbacks::Display);

	//get keyboard input
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	//get mouse click input
	glutMouseFunc(GLUTCallbacks::MouseClick);

	//get mouse motion when holding a mouse button
	glutMotionFunc(GLUTCallbacks::MouseUpdate);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	//switch to identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set viewport to window size
	glViewport(0, 0, windowWidth, windowHeight);

	//set the correct perspective
	gluPerspective(45, 1, 0.5, 1000);

	//switch to model view matrix to work w/ models
	glMatrixMode(GL_MODELVIEW);

	//enable depth testing so overlapping triangles render correctly
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	//enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//enable lighting and the first light source
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void HelloGL::InitSkyBox(Mesh* cubeMesh)
{
	Texture2D* tempTexture = new Texture2D();
	tempTexture->Load((char*)"penguins.raw", 512, 512);
	skyBox = new SkyBox(cubeMesh, tempTexture,0,0,0);
}

void HelloGL::InitMesh()
{
	cubeMesh = MeshLoader::Load((char*)"cube.txt");
	pawnMesh = ObjLoader::Load((char*)"Obj\\pawn.obj");
	catMesh = ObjLoader::Load((char*)"Obj\\cat.obj");

	chessTex = new Texture2D();
	chessTex->LoadBMP((char*)"checkerboard.bmp");
	pawnTex = new Texture2D();
	pawnTex->LoadBMP((char*)"WoodPawn.bmp");
	catTex = new Texture2D();
	catTex->LoadBMP((char*)"cat.bmp");

	allTextures.push_back({ chessTex, "Chess Texture" });
	allTextures.push_back({ pawnTex, "Pawn Texture" });
	allTextures.push_back({ catTex, "Cat Texture" });
}

void HelloGL::InitObjects()
{
	InitMesh();
	if (cubeMesh == nullptr || pawnMesh == nullptr || catMesh == nullptr)
		return;

	InitSkyBox(cubeMesh);

	objects->MakeNode(&listHead, (new Cube(cubeMesh, chessTex, 0, -10, 0)));
	objects->GetNode(listHead, 0)->data->Scale(Vector3{ 20, 2, 20 });
	SpawnPawn(6, pawnMesh, pawnTex);
	SpawnCat(4, catMesh, catTex);
}

//initialise the lighting properties of the scene
void HelloGL::InitLighting()
{
	lightPosition = new Vector4{0, 1, -0.3f, 0};

	lightData = new Lighting();
	lightData->ambient = Vector4{ 0.7f, 0.65f, 0.6f, 1.0f };
	lightData->diffuse = Vector4{ 0.8f, 0.8f, 0.8f, 1.0f };
	lightData->specular = Vector4{ 0.2f, 0.2f, 0.2f, 1.0f };
}

void HelloGL::InitCam()
{
	camera = new Camera;
}

void HelloGL::InitMouse()
{
	mousePos = new Vector2;
	mouseDelta = new Vector2;
}

void HelloGL::InitText()
{
	totalObjText = NewText("", Vector3(0,0,0), Colour{ 1.0f, 1.0f, 1.0f });
}

void HelloGL::DisplayData()
{
	//display text on 2d screen
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, windowWidth, windowHeight, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	string totalObj = "Number of objects: " + to_string(objects->GetListSize(listHead));

	//create a new text object that follows cam movement
	//set text to top left
	totalObjText->UpdateText(totalObj.c_str(), Vector3(10, 20, 0), Colour{ 1.0f, 1.0f, 1.0f });

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//make a new text object
Text* HelloGL::NewText(const char* text, Vector3 position, Colour colour)
{
	return new Text(text, position, colour);
}

SceneObject* HelloGL::GetObjectBounds(LinkedNode<SceneObject*>* node, Vector3 cursor)
{
	while (node != nullptr)
	{
		AABBCollider bounds = node->data->DefineBounds();
		if (cursor.x >= bounds.min.x && cursor.x <= bounds.max.x && cursor.y >= bounds.min.y && cursor.y <= bounds.max.y)
		{
			return node->data;
		}

		node = node->nextNode;
	}
	return nullptr;
}

SceneObject* HelloGL::CheckClickObject(LinkedNode<SceneObject*>* node)
{
	//make a ray and pass mouse pos
	Ray ray(mousePos->x, mousePos->y);

	float closestObjDistance = (numeric_limits<float>::max)();
	SceneObject* closestObj = nullptr;

	//go through every object and check if the ray intercepts its collider
	while (node != nullptr)
	{
		AABBCollider bounds = node->data->DefineBounds();
		float hitDistance;

		if (ray.RayIntersectsAABB(ray, bounds, hitDistance))
		{
			//ignore obj behind camera
			//if hit distance is smaller/closer than the current closest distance
			if (hitDistance >= 0.0f && hitDistance < closestObjDistance)
			{
				//set new closest obj
				closestObjDistance = hitDistance;
				closestObj = node->data;
			}
		}

		node = node->nextNode;
	}

	cout << "Clicked object: " << closestObj << "\n";
	return closestObj;
}

void HelloGL::DrawList(LinkedNode<SceneObject*>* node)
{
	//while the node is set, draw the obj
	while (node != nullptr)
	{
		node->data->Draw();
		node = node->nextNode;
	}
}

void HelloGL::UpdateList(LinkedNode<SceneObject*>* node)
{
	//while the node is set, update the obj
	while (node != nullptr)
	{
		node->data->Update();
		node = node->nextNode;
	}
}

void HelloGL::SpawnPawn(int count, ObjMesh* mesh, Texture2D* texture)
{
	int spacing = -1;
	int currentEnd = objects->GetListSize(listHead);

	for (int i = 0; i < count; i++)
	{
		objects->Append(listHead, (new Object(mesh, texture, spacing, -9, 5)));
		objects->GetNode(listHead, currentEnd + i)->data->Rotate(-90, Vector3{ 1, 0, 0 });

		spacing += 7;
	}
}

void HelloGL::SpawnCat(int count, ObjMesh* mesh, Texture2D* texture)
{
	int spacing = -20;
	int currentEnd = objects->GetListSize(listHead);

	for (int i = 0; i < count; i++)
	{
		objects->Append(listHead, (new Cat(mesh, texture, spacing, -3, 30)));
		LinkedNode<SceneObject*>* catNode = objects->GetNode(listHead, currentEnd + i);

		catNode->data->Rotate(180, Vector3{ 0, 1, 0 });
		catNode->data->Rotate(90, Vector3{ 1, 0, 0 });
		catNode->data->Scale(Vector3{ 0.2f, 0.2f, 0.2f });

		spacing += 10;
	}
}
