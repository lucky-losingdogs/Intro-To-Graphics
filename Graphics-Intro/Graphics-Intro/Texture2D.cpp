#include "Texture2D.h"

Texture2D::Texture2D()
{
	ID = 0;
	height = 0;
	width = 0;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}

//loads raw texture files
bool Texture2D::Load(char* path, int _width, int _height)
{
	char* tempTextureData;
	int fileSize;
	ifstream inFile;
	width = _width;
	height = _height;
	inFile.open(path, ios::binary);

	//error if cant open file
	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	//send from start to the end of the file
	inFile.seekg(0, ios::end);

	//current position in file - the end of the file = total file size
	fileSize = (int)inFile.tellg();

	//create array to store data
	tempTextureData = new char[fileSize];

	//seek back to the beginning of the file and read all the data
	inFile.seekg(0, ios::beg);
	inFile.read(tempTextureData, fileSize);

	inFile.close();
	cout << path << " loaded." << endl;

	//get the next texture id
	glGenTextures(1, &ID);

	//bind texture to the id
	glBindTexture(GL_TEXTURE_2D, ID);

	//specify details of the texture img
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	//clear data we don't need anymore
	delete[] tempTextureData;
	return true;
}