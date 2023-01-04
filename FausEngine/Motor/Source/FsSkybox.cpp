#include"../Headers/FsSkybox.h"
#include"../Headers/FsGame.h"
#include <GL\glew.h>
//#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/stb_image.h"
#include<iostream>

using namespace FausEngine;

FsSkybox::FsSkybox()
{
	textureID = 0;
    on = true;
    colour = {1,1,1};
}

FsSkybox::FsSkybox(std::vector <std::string> caras)
{
	pathFaces = caras;
}

void FsSkybox::Load() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;

    for (unsigned int i = 0; i < pathFaces.size(); i++)
    {
        unsigned char* data = stbi_load(pathFaces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Skybox failed, path:: " << pathFaces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    FsGame::GetInstance()->SetSkybox(*this);
}

unsigned int FsSkybox::GetTextureID() {
    return textureID;
}


FsSkybox::~FsSkybox()
{
    glDeleteTextures(1, &textureID);
}