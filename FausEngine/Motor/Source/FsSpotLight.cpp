#include"../Headers/FsSpotLight.h"
#include"../Headers/FsGame.h"
#include <memory>

using namespace FausEngine;

FsSpotLight::FsSpotLight():FsPointLight()
{
	direction = FsVector3(0,-1,0);
	position = FsVector3(0,5,0);
}

//FsSpotLight::FsSpotLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
//	FsVector3 position, FsVector3 direction, float constant, float linear, float exponent)/*:
//	FsPointLight(ambient, diffuse, specular, position, constant, linear, exponent) */
//{
//	this->direction = direction;
//}

void FsSpotLight::Load(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
	FsVector3 position, FsVector3 direction, float constant, float linear, float exponent) {

	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->position = position;
	this->direction = direction;
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;

	FausEngine::FsGame::GetReference()->LoadLight(this);
}

void FsPointLight::SetDiffuse(FsVector3 d) {
	diffuse = d;
}

//FsVector3* FsSpotLight::GetDirection() {
//	return &direction;
//}

std::shared_ptr<FsVector3> FsSpotLight::GetDirection() {
	return std::make_shared<FsVector3>(direction);
}

FsSpotLight::~FsSpotLight()
{
}