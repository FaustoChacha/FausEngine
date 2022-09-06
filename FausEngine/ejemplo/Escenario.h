#include"../MotorGrafico/Headers/FsObject.h"
#include"../MotorGrafico/Headers/FsMaterial.h"
#include"../MotorGrafico/Headers/FsMaths.h"
#include"../ejemplo/UserGame.h"
#include"../MotorGrafico/Headers/FsMesh.h"
#include"../MotorGrafico/Headers/FsDirectionalLight.h"
#include"../MotorGrafico/Headers/FsPointLight.h"
#include"../MotorGrafico/Headers/FsSpotLight.h"
#include"../MotorGrafico/Headers/FsSkybox.h"
#include"../MotorGrafico/Headers/FsCollider.h"
#include"../MotorGrafico/Headers/FsText.h"

//#include<btBulletDynamicsCommon.h>//BT.........

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
	void Control2D(FsTransform&, float, float);

	void Update(float, float)override;
	~Escenario4();

private:
	UserGame* gamereference;
	
	FsMesh mNave, mCaja, mPiso, mCaja2, mCaja3;
	FsMesh esferaLuz1, esferaLuz2, esferaLuz3, conoLuz1, conoLuz2, conoLuz3, cuboX, cuboY, cuboZ;
	FsMesh player;

	FsMesh colMax1, colMin1;
	FsMesh colMax2, colMin2;
	FsMesh colMax3, colMin3;
	FsCollider collPlayer, collCaja[3];

	FsDireciontalLight luzDireccional;
	FsPointLight pointLight[4];
	FsSpotLight spotlight[4];
	FsSkybox sky;

	bool swCam=false;
	bool colisiones[4];
	bool* teclas;
	int indexCollision;

	FsText texto1, texto2;

	bool jump=false;
	float jumpLap;
};



