#include "../Headers/Window.h"

using namespace FausEngine;
GLint bufferWidth, bufferHeight;
float ultimoX, ultimoY;
GLfloat xMouseOffset;
GLfloat yMouseOffset;
GLint widthWindow, heightWindow;
bool mouseFirstMoved = true;
GLFWwindow* mainWindow;
std::string nombre;
bool keys[1024];

//------------------------prototipos--------------------------------------
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void keyCallback(GLFWwindow* window, int key, int code, int action, int mode);


//----------------------------------------------------------
Window::Window(){}

bool* Window::getKeys() { return keys; }

bool Window::createWindow(GLint windowWidth, GLint windowHeight, std::string tit, bool fullScreen)
{
	widthWindow = windowWidth;
	heightWindow = windowHeight;
	nombre = tit;

	for (int i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	
	xMouseOffset = 0.0f;
	yMouseOffset = 0.0f;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (fullScreen) {
		mainWindow = glfwCreateWindow(widthWindow, heightWindow, nombre.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else {
		mainWindow = glfwCreateWindow(widthWindow, heightWindow, nombre.c_str(), NULL, NULL);
	}
	
	if (!mainWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	//Callbacks
	glfwSetKeyCallback(mainWindow, keyCallback);
	glfwSetCursorPosCallback(mainWindow, mouseCallback);

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//inicializar glew 
	glewInit();
	//GLenum error = glewInit();
	//if (GLEW_OK != error)
	//{
	//	//printf("Error: %s", glewGetErrorString(error));
	//	//glfwDestroyWindow(mainWindow);
	//	//glfwTerminate();
	//	//return 1;
	//}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return true;
}

GLFWwindow* Window::getWindowReference() {
	return mainWindow;
}

//std::shared_ptr<GLFWwindow> Window::getWindowReference() {
//	return std::make_shared<GLFWwindow>(mainWindow);
//}

GLfloat Window::getXMouseOffset()
{
	GLfloat change = xMouseOffset;
	xMouseOffset = 0.0f;
	return change;
}

GLfloat Window::getYMouseOffset()
{
	GLfloat theChange = yMouseOffset;
	yMouseOffset = 0.0f;
	return theChange;
}

void keyCallback(GLFWwindow* window, int key, int code, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (mouseFirstMoved)
	{
		ultimoX = xPos;
		ultimoY = yPos;
		mouseFirstMoved = false;
	}

	xMouseOffset = xPos - ultimoX;
	yMouseOffset = ultimoY - yPos;

	ultimoX = xPos;
	ultimoY = yPos;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
