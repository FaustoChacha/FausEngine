#ifndef ESCENARIO
#define ESCENARIO

#include"FsObject.h"
#include"UserGame.h"
#include"FsMesh.h"
#include"FsDirectionalLight.h"
#include"FsPointLight.h"
#include"FsSpotLight.h"

#include<stdio.h>
#include<string.h>
#include <iostream>
#include<cmath>

using namespace std;
using namespace FausEngine;

class Escenario4 :public FsObject
{
public:
	Escenario4();
	void Begin()override;
	void ControlFPS(float, float);
	void ControlTPS(FsTransform& targetPos, float, float);
	void Update(float, float)override;
	~Escenario4();

private:
	UserGame* gamereference;
	std::string PathGame = "../../../../UserGame/Assets/";

	FsMesh mNave, mCaja, mPiso;
	FsMesh esferaLuz1, esferaLuz2, esferaLuz3, conoLuz1, conoLuz2, conoLuz3, cuboX, cuboY, cuboZ;
	FsMesh player;
	FsDireciontalLight luzDireccional;
	FsPointLight pointLight[4];
	FsSpotLight spotlight[4];


	
};

#endif