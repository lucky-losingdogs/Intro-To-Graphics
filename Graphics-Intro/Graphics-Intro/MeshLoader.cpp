#include "MeshLoader.h"

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	bool CheckIfTextured(ifstream& inFile);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		//read first line for num of vertices
		inFile >> mesh.vertexCount;

		if (mesh.vertexCount > 0)
		{
			mesh.vertices = new Vertex[mesh.vertexCount];

			//populate vertices array from file
			for (int i = 0; i < mesh.vertexCount; i++)
			{
				inFile >> mesh.vertices[i].x;
				inFile >> mesh.vertices[i].y;
				inFile >> mesh.vertices[i].z;
			}
		}
	}

	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.colourCount;

		if (mesh.colourCount > 0)
		{
			mesh.colours = new Colour[mesh.colourCount];

			//populate vertices array from file
			for (int i = 0; i < mesh.colourCount; i++)
			{
				inFile >> mesh.colours[i].r;
				inFile >> mesh.colours[i].g;
				inFile >> mesh.colours[i].b;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		if (CheckIfTextured(inFile))
			return;
		
		inFile >> mesh.texCoordCount;

		if (mesh.texCoordCount > 0)
		{
			mesh.texCoords = new TexCoord[mesh.texCoordCount];

			//populate vertices array from file
			for (int i = 0; i < mesh.texCoordCount; i++)
			{
				inFile >> mesh.texCoords[i].u;
				inFile >> mesh.texCoords[i].v;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.indexCount;

		if (mesh.indexCount > 0)
		{
			mesh.indices = new GLushort[mesh.indexCount];

			//populate vertices array from file
			for (int i = 0; i < mesh.indexCount; i++)
			{
				inFile >> mesh.indices[i];
			}
		}
	}

	//return true if successfully loaded, return false if not
	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadColours(inFile, *mesh);
		LoadIndices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);

		return mesh;
	}

	bool MeshLoader::CheckIfTextured(ifstream& inFile)
	{
		return inFile.eof();
	}
}