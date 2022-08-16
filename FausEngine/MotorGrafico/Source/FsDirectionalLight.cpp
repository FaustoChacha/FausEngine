#include"../Headers/FsDirectionalLight.h"
#include"../Headers/FsGame.h"

using namespace FausEngine;

FsDireciontalLight:: FsDireciontalLight():FsLight() {
	direction = FsVector3(0.0f, -0.4f, -0.17f);
}

FsDireciontalLight::FsDireciontalLight(FsVector3 _direction, FsVector3 _ambient, FsVector3 _diffuse, FsVector3 _specular):
	FsLight(_ambient, _diffuse, _specular)
{
	this->direction = _direction;
}

void FsDireciontalLight::Load() 
{
	FausEngine::FsGame::GetInstance()->LoadLight(this);
}

FsVector3* FsDireciontalLight::GetDirection() {
	return &direction;
}

void FsDireciontalLight::SetDirection(FsVector3 vector) {
	direction = vector;
}

FsDireciontalLight::~FsDireciontalLight() 
{

}
