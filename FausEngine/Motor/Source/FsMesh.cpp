#include "../Headers/FsMesh.h"
#include"../Headers/FsGame.h"

#include "../Headers/stb_image.h"

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp> 

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
//#include <btBulletDynamicsCommon.h>

using namespace FausEngine;

//std::map<int, btRigidBody*> rigidbodies;

FsMesh::FsMesh()
{
    VBO = 0; VAO = 0; meshLoaded = false;

    transform = FsTransform({ 0,0,0 }, { 0,0,0 }, {1,1,1});
    //material = FsMaterial();
    collider = nullptr;
    on = false;
    //logger.CreateLogger("FsMesh","log-FsMesh");
    shader = FausEngine::FsGame::GetReference()->GetShader(0);
}

//FsMesh::FsMesh(std::string _path)
//{
//	path = _path;
//
//	transform = FsTransform({ 0,0,0 }, { 0,0,0 }, { 1,1,1 });
//	material = FsMaterial();
//	collider = nullptr;
//	on = true;
//	logger.CreateLogger("FsMesh", "log-FsMesh");
//	shader = FausEngine::FsGame::GetReference()->GetShader(0);
//}

FsMesh::~FsMesh()
{
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void FsMesh::SetCollider(FsCollider& c) {
    //collider = &c;
    collider = std::shared_ptr<FsCollider>(&c);
    //collider.reset(&c);
    //tomo la posicion de la malla + la pos inicial del limite max/min del collider y hallo la distancia entre el limiite y el centro de la malla
    distanceCollider[0] = collider->DistanceToPivot(transform.position, CollisionDirection::MAX);
    distanceCollider[1] = collider->DistanceToPivot(transform.position, CollisionDirection::MIN);
    distanceCollider[2] = collider->GetBoundMax();
    distanceCollider[3] = collider->GetBoundMin();
}

void FsMesh::SetMaterial(FsMaterial& m) {
    //mat = std::make_shared<FsMaterial>(&m);
    mat = std::shared_ptr<FsMaterial>(&m);
    //mat = std::move(std::make_unique<FsMaterial>(m));
    //mat = &m;
}

void FsMesh::SetVisibility(bool b) {
    on = b;
}

void FsMesh::SetPosition(FsVector3 v) {
    transform.position = v;
}

void FsMesh::SetScale(FsVector3 v) {
    transform.scale = v;
}

void FsMesh::SetRotation(FsVector3 v) {
    transform.rotation = v;
}

void FsMesh::SetTransform(FsTransform t) {
    transform = t;

}

FsTransform FsMesh::GetTransform() {
    return transform;
}
bool FsMesh::GetVisibility(){
    return on;
}

std::vector<std::string> split(std::string s, std::string t)
{
    std::vector<std::string> res;
    while (1)
    {
        int pos = s.find(t);
        if (pos == -1)
        {
            res.push_back(s);
            break;
        }
        res.push_back(s.substr(0, pos));
        s = s.substr(pos + 1, s.size() - pos - 1);
    }
    return res;
}

bool FsMesh::Load2(std::string filename) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUVs;
    std::vector<glm::vec3> tempNormals;


    if (filename.find(".obj") != std::string::npos)
    {
        std::ifstream fin(filename, std::ios::in);
        if (!fin)
        {
            std::cerr << "Cannot open " << filename << std::endl;
            return false;
        }

        std::cout << "Loading OBJ file " << filename << " ..." << std::endl;

        std::string lineBuffer;
        while (std::getline(fin, lineBuffer))
        {
            std::stringstream ss(lineBuffer);
            std::string cmd;
            ss >> cmd;

            if (cmd == "v")
            {
                glm::vec3 vertex;
                int dim = 0;
                while (dim < 3 && ss >> vertex[dim])
                    dim++;

                tempVertices.push_back(vertex);
            }
            else if (cmd == "vt")
            {
                glm::vec2 uv;
                int dim = 0;
                while (dim < 2 && ss >> uv[dim])
                    dim++;

                tempUVs.push_back(uv);
            }
            else if (cmd == "vn")
            {
                glm::vec3 normal;
                int dim = 0;
                while (dim < 3 && ss >> normal[dim])
                    dim++;
                normal = glm::normalize(normal);
                tempNormals.push_back(normal);
            }
            else if (cmd == "f")
            {
                std::string faceData;
                int vertexIndex, uvIndex, normalIndex;

                while (ss >> faceData)
                {
                    std::vector<std::string> data = split(faceData, "/");

                    if (data[0].size() > 0)
                    {
                        sscanf_s(data[0].c_str(), "%d", &vertexIndex);
                        vertexIndices.push_back(vertexIndex);
                    }

                    if (data.size() >= 1)
                    {
                        // Is face format v//vn?  If data[1] is empty string then
                        // this vertex has no texture coordinate
                        if (data[1].size() > 0)
                        {
                            sscanf_s(data[1].c_str(), "%d", &uvIndex);
                            uvIndices.push_back(uvIndex);
                        }
                    }

                    if (data.size() >= 2)
                    {
                        // Does this vertex have a normal?
                        if (data[2].size() > 0)
                        {
                            sscanf_s(data[2].c_str(), "%d", &normalIndex);
                            normalIndices.push_back(normalIndex);
                        }
                    }
                }
            }
        }

        // Close the file
        fin.close();


        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            Vertex meshVertex;

            // Get the attributes using the indices

            if (tempVertices.size() > 0)
            {
                glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
                meshVertex.position = vertex;
            }

            if (tempNormals.size() > 0)
            {
                glm::vec3 normal = tempNormals[normalIndices[i] - 1];
                meshVertex.normal = normal;
            }

            if (tempUVs.size() > 0)
            {
                glm::vec2 uv = tempUVs[uvIndices[i] - 1];
                meshVertex.texCoords = uv;
            }

            mVertices.push_back(meshVertex);
        }

        // Create and initialize the buffers
        //initBuffers();
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Normals attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // Vertex Texture Coords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        // unbind to make sure other code does not change it somewhere else
        glBindVertexArray(0);

        meshLoaded = true;
        std::cout << "cargado: " << meshLoaded;
        on = true;
        return (mLoaded = true);
        

    }

    // We shouldn't get here so return failure
    return false;
}

