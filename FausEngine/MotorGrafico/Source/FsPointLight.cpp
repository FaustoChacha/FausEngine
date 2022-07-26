#include"../Headers/FsPointLight.h"
#include"../Headers/FsGame.h"
using namespace FausEngine;

FsPointLight::FsPointLight() : FsLight()
{
	position = FsVector3(0,3,0);
	constant = 1.0f;
	linear = 0.22f;
	exponent = 0.2f;
}

FsPointLight::FsPointLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
	FsVector3 position, float constant, float linear, float exponent) :FsLight(ambient, diffuse, specular) 
{
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;
}

void FsPointLight::Load() {
	FausEngine::FsGame::GetSelfReference()->LoadLight(this);
}

FsVector3* FsPointLight::GetPosition() 
{
	return &position;
}

float* FsPointLight::GetConstant() 
{
	return &constant;
}

float* FsPointLight::GetLinear()
{
	return &linear;
}

float* FsPointLight::GetExponent() 
{
	return &exponent;
}

FsPointLight::~FsPointLight()
{
}