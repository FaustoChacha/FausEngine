#include"../Headers/FsGame.h"
#include "../Headers/Window.h"
#include "../Headers/FsCamera.h"
#include"../Headers/FsMesh.h"
#include"../Headers/FsDirectionalLight.h"
#include"../Headers/FsPointLight.h"
#include"../Headers/FsSpotLight.h"
//#include"../Headers/FsLog.h"

#include <glm\gtc\type_ptr.hpp>
#include<string>
#include<iostream>

//#include<filesystem>
#include<memory>
#include<fstream>
#include <sys/types.h>
#include<sys/stat.h>

#include <algorithm>
#include<cmath>

#include "spdlog/sinks/basic_file_sink.h"
#include"spdlog/spdlog.h"


using namespace FausEngine;

static std::shared_ptr<FsGame> game(new FsGame);
int index_scene = 0;
int begin = 0;

Window mainWindow;
GLsizei width, height;
std::shared_ptr<FsCamera> camera;
std::unique_ptr<FsSkybox> skybox(new FsSkybox);

std::shared_ptr<FsShader> MainShader(new FsShader);
std::shared_ptr<FsShader> SkyboxShader(new FsShader);
std::shared_ptr<FsShader> TextShader(new FsShader);
std::shared_ptr<FsShader> ImageShader(new FsShader);

FsDireciontalLight* directionalLight;
std::unique_ptr<FsDireciontalLight> smartDirectional(nullptr);
std::vector<FsPointLight*> pointlights;
std::vector<FsSpotLight*> spotLights;
std::vector<int> tipoLog;
std::vector<std::string> msgsLog;



GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;



char* EmitirShader(int);


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
    //vertex skyshader
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
    //fragment skysahder
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
    //vertex textshader
    if (n == 4) {
        char* vertexTextShader="#version 330 core\n\
        layout(location = 0) in vec4 vertex; \n\
        out vec2 TexCoords;\n\
        \n\
        uniform mat4 projection;\n\
        \n\
        void main()\n\
        {\n\
            gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n\
            TexCoords = vertex.zw;\n\
        }";
        return vertexTextShader;
    }
    //fragment textshader
    if (n==5) {
        char* fragmenttextShader = "#version 330 \n\
        in vec2 TexCoords;\n\
        uniform sampler2D text;\n\
        uniform vec3 textColor;\n\
        out vec4 color;\n\
        void main() {\n\
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n\
            color = vec4(textColor, 1.0) * sampled;\n\
        }";
        return fragmenttextShader;
    }
    //vertex image shader
    if (n == 6) {
        char* vertexImageShader = "#version 330 core\n\
        layout(location = 0) in vec3 pos;\n\
        layout(location = 1) in vec2 texCoord;\n\
        uniform mat4 model;\n\
        out vec2 TexCoord;\n\
        void main()\n\
        {\n\
            gl_Position = model * vec4(pos, 1.0);\n\
            TexCoord = texCoord;\n\
        }"; 
        return vertexImageShader;
    }
    // fragment image shader
    if (n == 7) {
        char* fragmentImageShader = "#version 330 core\n\
        in vec2 TexCoord;\n\
        out vec4 frag_color;\n\
        uniform sampler2D texSampler1;\n\
        void main()\n\
        {\n\
            vec4 texColor = texture(texSampler1, TexCoord);\n\
            if(texColor.a < 0.1) discard;\n\
            frag_color = texColor;\n\
        }";
        return fragmentImageShader;
    }
    return "";
}

struct stat buffer;

//Prototipos
void ValidarVentana();
void ValidarCamara();
void ValidarLuzDireccional();

glm::mat4 CalcularMatrizVista();


FsGame::FsGame() {
    if (!game) *game = *this;

    //logger.CreateLogger("Game","GameLog");
    
}

FsGame::~FsGame() {
    //delete[] camera;
    //for (auto i = 0; i < spotLights.size(); i++)
    //    delete spotLights[i];

    //for (auto i = 0; i < pointlights.size(); i++)
    //    delete pointlights[i];

}


void ValidarCamara() {
    if (!camera) {
        //logger.SetName("Camera: ");
        //logger.SetMessage("Not set camera (default camera activate). ",1);
        FausEngine::FsGame::GetReference()->SetLog("Not set camera (default camera activate). ",1);

        camera.reset(new FsCamera());
        camera->SetPosition(FsVector3(0.0f, 0.0f, -5.0f));
    }
    else {
        //logger.SetMessage("Camera created. ", 0);
        FausEngine::FsGame::GetReference()->SetLog("Camera created. ", 0);
    }
}

