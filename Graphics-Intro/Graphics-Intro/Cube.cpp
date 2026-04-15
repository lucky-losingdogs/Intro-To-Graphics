#include "Cube.h"


//cube constructor
Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture, x, y, z)
{
	
}

//cube destructor
Cube::~Cube()
{

}

void Cube::Update()
{
	rotation += 0.5f;
}