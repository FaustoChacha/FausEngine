#include"../Motor/Headers/FsScene.h"
#include"../Motor/Headers/FsMaterial.h"
#include"../Motor/Headers/FsMaths.h"
#include"../ejemplo/SpacePlataform.h"
#include"../Motor/Headers/FsMesh.h"
#include"../Motor/Headers/FsDirectionalLight.h"
#include"../Motor/Headers/FsPointLight.h"
#include"../Motor/Headers/FsSpotLight.h"
#include"../Motor/Headers/FsSkybox.h"
#include"../Motor/Headers/FsCollider.h"
#include"../Motor/Headers/FsText.h"
#include"../Motor/Headers/FsImage.h"

#include"../ejemplo/Player.h"
#include"../ejemplo/Plataforms.h"
#include"../ejemplo/Coins.h"

#include<stdio.h>
#include<string.h>
#include <iostream>
#include<cmath>

using namespace std;
using namespace FausEngine;

class Intro : public FsScene
{
public:
	Intro();
	void Begin()override;
	void Update(float, float)override;
	~Intro();

private:
	std::unique_ptr<SpacePlataform> gameReference;
	FsImage menuImage, buttonPressImage;
};



class Level1 :public FsScene
{
public: 
	Level1();
	void Begin()override;
	void Update(float, float)override;

	~Level1();

private:
	std::unique_ptr<SpacePlataform> gR;
	Player jugador;
	Plataforms plataforms;
	Coins coins;

	FsSkybox sky;
	bool pause;

	//luces
	FsDireciontalLight directionalLight;
	FsSpotLight spotLight;
	vector<shared_ptr<FsPointLight>>pointLights;

	//texto e imagenes
	FsText scoretext;
	FsImage lifeImages[3];
	FsImage winImage, finishImage, pauseImage;

	//item
	FsMesh item;
	FsMaterial matItem;
	FsCollider collItem;

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


	std::unique_ptr<SpacePlataform> gR;
	
	FsMaterial matMalla, matMalla2;
	FsMesh malla;
	FsSkybox sky;
	FsDireciontalLight luzDireccional;

};








