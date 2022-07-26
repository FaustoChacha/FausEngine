#include"../Headers/FsLight.h"

using namespace FausEngine;

FsLight::FsLight() 
{
	ambient = FsVector3(1,1,1);
	diffuse = FsVector3(0.5f, 0.5f, 0.5f);
	specular = FsVector3(0.5f, 0.5f, 0.5f);
}

FsLight::FsLight(FsVector3 _ambient, FsVector3 _diffuse, FsVector3 _specular)
{
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;
}

void FsLight::Load() { }

FsVector3* FsLight::GetAmbient(){
	return &ambient;
}

FsVector3* FsLight::GetDiffuse() {
	return &diffuse;
}

FsVector3* FsLight::GetSpecular() {
	return &specular;
}

FsLight::~FsLight()
{
}