#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene
	DrawTriangle();
	DrawPentagon();
	glFlush(); //flushes the scene drawn to the graphics card
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