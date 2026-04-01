#include "Cube.h"
#include <iostream>

Vertex Cube::indexedVertices[] =
{
	1, 1, 1,  -1, 1, 1, //v0-v1
	-1,-1, 1,  1,-1, 1, //v2-v3
	1, -1, -1,  1,1, -1, //v4-v5
	-1, 1,-1,  -1,-1,-1, //v6-v7
};

Colour Cube::indexedColors[] =
{
	1, 1, 1,  1, 1, 0, //v0-v1
	1,0, 0,   1,0, 1, //v2-v3
	0, 0, 1,   0, 1, 1, //v4-v5
	0, 1, 0,   0, 0, 0, //v6-v7
};

GLushort Cube::indices[] =
{
	0, 1, 2,  2, 3, 0, // front
	0, 3, 4,  4, 5, 0, // right
	0, 5, 6,  6, 1, 0, // top
	1, 6, 7,  7, 2, 1, // left
	7, 4, 3,  3, 2, 7, // bottom
	4, 7, 6,  6, 5, 4  // back
};

//cube constructor
Cube::Cube(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	rotation = 0;
}

//cube destructor
Cube::~Cube()
{

}

void Cube::Draw()
{
	//enabling new state
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//set arrays that are being used to draw
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation, 1, 0, 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	//disabling state
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Cube::Update()
{
	rotation += 0.5f;
}