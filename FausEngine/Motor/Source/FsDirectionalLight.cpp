#include"../Headers/FsDirectionalLight.h"
#include"../Headers/FsGame.h"
#include "GL/glew.h"
using namespace FausEngine;

FsDireciontalLight:: FsDireciontalLight():FsLight() {
	direction = FsVector3(0.0f, -0.4f, -0.17f);
    //shader = FsGame::GetInstance()->GetShader(0);
	//shader.reset(FsGame::GetInstance()->GetShader(0));
}

//FsDireciontalLight::FsDireciontalLight(FsVector3 _direction, FsVector3 _ambient, FsVector3 _diffuse, FsVector3 _specular):
//	FsLight(_ambient, _diffuse, _specular)
//{
//	this->direction = _direction;
//    //this->shader = FsGame::GetInstance()->GetShader(0);
//	//shader.reset(FsGame::GetInstance()->GetShader(0));
//}

void FsDireciontalLight::Load(FsVector3 direction, FsVector3 ambient, FsVector3 diffuse, FsVector3 specular)
{
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	FausEngine::FsGame::GetReference()->LoadLight(this);
	FausEngine::FsGame::GetReference()->SetLog("Loaded directional light.",0);
	//FausEngine::FsGame::GetReference()->LoadDLight(&this);
	
	//FausEngine::FsGame::GetReference()->LoadDLight(std::make_shared<FsDireciontalLight>(this));
}



FsVector3 FsDireciontalLight::GetDirection() {
	return direction;
}

void FsDireciontalLight::SetDirection(FsVector3 vector) {
	direction = vector;
}

FsDireciontalLight::~FsDireciontalLight() 
{

}
