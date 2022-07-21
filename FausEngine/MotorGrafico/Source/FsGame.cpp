#include"../Headers/FsGame.h"
#include "../Headers/Window.h"
#include "../Headers/FsCamera.h"

#include"../Headers/Mesh.h"

#include <glm\gtc\type_ptr.hpp>
#include<string>
#include<iostream>
#include<memory>

#include<fstream>
#include<sys/stat.h>
#include <algorithm>
#include<cmath>

using namespace FausEngine;

static FsGame* game;

Window mainWindow;
GLsizei width, height;
FsCamera* camera;
//std::shared_ptr<FsCamera> camera{ new FsCamera(FsVector3(0.0f, 5.0f, 0.0f), FsVector3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f) };


GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

std::string pathFausEngine;

struct stat buffer;




//Prototipos
void ValidarPathEngine();
void ValidarVentana();
void ValidarCamara();
void ValidarLuzDireccional();
glm::mat4 CalcularMatrizVista();

FsGame::FsGame() {
    
    if (!game) game = this;
}

FsGame::~FsGame() {
    //delete[] camera;

}

void ValidarPathEngine() {

    if (pathFausEngine[0] == '\0') {
        std::cout << "Specify the path of the FausEngine folder, with SetPathEngine() method" << std::endl;
        exit(3);
    }
    else {
        if (stat(pathFausEngine.c_str(), &buffer) != 0) { //verifico si existe la ruta
            std::cout << "The path: " << "'" << pathFausEngine << "'" << " not exist" << std::endl;
            exit(3);
        }
    }
}

void ValidarCamara() {
    if (!camera) {
        camera = new FsCamera(FsVector3(0.0f, 5.0f, 0.0f), FsVector3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f);
    }
}

void ValidarVentana() {
    if (!mainWindow.getWindowReference()) {
        std::cout << "No exits a window, call Construct() function." << std::endl;
        exit(3);
    }
}



void CrearShaders(std::string pathEngine) {
    //Shader con iluminacion 
    //const int sizeVertexMainShaderPath = sizeof(vertexShaderPath) / sizeof(*vertexShaderPath);
    //char* vertexMainShaderComplete = new char[sizeVertexMainShaderPath + pathEngine.length()];
    //strcpy(vertexMainShaderComplete, pathEngine.c_str());
    //strcat(vertexMainShaderComplete, vertexShaderPath);

    //const int sizeFragmentMainShaderPath = sizeof(fragmentMainShaderPath) / sizeof(*fragmentMainShaderPath);
    //char* fragmentMainShaderComplete = new char[sizeFragmentMainShaderPath + pathEngine.length()];
    //strcpy(fragmentMainShaderComplete, pathEngine.c_str());
    //strcat(fragmentMainShaderComplete, fragmentMainShaderPath);

    //shaderPrincipal.CreateFromFiles(vertexMainShaderComplete, fragmentMainShaderComplete);

    //delete[]vertexMainShaderComplete;
    //delete[]fragmentMainShaderComplete;

    ////Shader para las sombras
    ////sombra direccionale
    //const int sizeVertexShadowPath = sizeof(vertexShaderShadowPath) / sizeof(*vertexShaderShadowPath);
    //char* vertexShadowComplete = new char[sizeVertexShadowPath + pathEngine.length()];
    //strcpy(vertexShadowComplete, pathEngine.c_str());
    //strcat(vertexShadowComplete, vertexShaderShadowPath);

    //const int sizeFragment = sizeof(fragmentShaderShadowPath) / sizeof(*fragmentShaderShadowPath);
    //char* fragmentShadowComplete = new char[sizeFragment + pathEngine.length()];
    //strcpy(fragmentShadowComplete, pathEngine.c_str());
    //strcat(fragmentShadowComplete, fragmentShaderShadowPath);

    //directionalShadowShader1.CreateFromFiles(vertexShadowComplete, fragmentShadowComplete);

    //delete[]vertexShadowComplete;
    //delete[]fragmentShadowComplete;

    ////sombras omnidireccionales
    //const int sizeVertexOmniShadowPath = sizeof(vertexShaderOmniShadowPath) / sizeof(*vertexShaderOmniShadowPath);
    //char* vertexOmniShadowComplete = new char[sizeVertexOmniShadowPath + pathEngine.length()];
    //strcpy(vertexOmniShadowComplete, pathEngine.c_str());
    //strcat(vertexOmniShadowComplete, vertexShaderOmniShadowPath);

    //const int sizeGeomOmniShadowPath = sizeof(geomShaderOmniShadowPath) / sizeof(*geomShaderOmniShadowPath);
    //char* geomOmniShadowComplete = new char[sizeGeomOmniShadowPath + pathEngine.length()];
    //strcpy(geomOmniShadowComplete, pathEngine.c_str());
    //strcat(geomOmniShadowComplete, geomShaderOmniShadowPath);

    //const int sizeOmniShadowFragment = sizeof(fragmentShaderOmniShadowPath) / sizeof(*fragmentShaderOmniShadowPath);
    //char* fragmentOmniShadowComplete = new char[sizeOmniShadowFragment + pathEngine.length()];
    //strcpy(fragmentOmniShadowComplete, pathEngine.c_str());
    //strcat(fragmentOmniShadowComplete, fragmentShaderOmniShadowPath);

    //omniShadowShader1.CreateFromFiles(vertexOmniShadowComplete, geomOmniShadowComplete, fragmentOmniShadowComplete);
    //
    //delete[] vertexOmniShadowComplete;
    //delete[] geomOmniShadowComplete;
    //delete[] fragmentOmniShadowComplete;

}

