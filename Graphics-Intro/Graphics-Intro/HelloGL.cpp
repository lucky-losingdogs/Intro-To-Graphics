#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	rotationTri = 0.0f;
	rotationRect = 0.0f;
	rotationPent = 0.0f;

	CamInit();
	
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutCreateWindow("Best OpenGL In The World");
	glutDisplayFunc(GLUTCallbacks::Display);

	//get keyboard input
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

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

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	RotateShape(rotationTri, -1.0f, Triangle);
	RotateShape(rotationRect, 1.0f, Rectangle);
	RotateShape(rotationPent, -1.0f, Pentagon);

	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	//reset model view matrix so previous transformations aren't included
	glLoadIdentity;
	
	//marks the current window as needing to be redisplayed
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//changes the key input to lower case to stop caps not working
	key = (char)tolower(key);
	
	if (key == 'd')
	{
		rotationTri += 0.5f;
		rotationRect += 0.2f;
		rotationPent += 0.8f;
	}
	if (key == 'a')
	{
		rotationTri -= 0.5f;
		rotationRect -= 0.2f;
		rotationPent -= 0.8f;
	}

	if (rotationTri >= 360.0f || rotationTri <= -360.0f)
	{
		rotationTri = 0.0f;
	}
	if (rotationRect >= 360.0f || rotationRect <= -360.0f)
	{
		rotationRect = 0.0f;
	}
	if (rotationPent >= 360.0f || rotationPent <= -360.0f)
	{
		rotationPent = 0.0f;
	}
}

void HelloGL::CamInit()
{
	camera = new Camera();

	camera->eye = SetVector3(0, 0, 1);
	camera->center = SetVector3(0, 0, 0);
	camera->up = SetVector3(0, 1, 0);
}

Vector3 HelloGL::SetVector3(float x, float y, float z)
{
	Vector3 vector3 = { x, y, z };
	return vector3;
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