#include"../Headers/FsLight.h"

using namespace FausEngine;

FsLight::FsLight() 
{
	ambient = FsVector3(1,1,1);
	diffuse = FsVector3(0.5f, 0.5f, 0.5f);
	specular = FsVector3(0.5f, 0.5f, 0.5f);
	on = true;
}

FsLight::FsLight(FsVector3 _ambient, FsVector3 _diffuse, FsVector3 _specular)
{
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;
	on = true;
}

//void FsLight::Load() { }
//
//void FsLight::Render() {}

std::shared_ptr<FsVector3> FsLight::GetAmbient() {
	return std::make_shared<FsVector3>(ambient);
}
std::shared_ptr<FsVector3> FsLight::GetDiffuse() {
	return std::make_shared<FsVector3>(diffuse);
}
std::shared_ptr<FsVector3> FsLight::GetSpecular() {
	return std::make_shared<FsVector3>(specular);
}
//FsVector3* FsLight::GetAmbient(){
//	return &ambient;
//}
//
//FsVector3* FsLight::GetDiffuse() {
//	return &diffuse;
//}
//
//FsVector3* FsLight::GetSpecular() {
//	return &specular;
//}

FsLight::~FsLight()
{
}