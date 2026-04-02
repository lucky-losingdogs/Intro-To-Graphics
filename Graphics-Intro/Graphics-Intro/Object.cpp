#include "Object.h"

Vertex* Object::indexedVertices = nullptr;
Colour* Object::indexedColours = nullptr;
GLushort* Object::indices = nullptr;

int Object::numVertices = 0;
int Object::numFaces = 0;
int Object::numColours = 0;
int Object::numIndices = 0;

Object::Object(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	rotation = 0;
}

Object::~Object()
{

}

bool Object::Load(char* path)
{
	ifstream inFile(path);
	if (!inFile.good())
	{
		cerr << "Can't open obj file " << path << endl;
		return false;
	}

	vector<Vertex> positions;
	vector<Vertex> normals;
	vector<GLushort> tempIndices;

	string line = "";
	while (getline(inFile, line))
	{
		//skip empty lines
		if (line.empty())
			continue;

		istringstream ss(line);
		string token;
		ss >> token;

		//if the line starts with v/vn/f
		//meaning vertices, normal or face
		if (token == "v")
		{
			float x, y, z;
			ss >> x >> y >> z;
			positions.push_back(Vertex{ x, y, z });
		}
		else if (token == "vn")
		{
			float nx, ny, nz;
			ss >> nx >> ny >> nz;
			normals.push_back(Vertex{ nx, ny, nz });
		}
		else if (token == "f")
		{
			//temp string vector for the face tokens
			vector<string> faceTokens;
			string faceVertex;

			while (ss >> faceVertex)
				faceTokens.push_back(faceVertex);

			//invalid face
			if (faceTokens.size() < 3)
				continue;

			//convert tokens into vertex indices
			vector<int> faceIndices;
			for (string& faceToken : faceTokens)
			{
				istringstream fss(faceToken);
				string vIndexStr;

				//get just the vertex index by reading until it hits /
				getline(fss, vIndexStr, '/');
				//convert from 1-based obj
				int vIndex = stoi(vIndexStr) - 1;

				faceIndices.push_back(vIndex);
			}

			//fan triangluation
			//take first index and pair with the next 2
			for (int i = 1; i < faceIndices.size() - 1; i++)
			{
				tempIndices.push_back(faceIndices[0]);
				tempIndices.push_back(faceIndices[i]);
				tempIndices.push_back(faceIndices[i + 1]);
			}
		}
	}

	//populate indexedVertices array with the positions vector
	numVertices = positions.size();
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		indexedVertices[i] = positions[i];
	}

	//populate indices array with the triangulated indices vector
	numIndices = tempIndices.size();
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		indices[i] = tempIndices[i];
	}

	//set the colour to white
	indexedColours = new Colour[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		indexedColours[i] = { 1.0f, 1.0f, 1.0f };
	}

	inFile.close();
	return true;
}

void Object::Draw()
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

void Object::Update()
{

}

void ParseFaceToken()
{

}