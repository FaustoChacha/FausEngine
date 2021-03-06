#include"../Headers/FsMaterial.h"
#include"../Headers/FsGame.h"

#include "../Headers/stb_image.h"

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp> 

using namespace FausEngine;

FsMaterial::FsMaterial()
{
	ambient = {0.7f,0.7f ,0.7f };
	specular = { 0.1f, 0.1f, 0.1f };
	color = {1.0f, 1.0f, 1.0f };
	shineness = 1;
	type = TypeMaterial::Lit;
	bind_TexToColor = false;
	textureID = 0;
	shader = FausEngine::FsGame::GetSelfReference()->GetShader();
}

FsShader* FsMaterial::GetShader() {
	return shader;
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
}

void LoadtextureAux(unsigned int& textureID, std::string  path) {
	int width, height, bitDepth;

	unsigned char* texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
	if (!texData)
	{
		std::cout << "Failed to find: %s" << path << std::endl;
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
		std::cout << "Number channels not found. " << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);

}

bool FsMaterial::LoadTexture(std::string path)
{
	int width, height, bitDepth;

	unsigned char* texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
	if (!texData)
	{
		std::cout << "Failed to find: %s" << path << std::endl;
		LoadtextureAux(textureID, FausEngine::FsGame::GetSelfReference()->GetPathEngine() + "/Shaders/TextureAux.png");
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
		std::cout << "Number channels not found. " << std::endl;
		LoadtextureAux(textureID, FausEngine::FsGame::GetSelfReference()->GetPathEngine() + "/Shaders/TextureAux.png");
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);

	return true;
}

FsMaterial::~FsMaterial()
{
	//texture
	glDeleteTextures(1, &textureID);
	textureID = 0;
}