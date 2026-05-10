#include "Object.h"

Object::Object(ObjMesh* _mesh, Texture2D* _texture, float x, float y, float z) : SceneObject(mesh, _texture, x, y, z)
{
	objMesh = _mesh;
	texture = _texture;

	collider = new SphereCollider(1.0f, position);

	position.x = x;
	position.y = y;
	position.z = z;

	rotation = 0;

	name = "Pawn";
}

Object::~Object()
{

}

void Object::Draw()
{
	if (objMesh->vertices != nullptr && objMesh->indices != nullptr)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(PackedVertex), &objMesh->vertices[0].texCoord);

		//enabling new state
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		//set arrays that are being used to draw
		glVertexPointer(3, GL_FLOAT, sizeof(PackedVertex), &objMesh->vertices[0].vertex);
		glNormalPointer(GL_FLOAT, sizeof(PackedVertex), &objMesh->vertices[0].normal);

		DefineMaterial();

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, rotationAxis.x, rotationAxis.y, rotationAxis.z);
		glScalef(scale.x, scale.y, scale.z);
		glDrawElements(GL_TRIANGLES, objMesh->indexCount, GL_UNSIGNED_INT, objMesh->indices);
		glPopMatrix();

		//disabling state
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		//disabling textures
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
}

AABBCollider Object::DefineBounds()
{
	vector<Vertex> tempVertex;

	for (int i = 0; i < objMesh->vertexCount; i++)
	{
		Vertex v = objMesh->vertices[i].vertex;
		RotateVertex(v);
		ScaleVertex(v);
		TranslateVertex(v);
		tempVertex.push_back(v);
	}

	return AABBCollider(tempVertex, position);
}

void Object::OnClick()
{
	position.z -= clickMovement;
	cout << "pawn clicked";
}
