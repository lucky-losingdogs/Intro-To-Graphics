#include "SceneObject.h"

SceneObject::SceneObject(Mesh* _mesh, Texture2D* _texture, float x, float y, float z)
{
	mesh = _mesh;
	texture = _texture;

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
	if (mesh->vertices != nullptr && mesh->colours != nullptr && mesh->indices != nullptr)
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

		/*if (mesh->texCoords == nullptr)
		{
			cout << ("Cube has NO texCoords\n");
		}*/
		
		//enabling new state
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		//set arrays that are being used to draw
		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
		glColorPointer(3, GL_FLOAT, 0, mesh->colours);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, 1, 0, 0);
		glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_SHORT, mesh->indices);
		glPopMatrix();

		//disabling state
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		//disabling textures
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
}

void SceneObject::Update()
{
	
}