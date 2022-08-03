#include "../Headers/FsShader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace FausEngine;

std::string ReadFile(const char*);

char* vertexShader = "#version 330 core \n\ layout (location = 0) in vec3 position;layout (location = 1) in vec3 normal;layout (location = 2) in vec2 texture;	uniform mat4 model;	uniform mat4 view;uniform mat4 projection;	out vec3 FragPos;	out vec3 Normal; out vec2 TexCoord; void main(){ gl_Position = projection * view *  model * vec4(position, 1.0f); Normal = mat3(transpose(inverse(model))) * normal;TexCoord = texture;FragPos = vec3(model * vec4(position, 1.0f));	FragPos = vec3(model * vec4(position, 1.0f));		} ";

FsShader::FsShader()
{
	ShaderID = 0;
	
}


FsShader::~FsShader()
{
	glDeleteProgram(ShaderID);
}


bool FsShader::Load(const char* vertexPath,  const char* fragmentPath)
{
	//lectura de codigo glsl
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	//std::string vertexString = ReadFile(vertexPath);
	//const GLchar* vertexShaderSource = vertexString.c_str();
	
	//Compilar vertex shader
	glShaderSource(vertShader, 1, &vertexShader, NULL);
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

	//lectura de codigo glsl
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentString = ReadFile(fragmentPath);
	const GLchar* fragmentShaderSource = fragmentString.c_str();

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

void FsShader::Compile(int pointCount, int spotCount)
{
	uVariablesLocation[uTypeVariables::uModel] = glGetUniformLocation(ShaderID, "model");
	uVariablesLocation[uTypeVariables::uView] = glGetUniformLocation(ShaderID, "view");
	uVariablesLocation[uTypeVariables::uProjection] = glGetUniformLocation(ShaderID, "projection");
	uVariablesLocation[uTypeVariables::uEyePos] = glGetUniformLocation(ShaderID, "uEyePos");

	uVariablesLocation[uTypeVariables::uAmbient]= glGetUniformLocation(ShaderID, "material.ambient");
	uVariablesLocation[uTypeVariables::uSpecular] = glGetUniformLocation(ShaderID, "material.specular");
	uVariablesLocation[uTypeVariables::uShininess] = glGetUniformLocation(ShaderID, "material.shininess");
	uVariablesLocation[uTypeVariables::uTexture] = glGetUniformLocation(ShaderID, "material.texture");
	uVariablesLocation[uTypeVariables::uColor] = glGetUniformLocation(ShaderID, "color");
	uVariablesLocation[uTypeVariables::uLit] = glGetUniformLocation(ShaderID, "lit");

	//directional light
	uVariablesLocation[uTypeVariables::uDir_direction] = glGetUniformLocation(ShaderID, "directionalLight.direction");
	uVariablesLocation[uTypeVariables::uDir_ambient] = glGetUniformLocation(ShaderID, "directionalLight.base.ambient");
	uVariablesLocation[uTypeVariables::uDir_diffuse] = glGetUniformLocation(ShaderID, "directionalLight.base.diffuse");
	uVariablesLocation[uTypeVariables::uDir_specular] = glGetUniformLocation(ShaderID, "directionalLight.base.specular");

	//Point lights
	std::map<uTypeVariables, unsigned int> tempMap;
	for (int i = 0; i< pointCount; i++)
	{	
		tempMap[uTypeVariables::uPoint_ambient] = glGetUniformLocation(ShaderID, ("pointLights[" + std::to_string(i) + "].base.ambient").c_str());
		tempMap[uTypeVariables::uPoint_diffuse] = glGetUniformLocation(ShaderID, ("pointLights[" + std::to_string(i) + "].base.diffuse").c_str());
		tempMap[uTypeVariables::uPoint_specular] = glGetUniformLocation(ShaderID, ("pointLights[" + std::to_string(i) + "].base.specular").c_str());
		tempMap[uTypeVariables::uPoint_position] = glGetUniformLocation(ShaderID, ("pointLights[" + std::to_string(i) + "].position").c_str());
		tempMap[uTypeVariables::uPoint_const] = glGetUniformLocation(ShaderID, ("pointLights[" + std::to_string(i) + "].constant").c_str());
		tempMap[uTypeVariables::uPoint_lin] = glGetUniformLocation(ShaderID, ("pointLights[" + std::to_string(i) + "].linear").c_str());
		tempMap[uTypeVariables::uPoint_exp] = glGetUniformLocation(ShaderID, ("pointLights[" + std::to_string(i) + "].exponent").c_str());

		uPointlights.push_back(tempMap);
		tempMap.clear();
	}

	//Spot lights
	for (int i = 0; i < spotCount; i++)
	{
		tempMap[uTypeVariables::uPoint_ambient] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].base.ambient").c_str());
		tempMap[uTypeVariables::uPoint_diffuse] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].base.diffuse").c_str());
		tempMap[uTypeVariables::uPoint_specular] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].base.specular").c_str());
		tempMap[uTypeVariables::uPoint_position] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].position").c_str());
		tempMap[uTypeVariables::uSpot_Dir] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].direction").c_str());
		tempMap[uTypeVariables::uPoint_const] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].constant").c_str());
		tempMap[uTypeVariables::uPoint_lin] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].linear").c_str());
		tempMap[uTypeVariables::uPoint_exp] = glGetUniformLocation(ShaderID, ("spotLights[" + std::to_string(i) + "].exponent").c_str());

		uSpotLights.push_back(tempMap);
		tempMap.clear();
	}
}



unsigned int FsShader::GetUVariableLocation(uTypeVariables var) {
	return uVariablesLocation[var];
}

unsigned int FsShader::GetUPointsLocation(uTypeVariables var, int index) {

	return uPointlights[index][var];
}

unsigned int FsShader::GetUSpotLocation(uTypeVariables var, int index) {

	return uSpotLights[index][var];
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



void FsShader::Use()
{
	glUseProgram(ShaderID);
}

unsigned int FsShader::GetShaderId() const
{
	return ShaderID;
}

