#ifndef FSWINDOW
#define FSWINDOW

#include "FsExport.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

namespace FausEngine {

	class FAUSENGINE_API  Window
	{
	public:
		Window();
		bool createWindow(GLint windowWidth, GLint windowHeight, std::string, bool fs);
		GLFWwindow* getWindowReference();
		//std::shared_ptr<GLFWwindow> getWindowReference();
		bool* getKeys();

		GLfloat getXMouseOffset();
		GLfloat getYMouseOffset();
		~Window();

	private:
		
	};
}

#endif // !FSWINDOW