void ValidarVentana() {
    if (!mainWindow.getWindowReference()) {
        //logger.SetName("Window");
        //logger.SetMessage("No exits window, call Construct() function.", 2);
        FausEngine::FsGame::GetReference()->SetLog("No exits window, call Construct() function. ", 2);
        exit(3);
    }
}

void ValidarLuzDireccional() {
    //if (!directionalLight) {
    //    std::cout << "No exits Directional light..." << std::endl;
    //    directionalLight = new FsDireciontalLight(FsVector3(0.0f, -0.4f, -0.17f), FsVector3(2, 2, 2), FsVector3(0.5f, 0.5f, 0.5f), FsVector3(0.5f, 0.5f, 0.5f));
    //}
}


bool FsGame::Construct(float _width, float _height, std::string name, bool fullscreen) {
    width = _width; height = _height;
   return mainWindow.createWindow(width, height, name, fullscreen);
}


//-----------------------Setters---------------------------
void FsGame::SetCamera(FsCamera& cam) {
    //camera = &cam;
    camera.reset(new FsCamera);
    *camera = cam;
}

void FsGame::SetSkybox(FsSkybox& sky) {
    //skybox = &sky;
    *skybox = sky;
}

void FsGame::SetLog(std::string msg, int i) {
    tipoLog.push_back(i);
    msgsLog.push_back(msg);
}

template<> void FsGame::LoadLight<FsDireciontalLight>(FsDireciontalLight* light) {
//template<> void FsGame::LoadLight<FsDireciontalLight>(std::shared_ptr<FsDireciontalLight> light) {
    directionalLight = light;
    smartDirectional.reset();
    //*smartDirectional = *light;
    smartDirectional = std::make_unique<FsDireciontalLight>(*light);
}


template<> void FsGame::LoadLight<FsPointLight>(FsPointLight* light) {

    pointlights.push_back(light);
    //pointlights.push_back(std::shared_ptr<FsPointLight>(light));
}


template<> void FsGame::LoadLight<FsSpotLight>(FsSpotLight* light) {
//template<> void FsGame::LoadLight<FsSpotLight>(std::shared_ptr<FsSpotLight> light) {
    spotLights.push_back(light);

}

//-----------------Getters--------------------

const std::shared_ptr<FsGame> FsGame::GetReference() {

    return game;
}

const std::shared_ptr<FsCamera> FsGame::GetCamera() {
    //return std::shared_ptr<FsCamera>(camera); // igual que hacer: return camera;
    return camera;
}


bool FsGame::GetKeyPress(Keys k) {
    return mainWindow.getKeys()[(int)k];
}

