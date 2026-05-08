#include "SkyBox.h"

SkyBox::SkyBox(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture, x, y, z)
{
	
}

Texture2D* SkyBox::MakeTexture(char* path)
{
	Texture2D* texture = new Texture2D();
	texture->LoadBMP(path);
	return texture;
}

//load each bmp file texture for each face of the skybox
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

    //front face
    glBindTexture(GL_TEXTURE_2D, skyboxTex[0]->GetID());
    glBegin(GL_QUADS);
    //set texture coordinate
    glTexCoord2f(0, 0); 
    //set vertex coordinate
    glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, -1);
    glEnd();

    //back face
    glBindTexture(GL_TEXTURE_2D, skyboxTex[1]->GetID());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, 1);
    glEnd();

    //left face
    glBindTexture(GL_TEXTURE_2D, skyboxTex[2]->GetID());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 1); 
    glVertex3f(-1, 1, 1);
    glEnd();

    //right face
    glBindTexture(GL_TEXTURE_2D, skyboxTex[3]->GetID());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, -1);
    glEnd();

    //top face
    glBindTexture(GL_TEXTURE_2D, skyboxTex[4]->GetID());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, 1);
    glEnd();

    //bottom face
    glBindTexture(GL_TEXTURE_2D, skyboxTex[5]->GetID());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -1);
    glEnd();

    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}