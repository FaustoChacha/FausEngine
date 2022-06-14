#include"../Headers/FsGame.h"
#include "../Headers/Window.h"
#include "../Headers/FsCamera.h"
//#include"../Headers/FsSkybox.h"

#include <glm\gtc\type_ptr.hpp>
#include<string>
#include<iostream>
#include<memory>
#include<fstream>
#include<sys/stat.h>
#include <algorithm>

using namespace FausEngine;

static FsGame* game;
//static FsDirectionalLight* luzDireccional = nullptr;
//static std::vector<FsPointLight*> lucesPuntualesVec;
//static std::vector<FsSpotLight*> lucesLinternaVec;


Window mainWindow;
GLsizei width, height;
FsCamera* camera;
//std::shared_ptr<FsCamera> camera{ new FsCamera(FsVector3(0.0f, 5.0f, 0.0f), FsVector3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f) };

//FsShader* currentShader;
//FsShader shaderPrincipal;
//FsShader directionalShadowShader1;
//FsShader omniShadowShader1;
//
//FsSkybox* skyBox;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

std::string pathFausEngine;

// Vertex Shader
char vertexShaderPath[] = "Shaders/shader.vert";
char vertexShaderShadowPath[] = "Shaders/directional_shadow_map.vert";
char vertexShaderOmniShadowPath[] = "Shaders/omni_directional_shadow_map.vert";

//Geometry Shader
char geomShaderOmniShadowPath[] = "Shaders/omni_directional_shadow_map.geom";

// Fragment Shader
char fragmentMainShaderPath[] = "Shaders/shader.frag";
char fragmentShaderShadowPath[] = "Shaders/directional_shadow_map.frag";
char fragmentShaderOmniShadowPath[] = "Shaders/omni_directional_shadow_map.frag";

struct stat buffer;

//Prototipos
void ValidarPathEngine();
void ValidarVentana();
void ValidarCamara();
void ValidarLuzDireccional();
glm::mat4 CalcularMatrizVista();