bool FsGame::Construct(float _width, float _height, std::string name) {
    width = _width; height = _height;
    return mainWindow.createWindow(width, height, name);
}


//-----------------------Setters---------------------------
void FsGame::SetPathEngine(std::string _path) {
    pathFausEngine = _path;
    ValidarPathEngine();
}


void FsGame::SetCamera(FsCamera& cam) {
    camera = &cam;
}


//-----------------Getters--------------------

std::string FsGame::GetPathEngine() {
    return pathFausEngine;
}

FsGame* FsGame::GetSelfReference() {
    return game;
}

FsCamera* FsGame::GetCamera() {
    return camera;
}

bool* FsGame::GetKeys() {
    return mainWindow.getKeys();
}

float FsGame::GetMouseX() {
    return mainWindow.getXMouseOffset();
}

float FsGame::GetMouseY() {
    return mainWindow.getYMouseOffset();
}

glm::mat4 CalcularMatrizVista() {
    auto target = camera->GetCameraPosition() + camera->getForward();
    return glm::lookAt(glm::vec3(camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z),
        glm::vec3(target.x, target.y, target.z),
        glm::vec3(camera->getUp().x, camera->getUp().y, camera->getUp().z) );
}


Shader* FsGame::GetShader() {
    return &MainShader;
}

void FsGame::Run(std::vector<FsObject*> _objetos) {

    ValidarPathEngine();
    ValidarVentana();
    ValidarCamara();

    const char vertex[] = "/Shaders/FsVertexShader.glsl";
    const char fragment[] = "/Shaders/FsFragmentShader.glsl";
    const int sizeVertexMainShaderPath = sizeof(vertex) / sizeof(*vertex);
    char* vertexMainShaderComplete = new char[sizeVertexMainShaderPath + pathFausEngine.length()];
    strcpy(vertexMainShaderComplete, pathFausEngine.c_str());
    strcat(vertexMainShaderComplete, vertex);

    const int sizeFragmentMainShaderPath = sizeof(fragment) / sizeof(*fragment);
    char* fragmentMainShaderComplete = new char[sizeFragmentMainShaderPath + pathFausEngine.length()];
    strcpy(fragmentMainShaderComplete, pathFausEngine.c_str());
    strcat(fragmentMainShaderComplete, fragment);


    MainShader.Load(vertexMainShaderComplete, fragmentMainShaderComplete);

    for each (auto var in _objetos)
    {
        var->Begin();
    }

    FsVector3 frustrum = *camera->GetFrustrum();
    glm::mat4 projection = glm::perspective(frustrum.x, (float)width/(float)height, frustrum.y, frustrum.z);
	
    while (!glfwWindowShouldClose(mainWindow.getWindowReference()))
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents(); 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        MainShader.Use();
        MainShader.SetUniformMatrix4fv("model", glm::mat4(1.0));  // do not need to translate the models so just send the identity matrix
        MainShader.SetUniformMatrix4fv("view", CalcularMatrizVista());
        MainShader.SetUniformMatrix4fv("projection", projection);
        MainShader.SetUniform3f("eyePos", camera->GetCameraPosition());
        MainShader.SetUniform1i("pointLightCounter", 3);
        MainShader.SetUniform1i("spotLightCounter", 3);


        for each (auto var in _objetos)
        {
            var->Update(deltaTime, now);
        }

        glUseProgram(0);
        glfwSwapBuffers(mainWindow.getWindowReference());
    }
   
	
}



