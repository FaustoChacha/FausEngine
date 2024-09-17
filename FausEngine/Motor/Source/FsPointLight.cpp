#include"../Headers/FsPointLight.h"
#include"../Headers/FsGame.h"
using namespace FausEngine;


//std::shared_ptr<FsPointLight> pointlightReference(new FsPointLight);

FsPointLight::FsPointLight() : FsLight()
{
	position = FsVector3(0,3,0);
	constant = 1.0f;
	linear = 0.22f;
	exponent = 0.2f;
}

void FsPointLight::Load(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
	FsVector3 position, float constant, float linear, float exponent) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;
	//FausEngine::FsGame::GetReference()->LoadLight(std::shared_ptr<FsPointLight>(this));
	//FausEngine::FsGame::GetReference()->LoadDLight(std::make_shared<FsPointLight>(*this));
	//FausEngine::FsGame::GetReference()->LoadRLight(*this);
	FausEngine::FsGame::GetReference()->LoadLight(this);
	FausEngine::FsGame::GetReference()->SetLog("Loaded pointlight.", 0);
	//std::shared_ptr< FsPointLight > self = shared_from_this();
	//FausEngine::FsGame::GetReference()->LoadDLight(self);
	//FausEngine::FsGame::GetReference()->LoadDLight(pointlightReference);
}


FsVector3 FsPointLight::GetPosition()
{
	return position;
}

float FsPointLight::GetConstant() {
	return constant;
}

float FsPointLight::GetLinear() {
	return linear;
}

float FsPointLight::GetExponent() {
	return exponent;
}

void FsPointLight::SetPosition(FsVector3 p) {
	position = p;
}

void FsPointLight::SetConstant(float c) {
	constant = c;
}

void FsPointLight::SetLinear(float l) {
	linear = l;
}

void FsPointLight::SetExponent(float e) {
	exponent = e;
}



FsPointLight::~FsPointLight()
{
}