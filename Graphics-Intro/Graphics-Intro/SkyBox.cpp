#include "SkyBox.h"

SkyBox::SkyBox(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture, x, y, z)
{
	size = 500;
}

Texture2D* SkyBox::MakeTexture(char* path)
{
	Texture2D* texture = new Texture2D();
	texture->LoadBMP(path);
	return texture;
}

void SkyBox::LoadSkybox()
{
	skyboxTex[0] = MakeTexture((char*)"Box_Front.bmp");
	skyboxTex[1] = MakeTexture((char*)"Box_Back.bmp");
	skyboxTex[2] = MakeTexture((char*)"Box_Left.bmp");
	skyboxTex[3] = MakeTexture((char*)"Box_Right.bmp");
	skyboxTex[4] = MakeTexture((char*)"Box_Top.bmp");
	skyboxTex[5] = MakeTexture((char*)"Box_Bottom.bmp");
}

void SkyBox::Draw()
{
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    glColor3f(1, 1, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
    glNormalPointer(GL_FLOAT, 0, mesh->normals);
    glTexCoordPointer(2, GL_FLOAT, 0, mesh->texCoords);

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    int indicesPerFace = 6;

    for (int i = 0; i < 6; i++)
    {
        glBindTexture(GL_TEXTURE_2D, skyboxTex[i]->GetID());

        glDrawElements(GL_TRIANGLES, indicesPerFace, GL_UNSIGNED_SHORT, mesh->indices + (i * indicesPerFace));
    }

    glPopMatrix();

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}