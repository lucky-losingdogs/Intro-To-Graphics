#include "Cube.h"
#include <sstream>

Vertex* Cube::indexedVertices = nullptr;
Colour* Cube::indexedColours = nullptr;
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;

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

//populate the cube vertices, colour and indices arrays from a txt file
//return true if successfully loaded, return false if not
bool Cube::Load(char* path)
{
	ifstream inFile(path);
	if (!inFile.good())
	{
		cerr << "Can't open text file " << path << endl;
		return false;
	}

	//read first line for num of vertices
	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	//populate vertices array from cube.txt
	for (int i = 0; i < numVertices; i++)
	{
		float x, y, z;
		inFile >> x >> y >> z;
		indexedVertices[i] = { x, y, z };
	}

	//populate colours array
	inFile >> numColours;
	indexedColours = new Colour[numColours];
	for (int i = 0; i < numColours; i++)
	{
		float r, g, b;
		inFile >> r >> g >> b;
		indexedColours[i] = { r, g, b };
	}

	//populate indices array
	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		GLushort ind = 0;
		inFile >> ind;
		indices[i] = ind;
	}

	inFile.close();
	return true;
}

void Cube::Draw()
{
	if (indexedVertices != nullptr && indexedColours != nullptr && indices != nullptr)
	{
		//enabling new state
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		//set arrays that are being used to draw
		glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
		glColorPointer(3, GL_FLOAT, 0, indexedColours);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, 1, 0, 0);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();

		//disabling state
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Cube::Update()
{
	rotation += 0.5f;
}