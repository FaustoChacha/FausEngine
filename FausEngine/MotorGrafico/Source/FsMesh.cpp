#include "../Headers/FsMesh.h"
#include"../Headers/FsGame.h"

#include "../Headers/stb_image.h"

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp> 

#include <iostream>
#include <sstream>
#include <fstream>

using namespace FausEngine;

FsMesh::FsMesh()
{
	VBO = 0; VAO = 0; meshLoaded = false;

	meshTransform = FsTransform({ 0,0,0 }, { 0,0,0 }, {1,1,1});
	material = FsMaterial();
	
}

FsMesh::FsMesh(std::string _path)
{
	path = _path;
}

FsMesh::~FsMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}


void FsMesh::LoadMesh()
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;

	std::ifstream fileStream(path, std::ios::in);
		
	if (fileStream.is_open() && path.find(".obj"))
	{
		std::string linea = "";
		while (std::getline(fileStream, linea))
		{
			if (linea.substr(0, 2) == "v ")
			{
				glm::vec3 vertex;
				sscanf_s(linea.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				tempVertices.push_back(vertex);
			}
			else if (linea.substr(0, 2) == "vt")
			{
				glm::vec2 uv;
				sscanf_s(linea.c_str(), "vt %f %f", &uv.x, &uv.y);
				tempUVs.push_back(uv);
			}
			else if (linea.substr(0, 2) == "vn") {
				glm::vec3 normals;
				sscanf_s(linea.c_str(), "vn %f %f %f", &normals.x, &normals.y, &normals.z);
				tempNormals.push_back(normals);
			}
			else if (linea.substr(0, 2) == "f ")
			{
				int p1, p2, p3; //f 0/1/1
				int t1, t2, t3; 
				int n1, n2, n3;
				const char* face = linea.c_str();
				int match = sscanf_s(face, "f %i/%i/%i %i/%i/%i %i/%i/%i",
					&p1, &t1, &n1,
					&p2, &t2, &n2,
					&p3, &t3, &n3);
				if (match != 9) {
					std::cout << "File can't be read." << std::endl;
					//return false;
				}
					
				vertexIndices.push_back(p1);
				vertexIndices.push_back(p2);
				vertexIndices.push_back(p3);

				uvIndices.push_back(t1);
				uvIndices.push_back(t2);
				uvIndices.push_back(t3);

				normalIndices.push_back(n1);
				normalIndices.push_back(n2);
				normalIndices.push_back(n3);
			}
		}

		fileStream.close();

		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
			glm::vec2 uv = tempUVs[uvIndices[i] - 1];
			glm::vec3 normal = tempNormals[normalIndices[i] - 1];

			vertexElements.push_back(vertex.x);
			vertexElements.push_back(vertex.y);
			vertexElements.push_back(vertex.z);
			vertexElements.push_back(normal.x);
			vertexElements.push_back(normal.y);
			vertexElements.push_back(normal.z);
			vertexElements.push_back(uv.x);
			vertexElements.push_back(uv.y);

		}

		// setting con la tarjeta grafica
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexElements.size() * sizeof(float), &vertexElements[0], GL_STATIC_DRAW); //&mVertices[0] &mVertexData[0]

		// Vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Normales
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// UVs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		meshLoaded = true;
		//return meshLoaded;
	}
	else
	{
		std::cout << "Path not found. " << path << std::endl;
		meshLoaded = false;
		//return meshLoaded;
	}

	//meshLoaded = false;
	//return meshLoaded;
}

int FsMesh::algo()const { return a; }

void FsMesh::Render()
{
	auto sh = material.GetShader();

	if (!meshLoaded) return;

	//Mesh Trasnform 
	glm::mat4 mModel(1.0f);
	mModel = glm::translate(mModel, glm::vec3(meshTransform.position.x, meshTransform.position.y, meshTransform.position.z));
	mModel = glm::rotate(mModel, glm::radians<float>(meshTransform.rotation.x), glm::vec3(1, 0, 0));
	mModel = glm::rotate(mModel, glm::radians<float>(meshTransform.rotation.y), glm::vec3(0, 1, 0));
	mModel = glm::rotate(mModel, glm::radians<float>(meshTransform.rotation.z), glm::vec3(0, 0, 1));
	mModel = glm::scale(mModel, glm::vec3(meshTransform.scale.x, meshTransform.scale.y, meshTransform.scale.z));
	glUniformMatrix4fv( sh->GetUVariableLocation(uTypeVariables::uModel), 1, GL_FALSE, glm::value_ptr(mModel));

	//Material setting
	glUniform3f(sh->GetUVariableLocation(uTypeVariables::uAmbient),
		material.ambient.x, material.ambient.y, material.ambient.z);
	glUniform3f(sh->GetUVariableLocation(uTypeVariables::uSpecular),
		material.specular.x, material.specular.y, material.specular.z);
	glUniform3f(sh->GetUVariableLocation(uTypeVariables::uColor),
		material.color.x, material.color.y, material.color.z);
	glUniform1f(sh->GetUVariableLocation(uTypeVariables::uShininess), material.shineness);
	glUniform1i(sh->GetUVariableLocation(uTypeVariables::uTexture), 0);
	glUniform1i(sh->GetUVariableLocation(uTypeVariables::uLit), true ? material.type == TypeMaterial::Lit : false);

	//Use Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.textureID);

	//Mesh
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0,vertexElements.size()/8);
	glBindVertexArray(0);
}

