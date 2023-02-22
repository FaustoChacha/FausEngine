#include"../Motor/Headers/FsScene.h"
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
#include"../Motor/Headers/FsImage.h"
#include"../Motor/Headers/FsLog.h"

#include"../ejemplo/Jugador.h"

#include<stdio.h>
#include<string.h>
#include <iostream>
#include<cmath>

using namespace std;
using namespace FausEngine;

class Inicio : public FsScene
{
public:
	Inicio();
	void Begin()override;
	void Update(float, float)override;
	~Inicio();

private:
	std::unique_ptr<UserGame> gameReference;
	bool* teclas;
	FsImage imgenMenu, imgMenuPress;
	FsLog log;
};



class Plataformas :public FsScene
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
	std::vector<std::shared_ptr<FsPointLight>>lucesPuntuales;

	FsMesh monedas[15];
	FsCollider collMonedas[15];
	int puntos=0;

	FsMesh plataformas[14];
	FsMaterial matPla1, matPla2, matPla3, matPla4, matMoneda;
	FsMesh complemento0;
	FsCollider collPlataformas[14];
	FsMesh refRight, refLeft;
	FsMesh colMax2, colMin2;

	FsDireciontalLight luzDireccional;
	FsSpotLight luzLinterna;
	//FsSpotLight spotlight[4];
	FsSkybox sky;

	FsText texto1, texto2, texto3;
	//std::unique_ptr<FsText> texto2;
	//FsText texto3;
	FsImage imgVidas[3];
	FsImage imgGanaste, imgPressEscape, imgPause;

	FsMesh item;
	FsMaterial matItem;
	FsCollider collItem;

	bool swCam=false;
	//bool* teclas;	                                                                                   
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

	bool colisionalguna;
};

class Test : public FsScene
{
public:
	Test();

	void Begin()override;
	void CamaraFPS(float, float);
	void ControlFPS(float, float);
	void Update(float, float)override;

	~Test();

private:


	std::unique_ptr<UserGame> gameReference;
	
	//std::unique_ptr<FsMesh> malla;
	FsMaterial matMalla, matMalla2;
	FsMesh malla;
	FsSkybox sky;
	FsDireciontalLight luzDireccional;

};








