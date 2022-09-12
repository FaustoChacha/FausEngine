#ifndef ESCENARIO
#define ESCENARIO

#include"FsObject.h"
#include"FsMaterial.h"
#include"FsMaths.h"
#include"UserGame.h"
#include"FsMesh.h"
#include"FsDirectionalLight.h"
#include"FsPointLight.h"
#include"FsSpotLight.h"
#include"FsSkybox.h"
#include"FsCollider.h"
#include"FsText.h"

//#include<btBulletDynamicsCommon.h>//BT.........

#include<stdio.h>
#include<string.h>
#include <iostream>
#include<cmath>

using namespace std;
using namespace FausEngine;



class Plataformas :public FsObject
{
public:
	Plataformas();
	void Begin()override;
	void ControlFPS(float, float);
	void ControlTPS(FsTransform& targetPos, float, float);
	void Control2D(FsTransform&, float, float);

	void Update(float, float)override;
	~Plataformas();

private:
	UserGame* gamereference;

	FsMesh player, mLuzPlayer;
	FsVector3 colorVida;
	FsCollider collPlayer;
	FsMesh colMax1, colMin1;
	FsVector3 posInicialPlayer;
	int vidasPlayer = 3;
	FsMesh monedas[15];
	FsCollider collMonedas[15];
	int puntos = 0;

	FsMesh plataformas[14];
	FsMesh complemento0;
	FsCollider collPlataformas[14];
	FsMesh refRight, refLeft;
	FsMesh colMax2, colMin2;

	FsDireciontalLight luzDireccional;
	FsPointLight pointLight[4];
	FsSpotLight spotlight[4];
	FsSkybox sky;

	bool swCam = false;
	bool* teclas;
	int indexCollision = 0;
	int indexCollisionMOnedas = 0;

	FsText texto1, texto2, texto3;

	bool jump = false;
	float jumpLap;
	int contadorTeclaEspacio = 0;
	float moveLinear = 0;
	bool iniciar = false;
	bool moveOsci = false;
	float movePlataform = 0;
};


#endif