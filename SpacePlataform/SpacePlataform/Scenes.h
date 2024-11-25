#include"FausEngine/FsScene.h"
#include"FausEngine/FsSkybox.h"
#include"FausEngine/FsImage.h"

#include"SpacePlataform.h"
#include"Player.h"
#include"Plataforms.h"
#include"Coins.h"
#include"Items.h"
#include"Ui.h"
#include"Ilumination.h"

#include <iostream>

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
	unique_ptr<SpacePlataform> gameReference;
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
	unique_ptr<SpacePlataform> gameReference;
	Player player;
	Plataforms plataforms;
	Coins coins;
	Items item;
	Ui ui;
	Ilumination ilumination;
	FsSkybox sky;
	bool pause;
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


	unique_ptr<SpacePlataform> gR;
	
	FsMaterial matMalla, matMalla2;
	FsMesh malla;
	FsSkybox sky;
	FsDireciontalLight luzDireccional;

};








