#include"../Headers/FsSpotLight.h"
#include"../Headers/FsGame.h"

using namespace FausEngine;

FsSpotLight::FsSpotLight():FsPointLight()
{
	direction = FsVector3(0,-1,0);
	position = FsVector3(0,5,0);
}

FsSpotLight::FsSpotLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
	FsVector3 position, FsVector3 direction, float constant, float linear, float exponent):
	FsPointLight(ambient, diffuse, specular, position, constant, linear, exponent) 
{
	this->direction = direction;
}

void FsSpotLight::Load() {
	FausEngine::FsGame::GetSelfReference()->LoadLight(this);
}

FsVector3* FsSpotLight::GetDirection() {
	return &direction;
}

FsSpotLight::~FsSpotLight()
{
}