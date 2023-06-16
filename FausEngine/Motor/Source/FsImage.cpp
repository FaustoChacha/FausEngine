#include"../Headers/FsImage.h"
#include "../Headers/stb_image.h"
#include"../Headers/FsGame.h"


#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp> 

using namespace FausEngine;


FsImage::FsImage()
{
	shader = FausEngine::FsGame::GetReference()->GetShader(2);

	vbo = 0; ibo = 0; vao = 0;
	textureID = 0;
	transform = FsTransform();
	
	//logger.CreateLogger("FsImage","log-FsImage");
}

void FsImage::Load(std::string path)
{
	shader = FausEngine::FsGame::GetReference()->GetShader(2);
	
	int width, height, bitDepth;

	unsigned char* texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
	if (!texData)
	{
		/*logger.SetName(path);
		logger.SetMessage(, 1);*/
		FausEngine::FsGame::GetReference()->SetLog("Falied to find: " + path,1);
		return;
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
		//logger.SetName("Image " + std::to_string(textureID));
		//logger.SetMessage("Number channels not found." + path, 1);
		FausEngine::FsGame::GetReference()->SetLog("Number channels not found. " + path, 1);
		return;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);
	
	//malla
	GLfloat vertices[] = {
		-0.5f,  0.5f, 0.0f,	 0.0f, 1.0f,		// Sup izquierda
		 0.5f,  0.5f, 0.0f,	 1.0f, 1.0f,		// Sup derecha
		 0.5f, -0.5f, 0.0f,	 1.0f, 0.0f,		// Inferior derecha
		-0.5f, -0.5f, 0.0f,	 0.0f, 0.0f			// Ing Izquierda
	};

	GLuint indices[] = {
		0, 1, 2,  // 1 trian
		0, 2, 3   // 2 trian
	};

	glGenBuffers(1, &vbo);					
	glBindBuffer(GL_ARRAY_BUFFER, vbo);		
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	

	glGenVertexArrays(1, &vao);		
	glBindVertexArray(vao);					

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// Texture Coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Set up index buffer
	glGenBuffers(1, &ibo);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//transparencia
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//logger.SetName("Image " + std::to_string(textureID));
	//logger.SetMessage("Loaded image: " + path, 0);
	FausEngine::FsGame::GetReference()->SetLog("Loaded image: " + path, 0);

}

void FsImage::Render() {

	shader->Use();

	glm::mat4 mModel(1.0f);
	mModel = glm::translate(mModel, glm::vec3(transform.position.x, transform.position.y, transform.position.z));
	mModel = glm::rotate(mModel, glm::radians<float>(transform.rotation.x), glm::vec3(1, 0, 0));
	mModel = glm::rotate(mModel, glm::radians<float>(transform.rotation.y), glm::vec3(0, 1, 0));
	mModel = glm::rotate(mModel, glm::radians<float>(transform.rotation.z), glm::vec3(0, 0, 1));
	mModel = glm::scale(mModel, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));
	glUniformMatrix4fv(shader->GetUVariableLocation(uTypeVariables::uModel), 1, GL_FALSE, glm::value_ptr(mModel));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void FsImage::SetPosition(FsVector3 pos) {
	transform.position = pos;
}

void FsImage::SetRotation(FsVector3 v) {
	transform.rotation = v;
}

void FsImage::SetScale(FsVector3 v) {
	transform.scale = v;
}

FsVector3 FsImage::GetPosition() {
	return transform.position;
}
FsVector3 FsImage::GetRotation() {
	return transform.rotation;
}
FsVector3 FsImage::GetScale() {
	return transform.scale;
}

FsImage::~FsImage()
{
	glDeleteTextures(1,&textureID);
}