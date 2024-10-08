#include"../Motor/Headers/FsScene.h"
#include"../ejemplo/SpacePlataform.h"
#include"../Motor/Headers/FsSkybox.h"
#include"../Motor/Headers/FsImage.h"

#include"../ejemplo/Player.h"
#include"../ejemplo/Plataforms.h"
#include"../ejemplo/Coins.h"
#include"../ejemplo/Items.h"
#include"../ejemplo/Ui.h"
#include"../ejemplo/Ilumination.h"

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
	void Control2D(float, float);
	void Update(float, float)override;
	~Test();

private:
	FsText texto;
	FsMaterial playerMaterial, playerMaterial2;
	unique_ptr<SpacePlataform> gR;
	FsCollider playerCollider;
	FsMesh playerMesh, playerMesh2;
	FsSkybox sky;
	FsDireciontalLight luzDireccional;
	FsCollider collider, collider2;

	FsMesh planeMesh, plataformaMesh;
	FsMaterial planeMaterial, plataformaMaterial;
};








