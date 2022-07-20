#include "../Headers/Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

using namespace FausEngine;

std::string ReadFile(const char*);

Shader::Shader()
{
	ShaderID = 0;
}


Shader::~Shader()
{
	glDeleteProgram(ShaderID);
}


bool Shader::Load(const char* vertexPath, const char* fragmentPath)
{
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	//lectura de codigo glsl
	std::string vertexString = ReadFile(vertexPath);
	std::string fragmentString = ReadFile(fragmentPath);
	const GLchar* vertexShaderSource = vertexString.c_str();
	const GLchar* fragmentShaderSource = fragmentString.c_str();

	//Compilar vertex shader
	glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertShader);
	//errores
	GLint result = GL_FALSE;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		GLchar log[1024] = { 0 };
		glGetShaderInfoLog(vertShader, sizeof(log), NULL, log);
		std::cerr << "(Vertex) Error compilling: " << log << std::endl;
		return false;
	}

	//Compilar fragment shader
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);
	//errores
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		GLchar log[1024] = { 0 };
		glGetShaderInfoLog(fragShader, sizeof(log), NULL, log);
		std::cerr << "(Fragment) Error compilling: " << log << std::endl;
		return false;
	}

	//Enlazar programa
	ShaderID = glCreateProgram();
	glAttachShader(ShaderID, vertShader);
	glAttachShader(ShaderID, fragShader);
	glLinkProgram(ShaderID);
	//errores
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		GLchar log[1024] = { 0 };
		glGetShaderInfoLog(ShaderID, sizeof(log), NULL, log);
		std::cerr << "(ShaderID) Error compilling: " << log << std::endl;
		return false;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return true;
}

std::string ReadFile(const char* filePath)
{
	std::string content="";
	std::ifstream fileStream(filePath, std::ios::in);

	if (fileStream.is_open()) {
		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
	}
	else {
		std::cout << "Failed to read file. " << filePath << std::endl;
	}
	return content;
}



void Shader::Use()
{
	glUseProgram(ShaderID);
}

GLuint Shader::GetShaderId() const
{
	return ShaderID;
}

void Shader::SetUniform3f(const GLchar* name, const FsVector3& v)
{
	glUniform3f(glGetUniformLocation(ShaderID,name), v.x, v.y, v.z);
}

void Shader::SetUniformMatrix4fv(const GLchar* name, const glm::mat4& m)
{
	glUniformMatrix4fv(
		glGetUniformLocation(ShaderID,name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::SetUniform1f(const GLchar* name, const GLfloat f)
{
	glUniform1f(glGetUniformLocation(ShaderID, name), f);
}

void Shader::SetUniform1i(const GLchar* name, const GLint v)
{
	glUniform1i(glGetUniformLocation(ShaderID, name), v);
}
