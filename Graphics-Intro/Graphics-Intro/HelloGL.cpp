#include "HelloGL.h"
#include "Cube.h"

Vertex HelloGL::pyramidVertices[] =
{
	-1, -1, 1,  1, -1, 1, //v0-v1
	-1, -1, -1,  1, -1, -1, //v2-v3
	0, 1, 0, //v4
};

Colour HelloGL::pyramidColours[] =
{
	1, 0, 1,  1, 1, 0, //v0-v1
	1,0, 0,   1,0, 1, //v2-v3
	1, 1, 1, //v4
};

GLushort HelloGL::pyramidIndices[] =
{
	1, 0, 2,  2, 3, 1, //bottom
	0, 1, 4, //front
	1, 3, 4, //right
	3, 2, 4, //back
	2, 0, 4, //left
};

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	
	InitCam();
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

	for (int i = 0; i < 100; i++)
	{
		objects[i]->Draw();
	}

	//teapot->Draw();

	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	//reset model view matrix so previous transformations aren't included
	glLoadIdentity();

	camera->center = Vector3::AddVector3(camera->eye, camera->forward);
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
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
	
	//moves the camera along X or Y axis depending on keyboard input
	switch (key)
	{
	case 'd':
		camera->eye.x += delta;
		break;
	case 'a':
		camera->eye.x -= delta;
		break;
	case 'w':
		camera->eye.y += delta;
		break;
	case 's':
		camera->eye.y -= delta;
		break;
	}
}

void HelloGL::SpecialKeyboard(int key, int x, int y)
{
	//moves the camera along Z axis if keyboard input is special keys (up and down arrow keys)
	switch (key)
	{
	case GLUT_KEY_UP:
		camera->eye.z += camera->forward.z * delta;
		break;
	case GLUT_KEY_DOWN:
		camera->eye.z -= camera->forward.z * delta;
		break;
	}
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
}

void HelloGL::InitCam()
{
	camMoveX = 0.0f;
	camMoveY = 0.0f;
	camMoveZ = 0.0f;
	
	camera = new Camera();

	//camera->eye = SetVector3(0, 0, -1);
	camera->eye = Vector3::SetVector3(5, 5, -5);
	camera->center = Vector3::SetVector3(0, 0, 0);
	camera->up = Vector3::SetVector3(0, 1, 0);
	camera->forward = Vector3::SetVector3(0, 0, -1);
}

void HelloGL::InitObjects()
{

	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");
	
	for (int i = 0; i < 50; i++)
	{
		objects[i] = new Cube(cubeMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}

	for (int i = 50; i < 100; i++)
	{
		objects[i] = new Pyramid(pyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}

	/*Object::Load((char*)"Obj\\teapot.obj");
	teapot = new Object(1, 1, 1);*/
}

void HelloGL::DrawPyramid()
{
	//enabling new state
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//set arrays that are being used to draw
	glVertexPointer(3, GL_FLOAT, 0, pyramidVertices);
	glColorPointer(3, GL_FLOAT, 0, pyramidColours);

	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, pyramidIndices);
	glPopMatrix();

	//disabling state
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}