void FsGame::SetKeyRelease(Keys k) {
    mainWindow.getKeys()[(int)k] = false;
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

void FsGame::SetScene(int s) {
    index_scene = s;
    begin = 0;
}

const std::shared_ptr <FsShader> FsGame::GetShader(int n) {
    if (n == 0) return MainShader;
    if (n == 1) return TextShader;
    if (n == 2) return ImageShader;
}



void FsGame::Run(std::vector<FsScene*> escena) {
    //void FsGame::Run(std::vector<std::shared_ptr<FsScene>> escena) {

    ValidarVentana();
    ValidarCamara();


    MainShader->Load2("../../Motor/Shaders/FsVertexShader.glsl", "../../Motor/Shaders/FsFragmentShader.glsl");


    //MainShader->Load(EmitirShader(0), EmitirShader(1)); 
    //MainShader->Load2("../../Motor/Shaders/FsVertexShader.glsl","../../Motor/Shaders/FsFragmentShader.glsl");
    SkyboxShader->Load(EmitirShader(2), EmitirShader(3));
    TextShader->Load(EmitirShader(4), EmitirShader(5));
    ImageShader->Load(EmitirShader(6), EmitirShader(7));

    unsigned int uPointLightCounter = 0;
    unsigned int uSpotLightCounter = 0;

    FsVector3 frustrum = camera->GetFrustrum();
    glm::mat4 projection = glm::perspective(frustrum.x, (float)width / (float)height, frustrum.y, frustrum.z);

    ////===================== sky box =====================
    unsigned int vao, ibo, vbo;

    //===========================Texto===============================
    TextShader->Use();
    glm::mat4 ortoProjection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));
    glUniformMatrix4fv(TextShader->GetUVariableLocation(uTypeVariables::uOrtoProjection), 1, GL_FALSE, glm::value_ptr(ortoProjection));

    //==========================Log================
    auto logger = spdlog::basic_logger_mt("FausEngine", "Logs/Log.txt");

    while (!glfwWindowShouldClose(mainWindow.getWindowReference()))
    {
        if (begin == 0) {
            if (index_scene > escena.size() || index_scene < 0) exit(3);

            escena[index_scene]->Begin();

            for (int i = 0; i < msgsLog.size(); i++) {
                switch (tipoLog[i])
                {
                case 0:
                    logger->info("Scene " + std::to_string(index_scene) + ": " + msgsLog[i]);
                    break;
                case 1:
                    logger->warn("Scene " + std::to_string(index_scene) + ": " + msgsLog[i]);
                    break;
                case 2:
                    logger->error("Scene " + std::to_string(index_scene) + ": " + msgsLog[i]);
                default:
                    logger->info("Scene " + std::to_string(index_scene) + ": " + msgsLog[i]);
                    break;
                }

            }

            MainShader->Compile(pointlights.size(), spotLights.size());
            SkyboxShader->Compile(0, 0);
            TextShader->Compile(0, 0);
            ImageShader->Compile(0, 0);

            uPointLightCounter = glGetUniformLocation(MainShader->GetShaderId(), "pointLightCounter");
            uSpotLightCounter = glGetUniformLocation(MainShader->GetShaderId(), "spotLightCounter");
            //===================== sky box construct=====================
            if (skybox) {
                // Mesh setting
                unsigned int skyboxIndices[] = {
                    // front
                    0, 1, 2,
                    2, 1, 3,
                    // right
                    2, 3, 5,
                    5, 3, 7,
                    // back
                    5, 7, 4,
                    4, 7, 6,
                    // left
                    4, 6, 0,
                    0, 6, 1,
                    // top
                    4, 0, 5,
                    5, 0, 2,
                    // bottom
                    1, 6, 3,
                    3, 6, 7
                };
                float skyboxVertices[] = {
                    -1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
                    -1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
                    1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

                    -1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
                    -1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
                    1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
                };

                glGenVertexArrays(1, &vao);
                glBindVertexArray(vao);

                glGenBuffers(1, &ibo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices[0]) * 36, skyboxIndices, GL_STATIC_DRAW);

                glGenBuffers(1, &vbo);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices[0]) * 64, skyboxVertices, GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(skyboxVertices[0]) * 8, 0);
                glEnableVertexAttribArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

                glBindVertexArray(0);
            }

            begin = 1;
        }

        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();
        glViewport(0, 0, width, height);
        //glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //====================skybox render======================
        if (skybox) {
            if (skybox->GetActive()) {
                glDepthMask(GL_FALSE);
                SkyboxShader->Use();
                //projection matrix
                glUniformMatrix4fv(
                    SkyboxShader->GetUVariableLocation(uTypeVariables::uProjection), 1, GL_FALSE, glm::value_ptr(projection));
                //View matrix
                glm::mat4 view = glm::mat4(glm::mat3(CalcularMatrizVista()));
                glUniformMatrix4fv(
                    SkyboxShader->GetUVariableLocation(uTypeVariables::uView), 1, GL_FALSE, glm::value_ptr(view));

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GetTextureID());

                glBindVertexArray(vao);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
                glDepthMask(GL_TRUE);
            }
            else {
                glClearColor(skybox->GetColour().x, skybox->GetColour().y, skybox->GetColour().z, 1);
            }
        }

        //========================Render scene============================
        MainShader->Use();
        //View matrix
        glUniformMatrix4fv(
            MainShader->GetUVariableLocation(uTypeVariables::uView), 1, GL_FALSE, glm::value_ptr(CalcularMatrizVista()));
        //projection matrix
        glUniformMatrix4fv(
            MainShader->GetUVariableLocation(uTypeVariables::uProjection), 1, GL_FALSE, glm::value_ptr(projection));
        //camera matrix
        glUniform3f(
            MainShader->GetUVariableLocation(uTypeVariables::uEyePos),
            camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

        //Directional light
        if (directionalLight && directionalLight->GetActive()) {
            glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_direction),
                directionalLight->GetDirection().x, directionalLight->GetDirection().y, directionalLight->GetDirection().z);
            glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_ambient),
                directionalLight->GetAmbient().x, directionalLight->GetAmbient().y, directionalLight->GetAmbient().z);
            glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_diffuse),
                directionalLight->GetDiffuse().x, directionalLight->GetDiffuse().y, directionalLight->GetDiffuse().z);
            glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_specular),
                directionalLight->GetSpecular().x, directionalLight->GetSpecular().y, directionalLight->GetSpecular().z);
        }
        //if (smartDirectional && smartDirectional->GetActive()) {
        //    glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_direction),
        //        smartDirectional->GetDirection().x, smartDirectional->GetDirection().y, smartDirectional->GetDirection().z);
        //    glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_ambient),
        //        smartDirectional->GetAmbient().x, smartDirectional->GetAmbient().y, smartDirectional->GetAmbient().z);
        //    glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_diffuse),
        //        smartDirectional->GetDiffuse().x, smartDirectional->GetDiffuse().y, smartDirectional->GetDiffuse().z);
        //    glUniform3f(MainShader->GetUVariableLocation(uTypeVariables::uDir_specular),
        //        smartDirectional->GetSpecular().x, smartDirectional->GetSpecular().y, smartDirectional->GetSpecular().z);
        //}
        

        //Point lights
        glUniform1i(uPointLightCounter, pointlights.size());
        for (int i = 0; i < pointlights.size(); i++)
        {
            if (pointlights[i]->GetActive()) {
                glUniform3f(MainShader->GetUPointsLocation(uTypeVariables::uPoint_ambient, i),
                    pointlights[i]->GetAmbient().x, pointlights[i]->GetAmbient().y, pointlights[i]->GetAmbient().z);
                glUniform3f(MainShader->GetUPointsLocation(uTypeVariables::uPoint_diffuse, i),
                    pointlights[i]->GetDiffuse().x, pointlights[i]->GetDiffuse().y, pointlights[i]->GetDiffuse().z);
                glUniform3f(MainShader->GetUPointsLocation(uTypeVariables::uPoint_specular, i),
                    pointlights[i]->GetSpecular().x, pointlights[i]->GetSpecular().y, pointlights[i]->GetSpecular().z);
                glUniform3f(MainShader->GetUPointsLocation(uTypeVariables::uPoint_position, i),
                    pointlights[i]->GetPosition().x, pointlights[i]->GetPosition().y, pointlights[i]->GetPosition().z);
                glUniform1f(MainShader->GetUPointsLocation(uTypeVariables::uPoint_const, i), pointlights[i]->GetConstant());
                glUniform1f(MainShader->GetUPointsLocation(uTypeVariables::uPoint_lin, i), pointlights[i]->GetLinear());
                glUniform1f(MainShader->GetUPointsLocation(uTypeVariables::uPoint_exp, i), pointlights[i]->GetExponent());
            }
        }

        //Spot lights
        glUniform1i(uSpotLightCounter, spotLights.size());
        for (int i = 0; i < spotLights.size(); i++)
        {
            if (spotLights[i]->GetActive()) {
                glUniform3f(MainShader->GetUSpotLocation(uTypeVariables::uPoint_ambient, i),
                    spotLights[i]->GetAmbient().x, spotLights[i]->GetAmbient().y, spotLights[i]->GetAmbient().z);
                glUniform3f(MainShader->GetUSpotLocation(uTypeVariables::uPoint_diffuse, i),
                    spotLights[i]->GetDiffuse().x, spotLights[i]->GetDiffuse().y, spotLights[i]->GetDiffuse().z);
                glUniform3f(MainShader->GetUSpotLocation(uTypeVariables::uPoint_specular, i),
                    spotLights[i]->GetSpecular().x, spotLights[i]->GetSpecular().y, spotLights[i]->GetSpecular().z);
                glUniform3f(MainShader->GetUSpotLocation(uTypeVariables::uPoint_position, i),
                    spotLights[i]->GetPosition().x, spotLights[i]->GetPosition().y, spotLights[i]->GetPosition().z);
                glUniform3f(MainShader->GetUSpotLocation(uTypeVariables::uSpot_Dir, i),
                    spotLights[i]->GetDirection().x, spotLights[i]->GetDirection().y, spotLights[i]->GetDirection().z);
                glUniform1f(MainShader->GetUSpotLocation(uTypeVariables::uPoint_const, i), spotLights[i]->GetConstant());
                glUniform1f(MainShader->GetUSpotLocation(uTypeVariables::uPoint_lin, i), spotLights[i]->GetLinear());
                glUniform1f(MainShader->GetUSpotLocation(uTypeVariables::uPoint_exp, i), spotLights[i]->GetExponent());
            }
        }

        escena[index_scene]->Update(deltaTime, now);

        glUseProgram(0);
        glfwSwapBuffers(mainWindow.getWindowReference());
    }

    //for (auto i = 0; i < escena.size(); i++)
    //    delete escena[i];
    // ========== liberar memoria =================
    //delete skybox, camera, directionalLight, game;

    //for (auto i = 0; i < spotLights.size(); i++)
    //    delete spotLights[i];

    //for (auto i = 0; i < pointlights.size(); i++)
    //    delete pointlights[i];
	
}


