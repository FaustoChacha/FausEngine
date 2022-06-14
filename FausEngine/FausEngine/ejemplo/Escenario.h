#include"../MotorGrafico/Headers/FsObject.h"
//#include"../MotorGrafico/Headers/FsMesh.h"
//#include"../MotorGrafico/Headers/FsTexture.h"
//#include"../MotorGrafico/Headers/FsLight.h"
//#include"../MotorGrafico/Headers/FsMaterial.h"
//#include"../MotorGrafico/Headers/FsDirectionalLight.h"
//#include"../MotorGrafico/Headers/FsPointLight.h"
#include"../MotorGrafico/Headers/FsMaths.h"
//#include"../MotorGrafico/Headers/Window.h"
//#include"../MotorGrafico/Headers/FsSpotLight.h"
//#include"../MotorGrafico/Headers/FsModel.h"
#include"../ejemplo/UserGame.h"
//#include"../MotorGrafico/Headers/FsShader.h"
//#include "../MotorGrafico/Headers/FsSkybox.h"

#include<btBulletDynamicsCommon.h>//BT.........

#include<stdio.h>
#include<string.h>
#include <iostream>

using namespace std;
using namespace FausEngine;

//class Escenario1 : public FsObject
//{
//public:
//	Escenario1();
//	void Begin() override;
//	void Update(float, float) override;
//
//	void CreacionLuces();
//	void CreacionMallas();
//	void ControlesJugador(float, float);
//	void Mover(FsPointLight*);
//	void Mover(FsModel*);
//	void mod(float);
//
//	~Escenario1();
//
//private:
//	UserGame* gamereference;
//	std::string pathEngine = "../../../../MotorGrafico/";
//	std::string PathGame = "../../../../ejemplo/";
//
//	FsDirectionalLight mainLight;
//	FsPointLight pointLights[5];
//	FsSpotLight spotLights[5];
//
//	FsModel cuboPiso, nave, baseNave, 
//		esferaSpot1, cubo1, 
//		esferaPoint0;
//
//	bool swLinternaNave, 
//		swDespegue=false,
//		swLinterna;
//	bool swLinternasCostados;
//	bool swPuntualesBase;
//	bool swPuntualMediaBase;
//	float cont = 0;
//	float velocidadNave=0;
//
//	FsSkybox skybox;
//};
//
//class Escenario2 : public FsObject
//{
//public:
//		Escenario2();
//		void Begin()override;
//		void CrearMallas();
//		void CrearLuces();
//		void ControlesJugador(float, float);
//		void Mover(FsPointLight*);
//		void Mover(FsModel*);
//		void Update(float, float)override;
//		~Escenario2();
//	
//private:
//	UserGame* gamereference;
//	std::string pathEngine = "../../../../MotorGrafico/";
//	std::string PathGame = "../../../../ejemplo/";
//
//	FsDirectionalLight mainLight;
//	FsPointLight pointLights[5];
//	FsSpotLight spotLights[5];
//
//	FsModel cuboPiso, nave, baseNave,
//		esferaSpot1, cubo1,
//		tierra;
//
//	bool swLinternaNave,
//		swDespegue = false,
//		swLinterna;
//	bool swLinternasCostados;
//	bool swPuntualesBase;
//	bool swPuntualMediaBase;
//	
//	float velocidadNave = 0;
//	float cont = 0;
//	FsSkybox skybox;
//
//};

class Escenario3 : public FsObject
{
public:
	Escenario3();
	void Begin()override;
	void ControlesJugador(float, float);
	void Update(float, float)override;

	~Escenario3();

private:
	UserGame* gamereference;
	std::string pathEngine = "../../../../MotorGrafico/";
	std::string PathGame = "../../../../ejemplo/";

	//FsModel cuboPiso, sphere, sphere2;

	btDynamicsWorld* dynamicsWorld; //BT.........

};



