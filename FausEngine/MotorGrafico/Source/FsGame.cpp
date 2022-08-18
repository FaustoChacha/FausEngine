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
//#include<filesystem>
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
FsSkybox* skybox;
FsShader MainShader;
FsShader SkyboxShader;

FsDireciontalLight* directionalLight;
std::vector<FsPointLight*> pointlights;
std::vector<FsSpotLight*> spotLights;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

char* EmitirShader(int);



//namespace fs = std::filesystem;

char* EmitirShader(int n) {
    //vertex MainShader
    if (n == 0) {
        char* vertexShader = "#version 330 core \n\
        \n\
        //orden en la inicializacion de buffers! (Mesh.h)\n\
        layout(location = 0) in vec3 position;\n\
        layout(location = 1) in vec3 normal;\n\
        layout(location = 2) in vec2 texture;\n\
        \n\
        uniform mat4 model;\n\
        uniform mat4 view;\n\
        uniform mat4 projection;\n\
        \n\
        out vec3 FragPos;\n\
        out vec3 Normal;\n\
        out vec2 TexCoord;\n\
        \n\
        void main()\n\
        {\n\
            gl_Position = projection * view * model * vec4(position, 1.0f);\n\
            Normal = mat3(transpose(inverse(model))) * normal;\n\
            TexCoord = texture;\n\
        \n\
            FragPos = vec3(model * vec4(position, 1.0f));\n\
        }";

        return vertexShader;
    }
    //fragment Main sahder
    if (n == 1) {
        char* fragmentShader = "#version 330 core \n\#define MAX_POINT_LIGHTS 50\n\#define MAX_SPOT_LIGHTS 50\n\
        in vec2 TexCoord;\n\
        in vec3 FragPos;\n\
        in vec3 Normal;\n\
        \n\
        out vec4 fragColor;\n\
        \n\
        struct Light {\n\
	        vec3 ambient;\n\
	        vec3 diffuse;\n\
	        vec3 specular;\n\
        };\n\
        struct DirectionalLight\n\
        {\n\
	        Light base;\n\
	        vec3 direction;\n\
        };\n\
        struct PointLight\n\
        {\n\
	        Light base;\n\
	        vec3 position;\n\
	        float constant;\n\
	        float linear;\n\
	        float exponent;\n\
        };\n\
        struct SpotLight\n\
        {\n\
	        Light base;\n\
	        vec3 position;\n\
	        vec3 direction;\n\
	        float cosInnerCone;\n\
	        float cosOuterCone;\n\
	        float constant;\n\
	        float linear;\n\
	        float exponent;\n\
        };\n\
        struct Material\n\
        {\n\
	        vec3 ambient;\n\
	        vec3 specular;\n\
	        float shininess;\n\
	        sampler2D texture;\n\
        };\n\
        uniform DirectionalLight directionalLight;\n\
        uniform int pointLightCounter;\n\
        uniform PointLight pointLights[MAX_POINT_LIGHTS];\n\
        uniform int spotLightCounter;\n\
        uniform SpotLight spotLights[MAX_SPOT_LIGHTS];\n\
        uniform Material material;\n\
        uniform vec3 eyePos;\n\
        uniform bool lit;\n\
        uniform vec3 color;\n\
        uniform bool useTexture;\n\
        //=====================Directional Light Calculation==========================\n\
        vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 eyePos)\n\
        {\n\
	        vec3 lightDir = normalize(-light.direction);  // direccion desde el fragment a la luz\n\
	        // Diffuse \n\
	        float Normal_Dot_Light = max(dot(normal, lightDir), 0.0);\n\
	        vec3 diffuse = light.base.diffuse * Normal_Dot_Light * vec3(texture(material.texture, TexCoord));\n\
	        // Specular\n\
	        vec3 Dir_Eye_to_light = normalize(lightDir + eyePos);\n\
	        float Normal_dot_dirEL = max(dot(normal, Dir_Eye_to_light), 0.0f);\n\
	        vec3 specular = light.base.specular * material.specular * pow(Normal_dot_dirEL, material.shininess);\n\
	        return (diffuse + specular);\n\
        }\n\
        //=====================Point Light Calculation==========================\n\
        vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 eyePos)\n\
        {\n\
	        vec3 lightDir = normalize(light.position - fragPos);\n\
	        // Diffuse \n\
	        float Normal_Dot_Light = max(dot(normal, lightDir), 0.0);\n\
	        vec3 diffuse = light.base.diffuse * Normal_Dot_Light * vec3(texture(material.texture, TexCoord));\n\
	        // Specular \n\
	        vec3 Dir_Eye_to_light = normalize(lightDir + eyePos);\n\
	        float Normal_dot_dirEL = max(dot(normal, Dir_Eye_to_light), 0.0f); \n\
	        vec3 specular = light.base.specular * material.specular * pow(Normal_dot_dirEL, material.shininess);\n\
	        // Attenuation\n\
	        float d = length(light.position - FragPos);\n\
	        float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));\n\
	        diffuse *= attenuation;\n\
	        specular *= attenuation;\n\
	        return (diffuse + specular);\n\
        }\n\
        //=====================Spot Light Calculation==========================\n\
        vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 eyePos)\n\
        {\n\
	        vec3 lightDir = normalize(light.position - fragPos);\n\
	        vec3 spotDir = normalize(light.direction);\n\
	        float cosDir = dot(-lightDir, spotDir);\n\
	        //float spotIntensity = smoothstep(light.cosOuterCone, light.cosInnerCone, cosDir);\n\
	        float spotIntensity = smoothstep(0.93f, 0.96f, cosDir);\n\
	        // Diffuse \n\
	        float Normal_Dot_Light = max(dot(normal, lightDir), 0.0);\n\
	        vec3 diffuse = light.base.diffuse * Normal_Dot_Light * vec3(texture(material.texture, TexCoord));\n\
	        // Specular\n\
	        vec3 Dir_Eye_to_light = normalize(lightDir + eyePos);\n\
	        float Normal_dot_dirEL = max(dot(normal, Dir_Eye_to_light), 0.0f);\n\
	        vec3 specular = light.base.specular * material.specular * pow(Normal_dot_dirEL, material.shininess);\n\
	        // Attenuation 1 / c + l * d + exp * d2\n\
	        float d = length(light.position - FragPos);\n\
	        float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));\n\
	        diffuse *= attenuation * spotIntensity;\n\
	        specular *= attenuation * spotIntensity;\n\
	        return (diffuse + specular);\n\
        }\n\
        //================================MAIN===============================\n\
        void main()\n\
        {\n\
	        if (lit)\n\
	        {\n\
		        vec3 normal = normalize(Normal);\n\
		        vec3 viewDir = normalize(eyePos - FragPos);\n\
		        // Ambient \n\
		        vec3 ambient = vec3(0.0f);\n\
		        for (int i = 0; i < spotLightCounter; i++)\n\
			        ambient = spotLights[i].base.ambient * material.ambient * vec3(texture(material.texture, TexCoord)) * directionalLight.base.ambient;\n\
		        vec3 outColor = vec3(0.0f);\n\
		        //Directional light\n\
		        outColor += calcDirectionalLight(directionalLight, normal, viewDir);\n\
		        //Pointlight\n\
		        for (int i = 0; i < pointLightCounter; i++)\n\
			        outColor += calcPointLight(pointLights[i], normal, FragPos, viewDir);\n\
		        //Spotlight\n\
		        for (int i = 0; i < spotLightCounter; i++)\n\
			        outColor += calcSpotLight(spotLights[i], normal, FragPos, viewDir);\n\
		        fragColor = vec4(ambient + outColor, 1.0f) * vec4(color, 1.0f);\n\
	        }\n\
	        else {\n\
		        if (useTexture)\n\
			        fragColor = vec4(color, 1.0f) * vec4(vec3(texture(material.texture, TexCoord)), 1.0f);\n\
		        else\n\
			        fragColor = vec4(color, 1.0f);\n\
	        }\n\
        }";
    return fragmentShader;
    }

    if (n == 2) {
        char* vertexSkyShader = "#version 330 core\n\
        \n\
        layout(location = 0) in vec3 pos;\n\
        \n\
        out vec3 TexCoords;\n\
        \n\
        uniform mat4 projection; \n\
        uniform mat4 view;\n\
        \n\
        void main()\n\
        {\n\
            TexCoords = pos; \n\
            gl_Position = projection * view * vec4(pos, 1.0);\n\
        }";
        return vertexSkyShader;
    }

    if (n==3) {
        char* fragmentSkyShader = "#version 330\n\
        \n\
        in vec3 TexCoords;\n\
        \n\
        out vec4 colour;\n\
        \n\
        uniform samplerCube skybox;\n\
        \n\
        void main()\n\
        {\n\
            colour = texture(skybox, TexCoords);\n\
        }";
        return fragmentSkyShader;
    }
    
    return "";
}

