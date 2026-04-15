#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, float x, float y, float z)
{
	_mesh = mesh;

	position.x = x;
	position.y = y;
	position.z = z;

	rotation = 0;
}

SceneObject::~SceneObject()
{

}

void SceneObject::Draw()
{
	if (_mesh->vertices != nullptr && _mesh->colours != nullptr && _mesh->indices != nullptr)
	{
		//enabling new state
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		//set arrays that are being used to draw
		glVertexPointer(3, GL_FLOAT, 0, _mesh->vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->colours);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, 1, 0, 0);
		glDrawElements(GL_TRIANGLES, _mesh->indexCount, GL_UNSIGNED_SHORT, _mesh->indices);
		glPopMatrix();

		//disabling state
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void SceneObject::Update()
{
	
}