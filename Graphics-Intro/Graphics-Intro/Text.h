#pragma once
#include "Structures.h"

class Text
{
private:
	void DrawString(const char* text, Vector3* position, Colour* colour);

public:
	Text(const char* text, Vector3 position, Colour colour);
	~Text();

	void UpdateText(const char* text, Vector3 position, Colour colour);
};