struct stat buffer;

//Prototipos
void ValidarVentana();
void ValidarCamara();
void ValidarLuzDireccional();

//static std::string FausEngine::GetPath() {
//    fs::path ruta = fs::current_path();
//    std::string rutaFinal = ruta.string();
//    return rutaFinal;
//}

glm::mat4 CalcularMatrizVista();

FsGame::FsGame() {
    
    if (!game) game = this;
}

FsGame::~FsGame() {
    //delete[] camera;

}


void ValidarCamara() {
    if (!camera) {
        camera = new FsCamera(FsVector3(0.0f, 5.0f, 0.0f));
    }
}

void ValidarVentana() {
    if (!mainWindow.getWindowReference()) {
        std::cout << "No exits a window, call Construct() function." << std::endl;
        exit(3);
    }
}

void ValidarLuzDireccional() {
    if (!directionalLight) {
        std::cout << "No exits a Directional light..." << std::endl;
        directionalLight = new FsDireciontalLight(FsVector3(0.0f, -0.4f, -0.17f), FsVector3(2, 2, 2), FsVector3(0.5f, 0.5f, 0.5f), FsVector3(0.5f, 0.5f, 0.5f));
    }
}


bool FsGame::Construct(float _width, float _height, std::string name) {
    width = _width; height = _height;
    return mainWindow.createWindow(width, height, name);
}


