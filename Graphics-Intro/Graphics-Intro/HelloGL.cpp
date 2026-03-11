#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	rotationTri = 0.0f;
	rotationRect = 0.0f;
	rotationPent = 0.0f;
	
	GLUTCallbacks::Init(this);
	
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	RotateShape(rotationTri, -1.0f, Triangle);
	RotateShape(rotationRect, 1.0f, Rectangle);
	RotateShape(rotationPent, -1.0f, Pentagon);

	glFlush(); //flushes the scene drawn to the graphics card
}

void HelloGL::Update()
{
	rotationTri += 0.5f;
	if (rotationTri >= 360.0f)
		rotationTri = 0.0f;

	rotationRect += 0.2f;
	if (rotationRect >= 360.0f)
		rotationRect = 0.0f;

	rotationPent += 0.8f;
	if (rotationPent >= 360.0f)
		rotationPent = 0.0f;

	//marks the current window as needing to be redisplayed
	glutPostRedisplay();
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
		glEnd(); //defines the end of the draw
	}
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
		glEnd(); //defines the end of the draw
	}
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
		glEnd(); //defines the end of the draw
	}
}

void HelloGL::RotateShape(float rotation, float direction, Shape drawShape)
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, direction);

	switch (drawShape)
	{
	case Triangle:
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