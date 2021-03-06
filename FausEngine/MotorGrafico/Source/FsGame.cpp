#include"../Headers/FsGame.h"
#include "../Headers/Window.h"
#include "../Headers/FsCamera.h"
#include"../Headers/FsMesh.h"
#include"../Headers/FsDirectionalLight.h"
#include"../Headers/FsPointLight.h"
#include"../Headers/FsSpotLight.h"

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

FsDireciontalLight* directionalLight;
std::vector<FsPointLight*> pointlights;
std::vector<FsSpotLight*> spotLights;

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

template<> void FsGame::LoadLight<FsDireciontalLight>(FsDireciontalLight* light) {
    directionalLight = light;
}
template<> void FsGame::LoadLight<FsPointLight>(FsPointLight* light) {
    pointlights.push_back(light);
}
template<> void FsGame::LoadLight<FsSpotLight>(FsSpotLight* light) {
    spotLights.push_back(light);
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


FsShader* FsGame::GetShader() {
    return &MainShader;
}

void FsGame::Run(std::vector<FsObject*> _objetos) {

    ValidarPathEngine();
    ValidarVentana();
    ValidarCamara();

    for each (auto var in _objetos)
    {
        var->Begin();
    }

    const char vertex[] = "/Shaders/FsVertexShader.glsl";
    const int sizeVertexMainShaderPath = sizeof(vertex) / sizeof(*vertex);
    char* vertexMainShaderComplete = new char[sizeVertexMainShaderPath + pathFausEngine.length()];
    strcpy(vertexMainShaderComplete, pathFausEngine.c_str());
    strcat(vertexMainShaderComplete, vertex);

    const char fragment[] = "/Shaders/FsFragmentShader.glsl";
    const int sizeFragmentMainShaderPath = sizeof(fragment) / sizeof(*fragment);
    char* fragmentMainShaderComplete = new char[sizeFragmentMainShaderPath + pathFausEngine.length()];
    strcpy(fragmentMainShaderComplete, pathFausEngine.c_str());
    strcat(fragmentMainShaderComplete, fragment);

    MainShader.Load(vertexMainShaderComplete, fragmentMainShaderComplete);
    delete[] vertexMainShaderComplete, fragmentMainShaderComplete;

    MainShader.Compile(pointlights.size(), spotLights.size());

    FsVector3 frustrum = *camera->GetFrustrum();
    glm::mat4 projection = glm::perspective(frustrum.x, (float)width/(float)height, frustrum.y, frustrum.z);

    unsigned int uPointLightCounter = glGetUniformLocation(MainShader.GetShaderId(), "pointLightCounter");
    unsigned int uSpotLightCounter = glGetUniformLocation(MainShader.GetShaderId(), "spotLightCounter");
	
    while (!glfwWindowShouldClose(mainWindow.getWindowReference()))
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents(); 
        glViewport(0,0,width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        MainShader.Use();
        //View matrix
        glUniformMatrix4fv(
            MainShader.GetUVariableLocation(uTypeVariables::uView), 1, GL_FALSE, glm::value_ptr(CalcularMatrizVista()));
        //projection matrix
        glUniformMatrix4fv(
            MainShader.GetUVariableLocation(uTypeVariables::uProjection), 1, GL_FALSE, glm::value_ptr(projection));
        //camera matrix
        glUniform3f(
            MainShader.GetUVariableLocation(uTypeVariables::uEyePos),
            camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);
        //Directional light
        glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_direction), 
            directionalLight->GetDirection()->x, directionalLight->GetDirection()->y, directionalLight->GetDirection()->z);
        glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_ambient),
            directionalLight->GetAmbient()->x, directionalLight->GetAmbient()->y, directionalLight->GetAmbient()->z);
        glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_diffuse),
            directionalLight->GetDiffuse()->x, directionalLight->GetDiffuse()->y, directionalLight->GetDiffuse()->z);
        glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_specular),
            directionalLight->GetSpecular()->x, directionalLight->GetSpecular()->y, directionalLight->GetSpecular()->z);
        
        //Point lights
        glUniform1i(uPointLightCounter, pointlights.size());
        for(int i=0; i< pointlights.size(); i++)
        {
            glUniform3f(MainShader.GetUPointsLocation(uTypeVariables::uPoint_ambient, i),
                pointlights[i]->GetAmbient()->x, pointlights[i]->GetAmbient()->y, pointlights[i]->GetAmbient()->z);
            glUniform3f(MainShader.GetUPointsLocation(uTypeVariables::uPoint_diffuse, i),
                pointlights[i]->GetDiffuse()->x, pointlights[i]->GetDiffuse()->y, pointlights[i]->GetDiffuse()->z);
            glUniform3f(MainShader.GetUPointsLocation(uTypeVariables::uPoint_specular, i),
                pointlights[i]->GetSpecular()->x, pointlights[i]->GetSpecular()->y, pointlights[i]->GetSpecular()->z);
            glUniform3f(MainShader.GetUPointsLocation(uTypeVariables::uPoint_position, i),
                pointlights[i]->GetPosition()->x, pointlights[i]->GetPosition()->y, pointlights[i]->GetPosition()->z);
            glUniform1f(MainShader.GetUPointsLocation(uTypeVariables::uPoint_const, i), *pointlights[i]->GetConstant());
            glUniform1f(MainShader.GetUPointsLocation(uTypeVariables::uPoint_lin, i), *pointlights[i]->GetLinear());
            glUniform1f(MainShader.GetUPointsLocation(uTypeVariables::uPoint_exp, i), *pointlights[i]->GetExponent());
        }


        //Spot lights
        glUniform1i(uSpotLightCounter, spotLights.size());
        for (int i = 0; i < spotLights.size(); i++)
        {
            glUniform3f(MainShader.GetUSpotLocation(uTypeVariables::uPoint_ambient, i),
                spotLights[i]->GetAmbient()->x, spotLights[i]->GetAmbient()->y, spotLights[i]->GetAmbient()->z);
            glUniform3f(MainShader.GetUSpotLocation(uTypeVariables::uPoint_diffuse, i),
                spotLights[i]->GetDiffuse()->x, spotLights[i]->GetDiffuse()->y, spotLights[i]->GetDiffuse()->z);
            glUniform3f(MainShader.GetUSpotLocation(uTypeVariables::uPoint_specular, i),
                spotLights[i]->GetSpecular()->x, spotLights[i]->GetSpecular()->y, spotLights[i]->GetSpecular()->z);
            glUniform3f(MainShader.GetUSpotLocation(uTypeVariables::uPoint_position, i),
                spotLights[i]->GetPosition()->x, spotLights[i]->GetPosition()->y, spotLights[i]->GetPosition()->z);
            glUniform3f(MainShader.GetUSpotLocation(uTypeVariables::uSpot_Dir, i),
                spotLights[i]->GetDirection()->x, spotLights[i]->GetDirection()->y, spotLights[i]->GetDirection()->z);
            glUniform1f(MainShader.GetUSpotLocation(uTypeVariables::uPoint_const, i), *spotLights[i]->GetConstant());
            glUniform1f(MainShader.GetUSpotLocation(uTypeVariables::uPoint_lin, i), *spotLights[i]->GetLinear());
            glUniform1f(MainShader.GetUSpotLocation(uTypeVariables::uPoint_exp, i), *spotLights[i]->GetExponent());
        }

        for each (auto var in _objetos)
        {
            var->Update(deltaTime, now);
        }

        glUseProgram(0);
        glfwSwapBuffers(mainWindow.getWindowReference());
    }
   
	
}