//-----------------------Setters---------------------------
void FsGame::SetCamera(FsCamera& cam) {
    camera = &cam;
}

void FsGame::SetSkybox(FsSkybox& sky) {
    skybox = &sky;
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

FsGame* FsGame::GetInstance() {
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
    auto target = camera->GetTarget();
    return glm::lookAt(glm::vec3(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z),
        glm::vec3(target.x , target.y, target.z),
        glm::vec3(camera->GetUp().x, camera->GetUp().y, camera->GetUp().z) 
    );
}


FsShader* FsGame::GetShader() {
    return &MainShader;
}

void FsGame::Run(std::vector<FsObject*> _objetos) {

    ValidarVentana();
    ValidarCamara();
    

    //std::string rutaFinal = fs::current_path().string();
    
    for each (auto var in _objetos)
    {
        var->Begin();
    }
    ValidarLuzDireccional();

    //const char vertex[] = "/Shaders/FsVertexShader.glsl";
    //const int sizeVertexMainShaderPath = sizeof(vertex) / sizeof(*vertex);
    //char* vertexMainShaderComplete = new char[sizeVertexMainShaderPath + pathFausEngine.length()];
    //strcpy(vertexMainShaderComplete, pathFausEngine.c_str());
    //strcat(vertexMainShaderComplete, vertex);

    //const char fragment[] = "/Shaders/FsFragmentShader.glsl";
    //const int sizeFragmentMainShaderPath = sizeof(fragment) / sizeof(*fragment);
    //char* fragmentMainShaderComplete = new char[sizeFragmentMainShaderPath + rutaFinal.length()];
    //strcpy(fragmentMainShaderComplete, rutaFinal.c_str());
    //strcat(fragmentMainShaderComplete, fragment);

    //MainShader.Load(vertexMainShaderComplete, fragmentMainShaderComplete);
    MainShader.Load(EmitirShader(0),EmitirShader(1));
    SkyboxShader.Load(EmitirShader(2),EmitirShader(3));
    //delete[] /*vertexMainShaderComplete*/ fragmentMainShaderComplete;

    MainShader.Compile(pointlights.size(), spotLights.size());
    SkyboxShader.Compile(0,0);

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
            camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

        //Directional light
        if (directionalLight->on) {
            glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_direction),
                directionalLight->GetDirection()->x, directionalLight->GetDirection()->y, directionalLight->GetDirection()->z);
            glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_ambient),
                directionalLight->GetAmbient()->x, directionalLight->GetAmbient()->y, directionalLight->GetAmbient()->z);
            glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_diffuse),
                directionalLight->GetDiffuse()->x, directionalLight->GetDiffuse()->y, directionalLight->GetDiffuse()->z);
            glUniform3f(MainShader.GetUVariableLocation(uTypeVariables::uDir_specular),
                directionalLight->GetSpecular()->x, directionalLight->GetSpecular()->y, directionalLight->GetSpecular()->z);
        }
       
        //Point lights
        glUniform1i(uPointLightCounter, pointlights.size());
        for(int i=0; i< pointlights.size(); i++)
        {
            if (pointlights[i]->on) {
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
        }

        //Spot lights
        glUniform1i(uSpotLightCounter, spotLights.size());
        for (int i = 0; i < spotLights.size(); i++)
        {
            if (spotLights[i]->on) {
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
        }

        for each (auto var in _objetos)
        {
            var->Update(deltaTime, now);
        }

        glUseProgram(0);
        glfwSwapBuffers(mainWindow.getWindowReference());
    }
   
	
}



