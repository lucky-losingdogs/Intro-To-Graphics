#include "Cat.h"

Cat::Cat(ObjMesh* _mesh, Texture2D* _texture, float x, float y, float z) : Object(_mesh,  _texture, x, y, z)
{
	name = "Cat";
}

Cat::~Cat()
{
}

void Cat::OnClick()
{
	int randNums[3];
	
	for (int i = 0; i < 3; i++)
	{
		//generate random number between 0 and 1
		int randomNum = rand() % 3;
		//generate if the number will be negative or positive
		// based on if the generated number is 0 or 1
		if (randomNum == 2)
			randomNum = -1;

		randNums[i] = randomNum;
	}

	rotationAxis = Vector3(randNums[0], randNums[1], randNums[2]);
}

void Cat::Update()
{
	rotation += delta;
}