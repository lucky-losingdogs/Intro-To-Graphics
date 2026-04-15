#include "Cube.h"


//cube constructor
Cube::Cube(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, x, y, z)
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