FsGame::FsGame() {
    //currentShader = nullptr;
    //if (!game) game = this;
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

void ValidarLuzDireccional() {
    //if (!luzDireccional) {
    //    luzDireccional = new FsDirectionalLight(1024, 1024,
    //        1.0f, 1.0f, 1.0f,
    //        0.4f, 0.3f,
    //        0.0f, -15.0f, -10.0f);
    //    luzDireccional->Load();
    //}
}

void CrearShaders(std::string pathEngine) {
    //Shader con iluminacion 
    const int sizeVertexMainShaderPath = sizeof(vertexShaderPath) / sizeof(*vertexShaderPath);
    char* vertexMainShaderComplete = new char[sizeVertexMainShaderPath + pathEngine.length()];
    strcpy(vertexMainShaderComplete, pathEngine.c_str());
    strcat(vertexMainShaderComplete, vertexShaderPath);

    const int sizeFragmentMainShaderPath = sizeof(fragmentMainShaderPath) / sizeof(*fragmentMainShaderPath);
    char* fragmentMainShaderComplete = new char[sizeFragmentMainShaderPath + pathEngine.length()];
    strcpy(fragmentMainShaderComplete, pathEngine.c_str());
    strcat(fragmentMainShaderComplete, fragmentMainShaderPath);

    shaderPrincipal.CreateFromFiles(vertexMainShaderComplete, fragmentMainShaderComplete);

    delete[]vertexMainShaderComplete;
    delete[]fragmentMainShaderComplete;

    //Shader para las sombras
    //sombra direccionale
    const int sizeVertexShadowPath = sizeof(vertexShaderShadowPath) / sizeof(*vertexShaderShadowPath);
    char* vertexShadowComplete = new char[sizeVertexShadowPath + pathEngine.length()];
    strcpy(vertexShadowComplete, pathEngine.c_str());
    strcat(vertexShadowComplete, vertexShaderShadowPath);

    const int sizeFragment = sizeof(fragmentShaderShadowPath) / sizeof(*fragmentShaderShadowPath);
    char* fragmentShadowComplete = new char[sizeFragment + pathEngine.length()];
    strcpy(fragmentShadowComplete, pathEngine.c_str());
    strcat(fragmentShadowComplete, fragmentShaderShadowPath);

    directionalShadowShader1.CreateFromFiles(vertexShadowComplete, fragmentShadowComplete);

    delete[]vertexShadowComplete;
    delete[]fragmentShadowComplete;

    //sombras omnidireccionales
    const int sizeVertexOmniShadowPath = sizeof(vertexShaderOmniShadowPath) / sizeof(*vertexShaderOmniShadowPath);
    char* vertexOmniShadowComplete = new char[sizeVertexOmniShadowPath + pathEngine.length()];
    strcpy(vertexOmniShadowComplete, pathEngine.c_str());
    strcat(vertexOmniShadowComplete, vertexShaderOmniShadowPath);

    const int sizeGeomOmniShadowPath = sizeof(geomShaderOmniShadowPath) / sizeof(*geomShaderOmniShadowPath);
    char* geomOmniShadowComplete = new char[sizeGeomOmniShadowPath + pathEngine.length()];
    strcpy(geomOmniShadowComplete, pathEngine.c_str());
    strcat(geomOmniShadowComplete, geomShaderOmniShadowPath);

    const int sizeOmniShadowFragment = sizeof(fragmentShaderOmniShadowPath) / sizeof(*fragmentShaderOmniShadowPath);
    char* fragmentOmniShadowComplete = new char[sizeOmniShadowFragment + pathEngine.length()];
    strcpy(fragmentOmniShadowComplete, pathEngine.c_str());
    strcat(fragmentOmniShadowComplete, fragmentShaderOmniShadowPath);

    omniShadowShader1.CreateFromFiles(vertexOmniShadowComplete, geomOmniShadowComplete, fragmentOmniShadowComplete);
    
    delete[] vertexOmniShadowComplete;
    delete[] geomOmniShadowComplete;
    delete[] fragmentOmniShadowComplete;

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

//void FsGame::SetCurrentShader(FsShader* sh) {
//	//currentShader = sh;
//}

//void FsGame::SetSkybox(FsSkybox* sky) {
//    skyBox = sky;
//}

//template<> void FsGame::SetLight<FsDirectionalLight>(FsDirectionalLight* luz) {
//    luzDireccional = luz;
//}

//template<> void FsGame::SetLight<FsPointLight>(FsPointLight* luz) {
//    lucesPuntualesVec.push_back(luz);
//}
//
//template<> void FsGame::SetLight<FsSpotLight>(FsSpotLight* luz) {
//    lucesLinternaVec.push_back(luz);
//}

void FsGame::SetCamera(FsCamera& cam) {
    camera = &cam;
}




//-----------------Getters--------------------

std::string FsGame::GetPathEngine() {
    return pathFausEngine;
}

//FsShader* FsGame::GetCurrentShader() { 
//	return currentShader; 
//};

int* FsGame::GetCountLights() {
    int* luces = new int[2];
    luces[0] = lucesPuntualesVec.size();
    luces[1] = lucesLinternaVec.size();
    return luces;
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


//-----------------Pases de Render--------------------
//void DirectionalShadowMapPass(std::vector<FsObject*> _objetos, GLfloat dTime, GLfloat time ,FsGame* self)
//{
//    directionalShadowShader1.UseShader();
//
//	glViewport(0, 0, luzDireccional->GetShadowMap()->GetShadowWidth(), luzDireccional->GetShadowMap()->GetShadowHeight());
//
//    luzDireccional->GetShadowMap()->Write();
//	glClear(GL_DEPTH_BUFFER_BIT);
//
//	//uniformModel = directionalShadowShader.GetModelLocation();
//	glm::mat4 mat = luzDireccional->GetProj<glm::mat4>() * glm::lookAt(
//        -glm::vec3(luzDireccional->getDirection().x, luzDireccional->getDirection().y, luzDireccional->getDirection().z), 
//        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    directionalShadowShader1.SetDirectionalLightTransform(&mat);
//
//    self->SetCurrentShader(&directionalShadowShader1);
//    directionalShadowShader1.Validate();
//   
//    for each (auto var in _objetos)
//    {
//        var->Update(dTime, time);
//    }
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void OmniShadowMapPass(FsPointLight* light, std::vector<FsObject*> _objetos, GLfloat dTime, GLfloat time ,FsGame* self)
//{
//    
//    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());
//
//    omniShadowShader1.UseShader();
//
//    light->GetShadowMap()->Write();
//
//    glClear(GL_DEPTH_BUFFER_BIT);
//
//    glUniform3f(omniShadowShader1.GetOmniLightPosLocation(), light->GetPosition()->x, light->GetPosition()->y, light->GetPosition()->z);
//    glUniform1f(omniShadowShader1.GetFarPlaneLocation(), light->GetFarPlane());
//    omniShadowShader1.SetOmniLightMatrices(light->CalculateLightTransform<glm::mat4>());
//
//    omniShadowShader1.Validate();
//
//    self->SetCurrentShader(&omniShadowShader1);
//
//    for each (auto var in _objetos)
//    {
//        var->Update(dTime, time);
//    }
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void RenderPass(std::vector<FsObject*> objs, glm::mat4& mProyeccion ,glm::mat4& mVista,
//     FsCamera* cam, GLfloat dTime, GLfloat time ,FsGame* self)
//{
//    
//    glViewport(0, 0, width, height);
//
//    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    //Verificar el SkyBox
//    if(skyBox) skyBox->DrawSkybox(mVista, mProyeccion);
//
//    shaderPrincipal.UseShader();
//
//    //uniformSpecularIntensity = shaderPrincipal.GetSpecularIntensityLocation();
//    //uniformShininess = shaderPrincipal.GetShininessLocation();
//
//    glUniformMatrix4fv(shaderPrincipal.GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(mProyeccion));
//    glUniformMatrix4fv(shaderPrincipal.GetViewLocation(), 1, GL_FALSE, glm::value_ptr(mVista));
//
//    glUniform3f(shaderPrincipal.GetEyePositionLocation(), cam->GetCameraPosition().x, cam->GetCameraPosition().y, cam->GetCameraPosition().z);
//
//    shaderPrincipal.SetDirectionalLight(luzDireccional);
//    //gameReference.GetCurrentShader()->SetPointLights(pointLights, pointLightCount, 3, 0);
//    //gameReference.GetCurrentShader()->SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
//    shaderPrincipal.SetPointLights(lucesPuntualesVec, lucesPuntualesVec.size(), 3, 0); //OJO con el 3 !!!!!!!!!!!!!!!!!!!
//    shaderPrincipal.SetSpotLights(lucesLinternaVec, lucesLinternaVec.size(), 3 + lucesPuntualesVec.size(), lucesPuntualesVec.size());
//    glm::mat4 mat = luzDireccional->GetProj<glm::mat4>() * glm::lookAt(
//        -glm::vec3(luzDireccional->getDirection().x, luzDireccional->getDirection().y, luzDireccional->getDirection().z), 
//        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    shaderPrincipal.SetDirectionalLightTransform(&mat);
//
//    luzDireccional->GetShadowMap()->Read(GL_TEXTURE2);
//
//    shaderPrincipal.SetTexture(1);
//    shaderPrincipal.SetDirectionalShadowMap(2);
//
//    shaderPrincipal.Validate();
//
//    self->SetCurrentShader(&shaderPrincipal);
//
//    for each (auto var in objs)
//    {
//        var->Update(dTime, time);
//    }
//}



void FsGame::Run(std::vector<FsObject*> _objetos) {
    
    ValidarPathEngine();
    ValidarVentana();
    ValidarCamara();
    ValidarLuzDireccional();

    for each (auto var in _objetos)
    {
        var->Begin();
    }

    CrearShaders(pathFausEngine);

    FsVector3 frustrum = *camera->GetFrustrum();
    glm::mat4 projection = glm::perspective(frustrum.x,
            //(GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 
        (float)width/(float)height,
            frustrum.y, frustrum.z);
	
    while (!glfwWindowShouldClose(mainWindow.getWindowReference()))
    {
        GLfloat now = glfwGetTime(); 
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();

        //camera->KeyControl(mainWindow.getsKeys(), deltaTime);
        //camera->MouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        //DirectionalShadowMapPass(_objetos, deltaTime,now, this);

        //for (size_t i = 0; i < lucesPuntualesVec.size(); i++)
        //{
        //    OmniShadowMapPass(lucesPuntualesVec[i],_objetos ,deltaTime, now ,this);
        //}
        //for (size_t i = 0; i < lucesLinternaVec.size(); i++)
        //{
        //    OmniShadowMapPass(lucesLinternaVec[i], _objetos,deltaTime, now ,this);
        //}

        //RenderPass(_objetos, projection, CalcularMatrizVista(),camera, deltaTime, now,this);


        glUseProgram(0);
        glfwSwapBuffers(mainWindow.getWindowReference());
    }
   
	
}



