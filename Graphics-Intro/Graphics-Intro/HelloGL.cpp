#include "HelloGL.h"

Vertex HelloGL::cubeVertices[] =
{
	1, 1, 1,  -1, 1, 1, //v0-v1
	-1,-1, 1,  1,-1, 1, //v2-v3
	1, -1, -1,  1,1, -1, //v4-v5
	-1, 1,-1,  -1,-1,-1, //v6-v7
};

Colour HelloGL::cubeColours[] =
{
	1, 1, 1,  1, 1, 0, //v0-v1
	1,0, 0,   1,0, 1, //v2-v3
	0, 0, 1,   0, 1, 1, //v4-v5
	0, 1, 0,   0, 0, 0, //v6-v7
};

GLushort HelloGL::cubeIndices[] = 
{
	0, 1, 2,  2, 3, 0, // front
	0, 3, 4,  4, 5, 0, // right
	0, 5, 6,  6, 1, 0, // top
	1, 6, 7,  7, 2, 1, // left
	7, 4, 3,  3, 2, 7, // bottom
	4, 7, 6,  6, 5, 4  // back
};

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
	rotationTri = 0.0f;
	rotationRect = 0.0f;
	rotationPent = 0.0f;

	camMoveX = 0.0f;
	camMoveY = 0.0f;
	camMoveZ = 0.0f;

	CamInit();
	
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);

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

	/*RotateShape(rotationTri, -1.0f, Triangle);
	RotateShape(rotationRect, 1.0f, Rectangle);
	RotateShape(rotationPent, -1.0f, Pentagon);*/

	glTranslatef(-1, -1, -1);
	DrawCube();

	glTranslatef(3, -1, 1);
	DrawPyramid();

	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	//reset model view matrix so previous transformations aren't included
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
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
		camera->eye = SetVector3(camMoveX, camera->eye.y, camera->eye.z);
		camMoveX += delta;
		break;
	case 'a':
		camera->eye = SetVector3(camMoveX, camera->eye.y, camera->eye.z);
		camMoveX -= delta;
		break;
	case 'w':
		camera->eye = SetVector3(camera->eye.x, camMoveY, camera->eye.z);
		camMoveY -= delta;
		break;
	case 's':
		camera->eye = SetVector3(camera->eye.x, camMoveY, camera->eye.z);
		camMoveY += delta;
		break;
	}
}

void HelloGL::SpecialKeyboard(int key, int x, int y)
{
	//moves the camera along Z axis if keyboard input is special keys (up and down arrow keys)
	switch (key)
	{
	case GLUT_KEY_UP:
		camera->eye = SetVector3(camera->eye.x, camera->eye.y, camMoveZ);
		camMoveZ += delta;
		break;
	case GLUT_KEY_DOWN:
		camera->eye = SetVector3(camera->eye.x, camera->eye.y, camMoveZ);
		camMoveZ -= delta;
		break;
	}
}

void HelloGL::CamInit()
{
	camera = new Camera();

	//camera->eye = SetVector3(0, 0, -1);
	camera->eye = SetVector3(5, 5, -5);
	camera->center = SetVector3(0, 0, 0);
	camera->up = SetVector3(0, 1, 0);
}

Vector3 HelloGL::SetVector3(float x, float y, float z)
{
	Vector3 vector3 = { x, y, z };
	return vector3;
}

void HelloGL::DrawCube()
{
	//enabling new state
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//set arrays that are being used to draw
	glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
	glColorPointer(3, GL_FLOAT, 0, cubeColours);
	
	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, cubeIndices);
	glPopMatrix();

	//disabling state
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
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

void HelloGL::DrawPolygon()
{
	//starts to draw a polygon
	glBegin(GL_POLYGON);
	{
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex2f(-0.75, 0.5); //define the first point of the polygon, top left
		glVertex2f(0.75, 0.5); //next point, top right
		glVertex2f(0.75, -0.5); //bottom right
		glVertex2f(-0.75, -0.5); //last point of the polygon, bottom left
	}
	glEnd(); //defines the end of the draw
}

void HelloGL::DrawTriangle()
{
	//starts to draw a triangle
	glBegin(GL_TRIANGLES);
	{
		//setting all the vertices to pink
		glColor4f(1.0f, 0.0f, 1.0f, 1.0f);

		//defining each vertex of a triangle
		glVertex2f(-0.9, 0.3);
		glVertex2f(-0.4, 0.3);
		glVertex2f(-0.65, 0.7);
	}
	glEnd(); //defines the end of the draw
}

void HelloGL::DrawPentagon()
{
	//starts to draw a Pentagon
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

		//defining each vertex of a triangle
		glVertex2f(0.225, 0.45);
		glVertex2f(0.45, 0.1);
		glVertex2f(0.25, -0.25);
		glVertex2f(-0.1, -0.15);
		glVertex2f(-0.15, 0.3);
	}
	glEnd(); //defines the end of the draw
}

void HelloGL::RotateShape(float rotation, float direction, Shape drawShape)
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, direction);

	switch (drawShape)
	{
	case Triangle:
		glTranslatef(0, 0, -5);
		DrawTriangle();
		break;
	case Rectangle:
		glTranslatef(0.4f , 0.8f, 0);
		DrawPolygon();
		break;
	case Pentagon:
		glTranslatef(0.6f, 0.6f, 0);
		DrawPentagon();
		break;
	}

	glPopMatrix();
}