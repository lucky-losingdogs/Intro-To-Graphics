#include "Texture2D.h"

Texture2D::Texture2D()
{
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

	BindTextureID(width, height, tempTextureData);
	return true;
}

//loads 24-bit bmp texture files
bool Texture2D::LoadBMP(char* path)
{
	char* tempTextureData;
	ifstream inFile;
	inFile.open(path, ios::binary);

	//error if cant open file
	if (!inFile.good())
	{
		cerr << "Can't open bitmap texture file " << path << endl;
		return false;
	}

	//read BITMAPFILEHEADER for file format
	inFile.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(BITMAPFILEHEADER));
	//check if it was read as the correct format
	if (bmFileHeader.bfType != 0x4D42)
	{
		cerr << "Not a valid bitmap" << std::endl;
		return false;
	}
	//read BITMAPINFOHEADER for image info (size, bits per pixel, etc)
	inFile.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(BITMAPINFOHEADER));
	//if the size of the img isn't set properly, set it manually
	if (bmInfoHeader.biSizeImage == 0)
		bmInfoHeader.biSizeImage = (bmInfoHeader.biHeight * bmInfoHeader.biWidth) * 3;

	tempTextureData = new char[bmInfoHeader.biSizeImage];

	//move to where the pixel data is
	inFile.seekg(bmFileHeader.bfOffBits, std::ios::beg);

	//read pixel data
	inFile.read(tempTextureData, bmInfoHeader.biSizeImage);

	//swap bitmap BGR format to RGB format
	for (int i = 0; i + 2 < bmInfoHeader.biSizeImage; i += 3)
	{
		swap(tempTextureData[i], tempTextureData[i + 2]);
	}

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	inFile.close();
	cout << path << " loaded." << endl;

	BindTextureID(width, height, tempTextureData);

	return true;
}

void Texture2D::BindTextureID(int width, int height, char* tempTextureData)
{
	//generate texture id
	glGenTextures(1, &ID);

	//bind texture to the id
	glBindTexture(GL_TEXTURE_2D, ID);

	//specify details of the texture img
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	//clear data we don't need anymore
	delete[] tempTextureData;
}