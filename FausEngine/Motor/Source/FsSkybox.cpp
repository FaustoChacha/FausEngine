#include"../Headers/FsSkybox.h"
#include"../Headers/FsGame.h"
#include <GL\glew.h>
//#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/stb_image.h"
#include<iostream>
#include <sstream>

using namespace FausEngine;

FsSkybox::FsSkybox()
{
	textureID = 0;
    on = true;
    colour = {1,1,1};
    logger.CreateLogger("FsLogger","log-FsSkybox");
}

void FsSkybox::Load(std::vector <std::string> caras)
{
	pathFaces = caras;
    logger.CreateLogger("FsLogger", "log-FsSkybox");

    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;

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
            logger.SetName("Skybox: " + ss.str());
            logger.SetMessage("Skybox failed, path: "+ pathFaces[i], 1);
            //std::cout << "Skybox failed, path:: " << pathFaces[i] << std::endl;
            stbi_image_free(data);
            return;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    FsGame::GetReference()->SetSkybox(*this);

    logger.SetName("Skybox: " + ss.str());
    logger.SetMessage("Loaded skybox. ", 0);
}

unsigned int FsSkybox::GetTextureID() {
    return textureID;
}


FsSkybox::~FsSkybox()
{
    glDeleteTextures(1, &textureID);
}