#include"Scenes.h"

Intro::Intro()
{
	gameReference.reset(new SpacePlataform());
}

void Intro::Begin() {
	menuImage.Load("Textures/menu.png");
	menuImage.SetScale({ 2,-2,2 });

	buttonPressImage.Load("Textures/PressSpace.png");
	buttonPressImage.SetPosition({ 0,-0.65f,0 });
	buttonPressImage.SetScale({ 1,0.25f,1 });
}

void Intro::Update(float deltatime, float time) {
	if ((int)time % 2 == 0) {
		buttonPressImage.Render();
	}
	menuImage.Render();

	if (gameReference->GetKeyPress(Keys::SPACE)) { //space
		gameReference->SetScene(1);
	}

}

Intro::~Intro()
{
}

//---------------------------------------PLATAFORMAS---------------------------------------------------

Level1::Level1()
{
	gameReference.reset(new SpacePlataform());
	pause = false;
}

Level1::~Level1()
{
}


void Level1::Begin() {
	
	player.Init();
	plataforms.Init();
	coins.Init();
	item.Init();
	ui.Init();
	ilumination.Init();

	//=================SKYBOX======================
	std::vector<std::string> caras = {
	"Textures/Sk_GalaxyRt.png",
	"Textures/Sk_GalaxyLf.png",
	"Textures/Sk_GalaxyUp.png",
	"Textures/Sk_GalaxyDn.png",
	"Textures/Sk_GalaxyBk.png",
	"Textures/Sk_GalaxyFt.png"
	};
	sky.Load(caras);
}

void Level1::Update(float deltaTime, float time) {

	plataforms.Tick(deltaTime, time, player, pause);
	coins.Tick(deltaTime, time, player, pause);
	player.Tick(pause, deltaTime, time, plataforms.PlayertoPlataformCollision());
	item.Tick(deltaTime, time,player, pause);
	ui.Tick(plataforms, player, coins, pause);

	if (gameReference->GetKeyPress(Keys::P)) {//p
		pause = !pause;
		gameReference->SetKeyRelease(Keys::P);
	}

}

//=============================== Test ================================

Test::Test() {
	gR.reset(new SpacePlataform());
}

void Test::Begin() {


	//=================SKYBOX======================


	//LUZCES================
	luzDireccional.Load(
		FsVector3(-0.9f, -1, 0.2f),
		FsVector3(5, 5, 5),
		FsVector3(0.9f, 0.9f, 0.9f),
		FsVector3(0.5f, 0.5f, 0.5f));
	//luzDireccional.Load();

	std::vector<std::string> caras = {
	"Textures/Sk_GalaxyRt.png",
	"Textures/Sk_GalaxyLf.png",
	"Textures/Sk_GalaxyUp.png",
	"Textures/Sk_GalaxyDn.png",
	"Textures/Sk_GalaxyBk.png",
	"Textures/Sk_GalaxyFt.png"
	};
	sky.Load(caras);
	//sky.Load();

	//jugador.Init(colisionalguna);

	//malla = FsMesh("Models/player-ball.obj");
	//malla.LoadMesh();
	//malla.material.type = TypeMaterial::Unlit;
	//malla.material.color = { 1,1,1 };
	//malla.transform.scale = { 0.5f,0.5f,0.5f };
	//std::shared_ptr<FsMesh> malla(new FsMesh("Models/player-ball.obj"));
	
	//malla.reset(new FsMesh("Models/player-ball.obj"));
	//malla->material.LoadTexture("Textures/player-ball.png");
	//malla->Load();
	//malla->material.type = TypeMaterial::Lit;
	//malla->material.color = { 1,1,1 };
	//malla->transform.scale = { 0.5f,0.5f,0.5f };

	matMalla.Load({0,0,1});
	
	matMalla2.Load({1,1,1});
	//matMalla.Load(/*{ 0.5f,0.5f ,0.5f }*/{1,1,1}, { 0.1f, 0.1f, 0.1f }, { 1.0f, 1.0f, 1.0f }, 1, "Textures/player-ball.png", false);
	malla.Load("Models/player-ball.obj");
	//malla.material = matMalla;
	malla.SetMaterial(matMalla);
	
}

void Test::CamaraFPS(float dt, float t)
{
	auto cam = gR->GetCamera();
	float velocidad = 0.2f;

	auto yaw = cam->GetYaw();
	yaw -= FsVector3::toRadians(gR->GetMouseX()) * velocidad;
	cam->SetYaw(yaw);

	auto pitch = cam->GetPitch();
	pitch += FsVector3::toRadians(gR->GetMouseY()) * velocidad;
	cam->SetPitch(FsVector3::Clamp(pitch, -3.14f / 2, 3.14f / 2));

	FsVector3 fordwardDir;
	fordwardDir.x = cos(cam->GetPitch()) * sin(cam->GetYaw());
	fordwardDir.y = sin(cam->GetPitch());
	fordwardDir.z = cos(cam->GetPitch()) * cos(cam->GetYaw());
	cam->SetForward(fordwardDir);
	FsVector3 rightDir = { -fordwardDir.z,0 ,fordwardDir.x }; //tambien un producto cruz con {0,1,0} o WorldUp
	cam->SetRight(rightDir);
	FsVector3 upDir = FsVector3::Cross(cam->GetRight(), cam->GetForward());
	cam->SetUp(upDir);

	cam->SetTarget(cam->GetPosition() + cam->GetForward());
}

void Test::ControlFPS(float dt, float time) {

	//CamaraFPS(dt, time);

	//Teclado
	float velocidad = 3.0f;
	if (gR->GetKeyPress(Keys::SPACE)) {//space
		velocidad = 15;
	}
	if (gR->GetKeyPress(Keys::W)) { // tecla W
		FsVector3 posicion = gR->GetCamera()->GetPosition() += gR->GetCamera()->GetForward() * dt * velocidad;
		gR->GetCamera()->SetPosition(posicion);
	}
	if (gR->GetKeyPress(Keys::S)) { // tecla S
		FsVector3 posicion = gR->GetCamera()->GetPosition() -= gR->GetCamera()->GetForward() * dt * velocidad;
		gR->GetCamera()->SetPosition(posicion);
	}
	if (gR->GetKeyPress(Keys::A)) { // tecla A
		FsVector3 posicion = gR->GetCamera()->GetPosition() -= gR->GetCamera()->GetRight() * dt * velocidad;
		gR->GetCamera()->SetPosition(posicion);
	}
	if (gR->GetKeyPress(Keys::D)) { // tecla D
		FsVector3 posicion = gR->GetCamera()->GetPosition() += gR->GetCamera()->GetRight() * dt * velocidad;
		gR->GetCamera()->SetPosition(posicion);
	}
	if (gR->GetKeyPress(Keys::E)) { // tecla E
		FsVector3 posicion = gR->GetCamera()->GetPosition() += gR->GetCamera()->GetUp() * dt * velocidad;
		gR->GetCamera()->SetPosition(posicion);
	}
	if (gR->GetKeyPress(Keys::Q)) { // tecla Q
		FsVector3 posicion = gR->GetCamera()->GetPosition() -= gR->GetCamera()->GetUp() * dt * velocidad;
		gR->GetCamera()->SetPosition(posicion);
	}
}

void Test::Update(float deltaTime, float time) {
	ControlFPS(deltaTime, time);
	
	//malla.transform.position = { 0,0,0 };
	malla.Render();
	
}

Test::~Test() {}