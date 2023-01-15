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
	type = TypeMaterial::Lit;
	bind_TexToColor = false;
	textureID = 0;
	//shader = &FausEngine::FsGame::GetInstance()->GetShader(0);
	//shader = std::make_shared<FsShader>(FausEngine::FsGame::GetInstance()->GetShader(0));
	logger.CreateLogger("FsMaterial","log-FsMaterial");
}


FsMaterial::FsMaterial(FsVector3 ambient, FsVector3 specular, FsVector3 color, float shineness, TypeMaterial type, bool bind)
{
	this->ambient = ambient;
	this->specular = specular;
	this->color = color;
	this->shineness = shineness;
	this->type = type;
	this->bind_TexToColor = bind;
	this->textureID = 0;
	logger.CreateLogger("FsMaterial", "log-FsMaterial");
	//shader = std::make_shared<FsShader>(FausEngine::FsGame::GetInstance()->GetShader(0));
}

unsigned int FsMaterial::GetTexture() {
	return textureID;
}

bool FsMaterial::LoadTexture(std::string path)
{
	int width, height, bitDepth;
	const void* address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;

	unsigned char* texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
	if (!texData)
	{
		logger.SetName("Material " + ss.str());
		logger.SetMessage("Texture material falied to find: " + path, 1);
		this->type = TypeMaterial::Unlit;
		this->color = { 0.75f,0.1f,0.95f };
		return false;
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
		this->type = TypeMaterial::Unlit;
		this->color = { 0.75f,0.1f,0.95f };
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);

	logger.SetName("Material " + ss.str());
	logger.SetMessage("Loaded material: " + path, 0);

	return true;
}

FsMaterial::~FsMaterial()
{
	glDeleteTextures(1, &textureID);
}