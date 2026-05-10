#include "ObjLoader.h"

using namespace std;

namespace ObjLoader
{
	//populate the packed vertices (vertex, normal texture) array with the vector
	void LoadVertices(vector<PackedVertex>& packedVertices, ObjMesh& mesh)
	{
		mesh.vertexCount = packedVertices.size();

		if (mesh.vertexCount > 0)
		{
			mesh.vertices = new PackedVertex[mesh.vertexCount];

			for (int i = 0; i < mesh.vertexCount; i++)
			{
				mesh.vertices[i] = packedVertices[i];
			}
		}
	}

	//populate indices from vector
	void LoadIndices(vector<GLuint>& indices, ObjMesh& mesh)
	{
		mesh.indexCount = indices.size();

		if (mesh.indexCount > 0)
		{
			mesh.indices = new GLuint[mesh.indexCount];

			for (int i = 0; i < mesh.indexCount; i++)
			{
				mesh.indices[i] = indices[i];
			}
		}
	}

	ObjMesh* Load(char* path)
	{
		ObjMesh* mesh = new ObjMesh();

		ifstream inFile(path);
		if (!inFile.good())
		{
			cerr << "Can't open obj file " << path << endl;
			return nullptr;
		}

		//temp storage
		vector<Vertex> vertices;
		vector<Normal> normals;
		vector<GLuint> tempIndices;
		vector<TexCoord> texCoord;
		vector<PackedVertex> packedVertices;

		string line = "";
		while (getline(inFile, line))
		{
			//skip empty lines
			if (line.empty())
				continue;

			//split te lines into tokens to check
			//which part of the obj is being read
			istringstream ss(line);
			string token;
			ss >> token;

			//check the token at the start of the line
			//parse vertices
			if (token == "v")
			{
				float x, y, z;
				ss >> x >> y >> z;
				//store in vector
				vertices.push_back(Vertex{ x, y, z });
			}
			//parse normals
			else if (token == "vn")
			{
				float nx, ny, nz;
				ss >> nx >> ny >> nz;
				normals.push_back(Normal{ nx, ny, nz });
			}
			//parse texture coordinates
			else if (token == "vt")
			{
				float u, v;
				ss >> u >> v;
				texCoord.push_back(TexCoord{ u, v });
			}
			//parse faces
			else if (token == "f")
			{
				//temp string vector for the face tokens
				vector<string> faceTokens;
				string faceVertex;

				//read face tokens
				while (ss >> faceVertex)
					faceTokens.push_back(faceVertex);

				//convert polygons into triangles
				for (size_t i = 1; i + 1 < faceTokens.size(); i++)
				{
					string triangle[3] = { faceTokens[0], faceTokens[i], faceTokens[i + 1] };

					//parse each face vertex in the triangle
					for (string& faceToken : triangle)
					{
						istringstream fss(faceToken);
						string vStr, vtStr, vnStr;

						//face token is split into vertex, tex coord and normal
						getline(fss, vStr, '/'); //read until 1st /
						getline(fss, vtStr, '/'); //get after 1st / and before 2nd /
						getline(fss, vnStr, '/'); // get after 2nd /
						//[!] Warning: can only parse obj with coords separated with 1 '/'

						//convert from 1-based obj to 0-based
						//also convert from string to int
						int vIndex = stoi(vStr) - 1;

						//check texcoords and normals aren't missing
						int vtIndex = -1;
						if (!vtStr.empty())
							vtIndex = stoi(vtStr) - 1;

						int vnIndex = -1;
						if (!vnStr.empty())
							vnIndex = stoi(vnStr) - 1;

						//combines vertex, tex and normal into 1 vertex struct
						PackedVertex packedVertex;
						packedVertex.vertex = vertices[vIndex];

						//set default tex coord in case of absence]
						packedVertex.texCoord = { 0.0f, 0.0f };
						//if present, set it in packVertex
						if (vtIndex >= 0)
							packedVertex.texCoord = texCoord[vtIndex];

						packedVertex.normal = { 0.0f, 0.0f , 1.0f };
						if (vnIndex >= 0)
							packedVertex.normal = normals[vnIndex];

						//store assembled packed vertex in vector
						packedVertices.push_back(packedVertex);
						//store index pointing to the newly added vertex
						tempIndices.push_back(packedVertices.size() - 1);
					}
				}
			}
		}

		//load vectors into mesh
		LoadVertices(packedVertices, *mesh);
		LoadIndices(tempIndices, *mesh);

		return mesh;
	}
}