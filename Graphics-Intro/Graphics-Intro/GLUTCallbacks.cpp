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
		renderer->Update();

		glutTimerFunc(preferredRefresh, GLUTCallbacks::Timer, preferredRefresh);
	}
}