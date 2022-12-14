#include"../Motor/Headers/FsObject.h"
#include"../Motor/Headers/FsMaterial.h"
#include"../Motor/Headers/FsMaths.h"
#include"../ejemplo/UserGame.h"
#include"../Motor/Headers/FsMesh.h"
#include"../Motor/Headers/FsDirectionalLight.h"
#include"../Motor/Headers/FsPointLight.h"
#include"../Motor/Headers/FsSpotLight.h"
#include"../Motor/Headers/FsSkybox.h"
#include"../Motor/Headers/FsCollider.h"
#include"../Motor/Headers/FsText.h"
#include"../Motor/Headers/FsImage2D.h"
#include"../Motor/Headers/FsLog.h"

#include"../ejemplo/Jugador.h"

#include<stdio.h>
#include<string.h>
#include <iostream>
#include<cmath>

using namespace std;
using namespace FausEngine;

class Inicio : public FsObject
{
public:
	Inicio();
	void Begin()override;
	void Update(float, float)override;
	~Inicio();

private:
	std::unique_ptr<UserGame> gameReference;
	bool* teclas;
	FsImage2D imgenMenu, imgMenuPress;
};



class Plataformas :public FsObject 
{
public: 
	Plataformas();
	void Begin()override;

	void Update(float, float)override;
	~Plataformas();

private:
	std::unique_ptr<UserGame> gameReference;
	//UserGame* gameReference;
	Jugador jugador;

	FsMesh monedas[15];
	FsCollider collMonedas[15];
	int puntos=0;

	FsMesh plataformas[14];
	FsMesh complemento0;
	FsCollider collPlataformas[14];
	FsMesh refRight, refLeft;
	FsMesh colMax2, colMin2;

	FsDireciontalLight luzDireccional;
	FsSpotLight spotlight[4];
	FsSkybox sky;

	FsText texto1, texto2, texto3;
	FsImage2D imgVidas[3];
	FsImage2D imgGanaste, imgPressEscape, imgPause;

	FsMesh item;
	FsCollider collItem;

	bool swCam=false;
	bool* teclas;
	int indexCollision=0;
	int indexCollisionMOnedas=0;

	bool jump=false;
	float jumpLap;
	int powerJump = 22;
	float timePowerJump = 0.0f;
	FsVector3 colorPower = {1,1,1};
	int contadorTeclaEspacio=0;
	float moveLinear = 0;
	//bool iniciar=false;
	bool moveOsci=false;
	float movePlataform=0;

	bool pausa = false;
	FsLog log, log2;

	bool colisionalguna;
};






