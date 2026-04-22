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
		glRotatef(rotation, 1, 0, 0);
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
	
}

//defines the material properties of the object and applies them to the current OpenGL state
void SceneObject::DefineMaterial()
{
	material = new Material();
	material->ambient.x = 0.8; material->ambient.y = 0.05; material->ambient.z = 0.05;
	material->ambient.w = 1.0;
	material->diffuse.x = 0.8; material->diffuse.y = 0.05; material->diffuse.z = 0.05;
	material->diffuse.w = 1.0;
	material->specular.x = 1.0; material->specular.y = 1.0; material->specular.z = 1.0;
	material->specular.w = 1.0;
	material->shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(material->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);
}