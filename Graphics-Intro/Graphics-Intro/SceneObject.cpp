#include "SceneObject.h"

SceneObject::SceneObject(Mesh* _mesh, Texture2D* _texture, float x, float y, float z)
{
	mesh = _mesh;
	texture = _texture;

	collider = new SphereCollider(1.0f, position);

	position.x = x;
	position.y = y;
	position.z = z;

	rotation = 0;

	name = "SceneObject";
}

SceneObject::~SceneObject()
{
	delete collider;
}

void SceneObject::Draw()
{
	if (mesh->vertices != nullptr && mesh->normals != nullptr && mesh->indices != nullptr)
	{
		bool hasTexture = (texture != nullptr) && (mesh->texCoords != nullptr);
		
		if (hasTexture)
		{
			//enable texturing for objects with textures
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture->GetID());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, mesh->texCoords);
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		
		//enabling new state
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		//set arrays that are being used to draw
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glNormalPointer(GL_FLOAT, 0, mesh->normals);

		DefineMaterial();

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(rotation, rotationAxis.x, rotationAxis.y, rotationAxis.z);
		glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_SHORT, mesh->indices);
		glPopMatrix();

		//disabling state
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		//disabling textures
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
}

void SceneObject::Update()
{
	collider->position = position;
}

//defines the material properties of the object and applies them to the current OpenGL state
void SceneObject::DefineMaterial()
{
	material = new Material();
	material->ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	material->diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	material->specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material->shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(material->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);
}

void SceneObject::UpdateTexture(Texture2D* newTex)
{
	texture = newTex;
}

void SceneObject::Scale(Vector3 newScale)
{
	scale = newScale;
}

void SceneObject::Rotate(float rotationScale, Vector3 axis)
{
	rotation = rotationScale;
	rotationAxis = axis;
}

void SceneObject::Translate(Vector3 newPosition)
{
	position = newPosition;
}

void SceneObject::CheckCollision(SceneObject *other)
{
	if (collider->Intersects(*other->collider))
	{
		cout << "colliding";
	}
}

AABBCollider SceneObject::DefineBounds()
{
	vector<Vertex> tempVertex;
	
	for (int i = 0; i < mesh->vertexCount; i++)
	{
		Vertex v = mesh->vertices[i];
		RotateVertex(v);
		ScaleVertex(v);
		TranslateVertex(v);
		tempVertex.push_back(v);
	}

	return AABBCollider(tempVertex, position);
}

void SceneObject::ScaleVertex(Vertex& vertex)
{
	vertex.x *= scale.x;
	vertex.y *= scale.y;
	vertex.z *= scale.z;
}

void SceneObject::TranslateVertex(Vertex& vertex)
{
	vertex.x += position.x;
	vertex.y += position.y;
	vertex.z += position.z;
}

void SceneObject::RotateVertex(Vertex& vertex)
{
	vertex = HandleRotateVertex(vertex, rotation, rotationAxis);
}

Vertex SceneObject::HandleRotateVertex(Vertex vertex, float angleDegrees, Vector3 axis)
{
	//convert degrees to radians
	float radians = angleDegrees * (3.14159265f / 180.0f);

	//normalize axis
	float length = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	axis.x /= length;
	axis.y /= length;
	axis.z /= length;

	float cosA = cos(radians);
	float sinA = sin(radians);

	Vertex result;

	//Rodrigues' rotation formula
	result.x =
		vertex.x * (cosA + axis.x * axis.x * (1 - cosA)) +
		vertex.y * (axis.x * axis.y * (1 - cosA) - axis.z * sinA) +
		vertex.z * (axis.x * axis.z * (1 - cosA) + axis.y * sinA);

	result.y =
		vertex.x * (axis.y * axis.x * (1 - cosA) + axis.z * sinA) +
		vertex.y * (cosA + axis.y * axis.y * (1 - cosA)) +
		vertex.z * (axis.y * axis.z * (1 - cosA) - axis.x * sinA);

	result.z =
		vertex.x * (axis.z * axis.x * (1 - cosA) - axis.y * sinA) +
		vertex.y * (axis.z * axis.y * (1 - cosA) + axis.x * sinA) +
		vertex.z * (cosA + axis.z * axis.z * (1 - cosA));

	return result;
}

void SceneObject::OnClick()
{
	
}

string SceneObject::GetName()
{
	return name;
}
