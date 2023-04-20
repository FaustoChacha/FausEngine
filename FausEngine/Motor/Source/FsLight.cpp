#include"../Headers/FsLight.h"

using namespace FausEngine;

FsLight::FsLight() 
{
	ambient = FsVector3(1,1,1);
	diffuse = FsVector3(0.5f, 0.5f, 0.5f);
	specular = FsVector3(0.5f, 0.5f, 0.5f);
	active = true;
}

void FsLight::SetActive(bool a) {
	active = a;
}

void FsLight::SetAmbient(FsVector3 amb) {
	ambient = amb;
}

void FsLight::SetDiffuse(FsVector3 dif) {
	diffuse = dif;
}

void FsLight::SetSpecular(FsVector3 spe) {
	specular = spe;
}

FsVector3 FsLight::GetAmbient() {
	return ambient;
}

FsVector3 FsLight::GetDiffuse() {
	return diffuse;
}

FsVector3 FsLight::GetSpecular() {
	return specular;
}

bool FsLight::GetActive() {
	return active;
}

FsLight::~FsLight()
{
}