void FsMesh::Load(std::string p)
{
    path = p;

    transform = FsTransform({ 0,0,0 }, { 0,0,0 }, { 1,1,1 });
    //material = FsMaterial();
    collider = nullptr;
    on = true;
    //logger.CreateLogger("FsMesh", "log-FsMesh");
    shader = FausEngine::FsGame::GetReference()->GetShader(0);


    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;

    //shader = std::make_shared<FsShader>(FausEngine::FsGame::GetReference()->GetShader(0));

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
                    //logger.SetName("Mesh: "+ ss.str());
                    //logger.SetMessage("Mesh can't be read. (faces)",1);
                    FausEngine::FsGame::GetReference()->SetLog("Mesh can't be read. (faces) " + path, 2);
                    return;
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

        FausEngine::FsGame::GetReference()->SetLog("Loaded mesh: "+path, 0);
        //logger.SetName("Mesh: " + ss.str());
        //logger.SetMessage("Loaded mesh. " +path, 0);

        //return meshLoaded;
    }
    else
    {
        //std::cout << "Path not found. " << path << std::endl;
        //log.Logger("Path not found.","FsMesh: ");
        meshLoaded = false;
        //logger.SetName("Mesh: " + path);
        //logger.SetMessage(" ", 1);
        FausEngine::FsGame::GetReference()->SetLog("Path not found: "+path, 2);
        //return meshLoaded;
    }

    //meshLoaded = false;
    //return meshLoaded;
}

void FsMesh::Render()
{
    if (!meshLoaded) return;

    if (on) {
    
        //auto sh = material.GetShader();
        //auto sh = shader;


        //Mesh Trasnform 
        glm::mat4 mModel(1.0f);
        mModel = glm::translate(mModel, glm::vec3(transform.position.x, transform.position.y, transform.position.z));
        mModel = glm::rotate(mModel, glm::radians<float>(transform.rotation.x), glm::vec3(1, 0, 0));
        mModel = glm::rotate(mModel, glm::radians<float>(transform.rotation.y), glm::vec3(0, 1, 0));
        mModel = glm::rotate(mModel, glm::radians<float>(transform.rotation.z), glm::vec3(0, 0, 1));
        mModel = glm::scale(mModel, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));
        glUniformMatrix4fv(shader->GetUVariableLocation(uTypeVariables::uModel), 1, GL_FALSE, glm::value_ptr(mModel));

        if (mat) {
            //Material setting
            glUniform3f(shader->GetUVariableLocation(uTypeVariables::uAmbient),
                mat->GetAmbient().x, mat->GetAmbient().y, mat->GetAmbient().z);
            glUniform3f(shader->GetUVariableLocation(uTypeVariables::uSpecular),
                mat->GetSpecular().x, mat->GetSpecular().y, mat->GetSpecular().z);
            glUniform3f(shader->GetUVariableLocation(uTypeVariables::uColor),
                mat->GetColor().x, mat->GetColor().y, mat->GetColor().z);
            glUniform1f(shader->GetUVariableLocation(uTypeVariables::uShininess), mat->GetShine());
            glUniform1i(shader->GetUVariableLocation(uTypeVariables::uTexture), 0);
            glUniform1i(shader->GetUVariableLocation(uTypeVariables::uLit), mat->GetLit());

            //Use Texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mat->GetTexture());
        }

        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        //Mesh
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,vertexElements.size()/8);
        glBindVertexArray(0);

        //glBindVertexArray(mVAO);
        //glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
        //glBindVertexArray(0);
        //std::cout << "pilot";

        //Collider---------------------------------------
        if (collider) {
            
            collider->SetBoundMax(transform.position + distanceCollider[0]);
            collider->SetBoundMin(transform.position - distanceCollider[1]);

            //basicamente tomo la PRIMERA poscion de MAX-MIN y en el eje respectivo solo sumo mas un radio
            //mientras en los otros calculo la mitad entre MAX-Min y ubico 
            auto max = distanceCollider[2];
            auto min = distanceCollider[3];
            auto pos = transform.position;
            float radio = 0.5f;

            auto right = collider->GetRight();
            right.x = pos.x + (abs(max.x) + radio);
            right.y = pos.y + ((max.y + min.y) / 2);
            right.z = pos.z + ((max.z + min.z) / 2);
            collider->SetRight(right);

            auto left = collider->GetLeft();
            left.x = pos.x - (abs(min.x) + radio);
            left.y = pos.y + ((max.y + min.y) / 2);
            left.z = pos.z + ((max.z + min.z) / 2);
            collider->SetLeft(left);

            auto up = collider->GetUp();
            up.x = pos.x + ((max.x + min.x) / 2);
            up.y = pos.y + (abs(max.y) + radio);
            up.z = pos.z + ((max.z + min.z) / 2);
            collider->SetUp(up);

            auto down = collider->GetDown();
            down.x = pos.x + ((max.x + min.x) / 2);
            down.y = pos.y - (abs(min.y) + radio);
            down.z = pos.z + ((max.z + min.z) / 2);
            collider->SetDown(down);
        }

        //shader.~shared_ptr();
    }
}

