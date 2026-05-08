#pragma once
class HelloGL;

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);
	void Display();
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void SpecialKeyboard(int key, int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseUpdate(int x, int y);
}