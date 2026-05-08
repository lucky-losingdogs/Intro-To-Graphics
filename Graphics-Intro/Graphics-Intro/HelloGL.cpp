#include "HelloGL.h"
#include "Cube.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitCam();
	InitMouse();
	InitSkyBox();
	InitLighting();
	InitObjects();
	
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

	//display skybox
	glPushMatrix();
	glTranslatef(camera->center.x, camera->center.y, camera->center.z);
	skyBox->Draw();
	glPopMatrix();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}
	
	//teapot->Draw();

	//create a new text object in the center of the camera (follows cam movement)
	//NewText("Hello OpenGL", Vector3::SetVector3(camera->center.x, camera->center.y, camera->center.z), Colour{ 1.0f, 1.0f, 1.0f });

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

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			objects[i]->CheckCollision(objects[j]);
		}
	}

	//marks the current window as needing to be redisplayed
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//changes the key input to lower case to stop caps not working 
	key = (char)tolower(key);
	
	camera->MoveCamera(key, delta);
}

void HelloGL::SpecialKeyboard(int key, int x, int y)
{
	camera->MoveCamera(key, delta);
}

void HelloGL::MouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		system("CLS");
		//getting cursor position
		mousePos->x = x;
		mousePos->y = y;


		SceneObject* clickedObj = CheckClickObject();
		if (clickedObj != nullptr)
		{
			clickedObj->OnClick();
		}
	}
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Best OpenGL In The World");
	glutDisplayFunc(GLUTCallbacks::Display);

	//get keyboard input
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	//get special keyboard input
	glutSpecialFunc(GLUTCallbacks::SpecialKeyboard);

	//get mouse click input
	glutMouseFunc(GLUTCallbacks::MouseClick);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	//switch to identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set viewport to window size
	glViewport(0, 0, 800, 800);

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

	//texture filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//enable lighting and the first light source
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void HelloGL::InitSkyBox()
{
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Texture2D* tempTexture = new Texture2D();
	tempTexture->LoadBMP((char*)"snail.bmp");
	skyBox = new SkyBox(cubeMesh, tempTexture,0,0,0);

	skyBox->LoadSkybox();
}

void HelloGL::InitObjects()
{
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);
	Texture2D* texture2 = new Texture2D();
	texture2->LoadBMP((char*)"snail.bmp");

	objects.push_back(new Cube(cubeMesh, texture, 1.5f, 0, 5));
	objects.push_back(new Cube(cubeMesh, texture2, 1, 0, 35));

	/*Object::Load((char*)"Obj\\teapot.obj");
	teapot = new Object(1, 1, 1);*/
}

//initialise the lighting properties of the scene
void HelloGL::InitLighting()
{
	lightPosition = new Vector4();
	lightPosition->x = 0.0;
	lightPosition->y = 0.0;
	lightPosition->z = 1.0;
	lightPosition->w = 0.0;

	lightData = new Lighting();
	lightData->ambient.x = 0.2;
	lightData->ambient.y = 0.2;
	lightData->ambient.z = 0.2;
	lightData->ambient.w = 1.0;
	lightData->diffuse.x = 0.8;
	lightData->diffuse.y = 0.8;
	lightData->diffuse.z = 0.8;
	lightData->diffuse.w = 1.0;
	lightData->specular.x = 0.2;
	lightData->specular.y = 0.2;
	lightData->specular.z = 0.2;
	lightData->specular.w = 1.0;
}

void HelloGL::InitCam()
{
	camera = new Camera;
}

void HelloGL::InitMouse()
{
	mousePos = new Vector2;
}

//make a new text object
void HelloGL::NewText(const char* text, Vector3 position, Colour colour)
{
	Text* newText = new Text(text, position, colour);
}

SceneObject* HelloGL::GetObjectBounds(Vector3 cursor)
{
	for (int i = 0; i < objects.size(); i++)
	{
		AABBCollider bounds = objects[i]->DefineBounds();

		if (cursor.x >= bounds.min.x && cursor.x <= bounds.max.x && cursor.y >= bounds.min.y && cursor.y <= bounds.max.y)
		{
			return objects[i];
		}
	}

	return nullptr;
}

SceneObject* HelloGL::CheckClickObject()
{
	//make a ray and pass mouse pos
	Ray ray(mousePos->x, mousePos->y);

	float closestObjDistance = (numeric_limits<float>::max)();
	SceneObject* closestObj = nullptr;

	//go through every object and check if the ray intercepts its collider
	for (int i = 0; i < objects.size(); i++)
	{
		AABBCollider bounds = objects[i]->DefineBounds();
		float hitDistance;

		if (ray.RayIntersectsAABB(ray, bounds, hitDistance))
		{
			//ignore obj behind camera
			//if hit distance is smaller/closer than the current closest distance
			if (hitDistance >= 0.0f && hitDistance < closestObjDistance)
			{
				//set new closest obj
				closestObjDistance = hitDistance;
				closestObj = objects[i];
			}
		}
	}

	cout << "Clicked object: " << closestObj << "\n";
	return closestObj;
}