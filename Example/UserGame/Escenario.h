#ifndef ESCENARIO
#define ESCENARIO

#include"FausEngine/FsObject.h"
#include"FausEngine/FsMesh.h"
#include"FausEngine/FsTexture.h"
#include"FausEngine/FsLight.h"
#include"FausEngine/FsMaterial.h"
#include"FausEngine/FsDirectionalLight.h"
#include"FausEngine/FsPointLight.h"
#include"FausEngine/FsMaths.h"
#include"FausEngine/FsSpotLight.h"
#include"FausEngine/FsModel.h"
#include"FausEngine/FsShader.h"
#include "FausEngine/FsSkybox.h"

#include"UserGame.h"

#include<stdio.h>
#include<string.h>
#include <iostream>

using namespace std;
using namespace FausEngine;

class Escenario1 : public FsObject
{
public:
	Escenario1();
	void Begin() override;
	void Update(float, float) override;

	void CreacionLuces();
	void CreacionMallas();
	void ControlesJugador(float, float);
	void Mover(FsPointLight*);
	void Mover(FsModel*);
	void mod(float);

	~Escenario1();

private:
	UserGame* gamereference;
	std::string pathEngine = "../../../../UserGame/FausEngine/";
	std::string PathGame = "../../../../UserGame/Assets/";

	FsDirectionalLight mainLight;
	FsPointLight pointLights[5];
	FsSpotLight spotLights[5];

	FsModel cuboPiso, nave, baseNave,
		esferaSpot1, cubo1,
		esferaPoint0;

	bool swLinternaNave,
		swDespegue = false,
		swLinterna;
	bool swLinternasCostados;
	bool swPuntualesBase;
	bool swPuntualMediaBase;
	float cont = 0;
	float velocidadNave = 0;

	FsSkybox skybox;
};

class Escenario2 : public FsObject
{
public:
	Escenario2();
	void Begin()override;
	void CrearMallas();
	void CrearLuces();
	void ControlesJugador(float, float);
	void Mover(FsPointLight*);
	void Mover(FsModel*);
	void Update(float, float)override;
	~Escenario2();

private:
	UserGame* gamereference;
	std::string pathEngine = "../../../../MotorGrafico/";
	std::string PathGame = "../../../../ejemplo/";

	FsDirectionalLight mainLight;
	FsPointLight pointLights[5];
	FsSpotLight spotLights[5];

	FsModel cuboPiso, nave, baseNave,
		esferaSpot1, cubo1,
		tierra;

	bool swLinternaNave,
		swDespegue = false,
		swLinterna;
	bool swLinternasCostados;
	bool swPuntualesBase;
	bool swPuntualMediaBase;

	float velocidadNave = 0;
	float cont = 0;
	FsSkybox skybox;

};

#endif