#include"../MotorGrafico/Headers/FsObject.h"
#include"../MotorGrafico/Headers/FsMaterial.h"
#include"../MotorGrafico/Headers/FsMaths.h"
#include"../ejemplo/UserGame.h"
#include"../MotorGrafico/Headers/FsMesh.h"
#include"../MotorGrafico/Headers/FsDirectionalLight.h"
#include"../MotorGrafico/Headers/FsPointLight.h"
#include"../MotorGrafico/Headers/FsSpotLight.h"

#include<btBulletDynamicsCommon.h>//BT.........

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
	void ControlTPS(FsTransform &targetPos,float, float);
	void Update(float, float)override;
	~Escenario4();

private:
	UserGame* gamereference;
	std::string pathEngine = "../../../../MotorGrafico/";
	std::string PathGame = "../../../../ejemplo/";
	
	FsMesh mNave, mCaja, mPiso;
	FsMesh esferaLuz1, esferaLuz2, esferaLuz3, conoLuz1, conoLuz2, conoLuz3, cuboX, cuboY, cuboZ;
	FsMesh player;
	FsDireciontalLight luzDireccional;
	FsPointLight pointLight[4];
	FsSpotLight spotlight[4];

};



