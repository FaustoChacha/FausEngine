#include"../Headers/FsMaterial.h"
#include"../Headers/FsGame.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/stb_image.h"

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp> 

#include <sstream>

//#include<filesystem>

using namespace FausEngine;
//namespace fs = std::filesystem;

FsMaterial::FsMaterial()
{
	ambient = { 0.5f,0.5f ,0.5f };
	specular = { 0.1f, 0.1f, 0.1f };
	color = { 1.0f, 1.0f, 1.0f };
	shineness = 1;
	bind_TexToColor = false;
	textureID = 0;
	lit = false;
	logger.CreateLogger("FsMaterial","log-FsMaterial");
}


void FsMaterial::Load(FsVector3 ambient, FsVector3 specular, FsVector3 color, float shineness, std::string path, bool bind)
{
	this->ambient = ambient;
	this->specular = specular;
	this->color = color;
	this->shineness = shineness;
	this->bind_TexToColor = bind;
	this->textureID = 0;
	logger.CreateLogger("FsMaterial", "log-FsMaterial");

	//Leer y cargar textura

	int width, height, bitDepth;
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;

	unsigned char* texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
	if (!texData)
	{
		logger.SetName("Material " + ss.str());
		logger.SetMessage("Texture material falied to find: " + path, 1);
		//this->type = TypeMaterial::Unlit;
		this->color = { 0.75f,0.1f,0.95f };
		//return false;
	}

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (texData) {
		GLint formato{};
		if (bitDepth == 1)formato = GL_RED;
		if (bitDepth == 3)formato = GL_RGB; //JPG
		if (bitDepth == 4)formato = GL_RGBA; //PNG

		glTexImage2D(GL_TEXTURE_2D, 0, formato, width, height, 0, formato, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		logger.SetName("Material " + ss.str());
		logger.SetMessage("Number channels not found." + path, 1);
		//this->type = TypeMaterial::Unlit;
		this->color = { 0.75f,0.1f,0.95f };
		//return false;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);

	logger.SetName("Material " + ss.str());
	logger.SetMessage("Loaded material: " + path, 0);

	//return true;
	lit = true;
}

void FsMaterial::Load(FsVector3 c) {
	color = c;
	lit = false;
}

void FsMaterial::SetAmbient(FsVector3 amb) {
	ambient = amb;
}
void FsMaterial::SetSpecular(FsVector3 v) {
	specular= v;
}
void FsMaterial::SetColor(FsVector3 v) {
	color = v;
}
void FsMaterial::SetShine(float v) {
	shineness = v;
}
void FsMaterial::SetBind(bool v) {
	bind_TexToColor= v;
}

FsVector3 FsMaterial::GetAmbient() {
	return ambient;
}
FsVector3 FsMaterial::GetSpecular() {
	return specular;
}
FsVector3 FsMaterial::GetColor() {
	return color;
}
float FsMaterial::GetShine() {
	return shineness;
}
bool FsMaterial::GetBind() {
	return bind_TexToColor;
}
bool FsMaterial::GetLit() {
	return lit;

}
unsigned int FsMaterial::GetTexture() {
	return textureID;
}

//bool FsMaterial::LoadTexture(std::string path)
//{
//	int width, height, bitDepth;
//	const void* address = static_cast<const void*>(this);
//	std::stringstream ss;
//	ss << address;
//
//	unsigned char* texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
//	if (!texData)
//	{
//		logger.SetName("Material " + ss.str());
//		logger.SetMessage("Texture material falied to find: " + path, 1);
//		//this->type = TypeMaterial::Unlit;
//		this->color = { 0.75f,0.1f,0.95f };
//		return false;
//	}
//
//	stbi_set_flip_vertically_on_load(true);
//
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	if (texData) {
//		GLint formato{};
//		if (bitDepth == 1)formato = GL_RED;
//		if (bitDepth == 3)formato = GL_RGB; //JPG
//		if (bitDepth == 4)formato = GL_RGBA; //PNG
//
//		glTexImage2D(GL_TEXTURE_2D, 0, formato, width, height, 0, formato, GL_UNSIGNED_BYTE, texData);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else {
//		logger.SetName("Material " + ss.str());
//		logger.SetMessage("Number channels not found." + path, 1);
//		//this->type = TypeMaterial::Unlit;
//		this->color = { 0.75f,0.1f,0.95f };
//		return false;
//	}
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//	stbi_image_free(texData);
//
//	logger.SetName("Material " + ss.str());
//	logger.SetMessage("Loaded material: " + path, 0);
//
//	return true;
//}

FsMaterial::~FsMaterial()
{
	glDeleteTextures(1, &textureID);
}