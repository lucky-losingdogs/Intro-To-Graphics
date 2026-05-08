#include "GLUTCallbacks.h"
#include "HelloGL.h"

//Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		//Initialise to a null pointer before we do anything
		HelloGL* renderer = nullptr;
	}	

	void Init(HelloGL* gl)
	{
		renderer = gl;
	}

	void Display()
	{
		if (renderer != nullptr)
		{
			renderer->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		renderer->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;

		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		renderer->Keyboard(key, x, y);
	}

	void SpecialKeyboard(int key, int x, int y)
	{
		renderer->SpecialKeyboard(key, x, y);
	}

	void MouseClick(int button, int state, int x, int y)
	{
		renderer->MouseClick(button, state, x, y);
	}

	void MouseUpdate(int x, int y)
	{
		renderer->MouseMove(x, y);
	}
}