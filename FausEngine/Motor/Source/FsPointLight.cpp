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

//FsPointLight::FsPointLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
//	FsVector3 position, float constant, float linear, float exponent) :FsLight(ambient, diffuse, specular) 
//{
//	this->position = position;
//	this->constant = constant;
//	this->linear = linear;
//	this->exponent = exponent;
//	//*pointlightReference=*this;
//	//pointlightReference = std::make_shared<FsPointLight>(*this);
//	//pointlightReference.reset(this);
//}

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
	
	//std::shared_ptr< FsPointLight > self = shared_from_this();
	//FausEngine::FsGame::GetReference()->LoadDLight(self);
	//FausEngine::FsGame::GetReference()->LoadDLight(pointlightReference);
}

//FsVector3* FsPointLight::GetPosition() 
//{
//	return &position;
//}

std::shared_ptr<FsVector3> FsPointLight::GetPosition()
{
	return std::make_shared<FsVector3>(position);
}

//float* FsPointLight::GetConstant() 
//{
//	return &constant;
//}
//
//float* FsPointLight::GetLinear()
//{
//	return &linear;
//}
//
//float* FsPointLight::GetExponent() 
//{
//	return &exponent;
//}


std::shared_ptr<float> FsPointLight::GetConstant() {
	return std::make_shared<float>(constant);
}

std::shared_ptr<float> FsPointLight::GetLinear() {
	return std::make_shared<float>(linear);
}

std::shared_ptr<float> FsPointLight::GetExponent() {
	return std::make_shared<float>(exponent);
}

void FsPointLight::SetLinear(float l) {
	linear = l;
}

void FsPointLight::SetPosition(FsVector3 p) {
	position = p;
}

FsPointLight::~FsPointLight()
{
}