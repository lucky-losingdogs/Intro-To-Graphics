#include "HelloGL.h"
#include "Cube.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitCam();
	InitLighting();
	InitObjects();
	initSpheres();
	
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

	/*for (int i = 0; i < 100; i++)
	{
		objects[i]->Draw();
	}*/

	//teapot->Draw();

	//create a new text object in the center of the camera (follows cam movement)
	//NewText("Hello OpenGL", Vector3::SetVector3(camera->center.x, camera->center.y, camera->center.z), Colour{ 0.0f, 0.0f, 0.0f });


	float distance = calculateDistanceSquared(sphere1, sphere2);
	drawSpheres(distance, true);

	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::initSpheres()
{
	sphere1.radius = 1.0f;
	sphere2.radius = 1.0f;

	sphere1.position.x = -1.5f;
	sphere2.position.x = 1.5f;
}

void HelloGL::drawSpheres(float distance, bool distanceSquared)
{
	float radiusDistance;
	if (distanceSquared)
		radiusDistance = pow(sphere1.radius + sphere2.radius, 2);
	else
		radiusDistance = sphere1.radius + sphere2.radius;

	//Draw Sphere 1
	glPushMatrix();

	//change the colour of the first sphere if it collides with the second
	if (distance <= radiusDistance)
		glColor3f(1, 0, 0);
	else
		glColor3f(0, 0, 1);

	glTranslatef(sphere1.position.x, sphere1.position.y, sphere1.position.z);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glutWireSphere(sphere1.radius, 20, 20);
	glPopMatrix();

	//Draw Sphere 2
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(sphere2.position.x, sphere2.position.y, sphere2.position.z);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glutWireSphere(sphere2.radius, 20, 20);
	glPopMatrix();
}

float HelloGL::calculateDistanceSquared(Sphere s1, Sphere s2)
{
	float distance = ((s1.position.x - s2.position.x) * (s1.position.x - s2.position.x)) + ((s1.position.y - s2.position.y) * (s1.position.y - s2.position.y)) + ((s1.position.z - s2.position.z) * (s1.position.z - s2.position.z));
	return distance;
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

	for (int i = 0; i < 100; i++)
	{
		objects[i]->Update();
	}

	//marks the current window as needing to be redisplayed
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//changes the key input to lower case to stop caps not working 
	key = (char)tolower(key);
	
	camera->MoveCamera(key, delta);

	if (key == 'm') {
		sphere1.position.x = sphere1.position.x + 0.1f;
	}
}

void HelloGL::SpecialKeyboard(int key, int x, int y)
{
	camera->MoveCamera(key, delta);
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutCreateWindow("Best OpenGL In The World");
	glutDisplayFunc(GLUTCallbacks::Display);

	//get keyboard input
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	//get special keyboard input
	glutSpecialFunc(GLUTCallbacks::SpecialKeyboard);

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

void HelloGL::InitObjects()
{
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);
	Texture2D* texture2 = new Texture2D();
	texture2->LoadBMP((char*)"snail.bmp");

	//loadBitMap((char*)"snail.bmp", (char*)"snail.raw");

	for (int i = 0; i < 50; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}

	for (int i = 50; i < 100; i++)
	{
		objects[i] = new Cube(cubeMesh, texture2, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}

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

//make a new text object
void HelloGL::NewText(const char* text, Vector3 position, Colour colour)
{
	Text* newText = new Text(text, position, colour);
}