#include "Text.h"

Text::Text(const char* text, Vector3 position, Colour colour)
{
	DrawString(text, &position, &colour);
}

Text::~Text()
{

}

void Text::UpdateText(const char* text, Vector3 position, Colour colour)
{
	DrawString(text, &position, &colour);
}

void Text::DrawString(const char* text, Vector3* position, Colour* colour)
{
	glPushMatrix();

	glTranslatef(position->x, position->y, position->z);
	//raster position is the position of the text on screen,
	//altered with transform to be in the correct position in the world
	glRasterPos2f(0.0f, 0.0f);
	//load the font and the text
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)text);

	glPopMatrix();
}