#include"Scenes.h"
#include"GL/glew.h"
#include"glm/gtc/type_ptr.hpp"

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

void Test::Control2D(float dt, float t) {
	auto cam = gR->GetCamera();

	FsVector3 pos = { playerMesh.GetTransform().position.x, 0, -12 };
	cam->SetPosition(pos);
	//cam->SetTarget(mallaJugador.transform.position);
	cam->SetTarget(playerMesh.GetTransform().position);

	if (gR->GetKeyPress(Keys::D)) { // D
		playerMesh.SetRotation({ playerMesh.GetTransform().rotation.x,
			playerMesh.GetTransform().rotation.y - 0.35f,
			playerMesh.GetTransform().rotation.z }); //animacion
		playerMesh.SetPosition({ playerMesh.GetTransform().position.x - 5 * dt,
			playerMesh.GetTransform().position.y,
			playerMesh.GetTransform().position.z });

	}

	if (gR->GetKeyPress(Keys::A)) { //A
		playerMesh.SetRotation({ playerMesh.GetTransform().rotation.x,
			playerMesh.GetTransform().rotation.y + 0.35f,
			playerMesh.GetTransform().rotation.z }); //animacion
		playerMesh.SetPosition({ playerMesh.GetTransform().position.x + 5 * dt,
			playerMesh.GetTransform().position.y,
			playerMesh.GetTransform().position.z });

	}

	if(gR->GetKeyPress(Keys::W)){
		playerMesh.SetPosition({ playerMesh.GetTransform().position.x ,
			playerMesh.GetTransform().position.y + 5 * dt,
			playerMesh.GetTransform().position.z });
	}

	if (gR->GetKeyPress(Keys::S)) {
		playerMesh.SetPosition({ playerMesh.GetTransform().position.x,
			playerMesh.GetTransform().position.y - 5 * dt,
			playerMesh.GetTransform().position.z });
	}


}

void Test::Begin() {


	//=================SKYBOX======================
	//gR.get()->GetCamera().get()->SetPosition(0,0,);

	//LUZCES================
	luzDireccional.Load(
		FsVector3(0.0f, -1.0f, 0.45f),
		FsVector3(1.0f, 1.2f, 1.2f),
		FsVector3(1.0f, 1.0f, 1.0f),
		FsVector3(1.0f, 1.0f, 1.0f));


	std::vector<std::string> caras = {
	"Textures/Sk_GalaxyRt.png",
	"Textures/Sk_GalaxyLf.png",
	"Textures/Sk_GalaxyUp.png",
	"Textures/Sk_GalaxyDn.png",
	"Textures/Sk_GalaxyBk.png",
	"Textures/Sk_GalaxyFt.png"
	};
	sky.Load(caras);
	sky.SetActive(false);
	sky.SetColour({ 1.0,1.0,1.0 });
	gR->SetSkybox(sky);

	//playerMesh.Load("Models/player-ball.obj");
	playerMesh.Load("Models/fSphere.obj");
		//mallaJugador.Load();
	//playerMaterial.Load({ 1.1f, 1.1f, 1.1f }, { 1.5f, 1.5f, 1.5f }, { 0.9f,1.0f,0.9f }, 0.5f, "Textures/player-ball.png", false);
	//playerMaterial.Load(
	//	{ 1.1f, 1.1f, 1.1f }, 
	//	{ 0.3, 0.3, 0.3 }, 
	//	{ 1.8f, 1.8f, 1.8f }, 
	//	100.0f, "Textures/player-ball.png", false);
	playerMaterial.SetColor({ 1,1,1 });
	playerMaterial.Load(
		{0.1f, 0.1f, 0.1f },
		{ 0.3, 0.3, 0.3 },
		{ 0.8f, 0.8f, 0.8f },
		32, "Textures/barrel_diffuse.png");
	//playerMaterial.SetBind(true);

	playerMesh.SetTransform({ { 0,0,0 }, {0,0,0},{0.8f,0.8f,0.8f} });
	playerMesh.SetMaterial(playerMaterial);
	collider.SetBoundMax({ 0.6f,0.75f,0.75f });
	collider.SetBoundMin({ -0.6f, -0.8f, -0.75f });
	playerMesh.SetCollider(collider);

	/*collider2 = collider;
	playerMesh2.Load("Models/player-ball.obj");
	playerMesh2.SetCollider(collider2);
	playerMaterial2.Load({1,0,1});
	playerMesh2.SetMaterial(playerMaterial2);
	playerMesh2.SetPosition({-2,0,0});

	planeMesh.Load("Models/fPlane.obj");
	planeMaterial.Load({ 0.1f, 0.1f, 0.1f }, { 0.0, 0.0, 0.0 }, { 0.8f, 0.8f, 0.8f }, 32.0f, "Textures/PisoArena.png", true);
	planeMesh.SetMaterial(planeMaterial);*/
	texto.Load("Fonts/waltographUI.ttf", 50, "Holaaa", FsVector3(20, 520, 0), FsVector3(1, 1, 1));

	//plataformaMesh.Load("Models/plataforma1.obj");
	//plataformaMaterial.Load(
	//	{ 0.1f, 0.1f, 0.1f },
	//	{ 0.3, 0.3, 0.3 },
	//	{ 0.8f, 0.8f, 0.8f },
	//	32, "Textures/plataforma1.png", false);
	//plataformaMesh.SetMaterial(plataformaMaterial);
	//plataformaMesh.SetPosition({-3,0,0});
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

	CamaraFPS(dt, time);

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
	ControlFPS(deltaTime,time);
	//Control2D(deltaTime, time);
	playerMesh.Render();
	playerMesh.SetRotation({0,playerMesh.GetTransform().rotation.y + 50*deltaTime, 0});
	//planeMesh.Render();
	//playerMesh2.Render();
	//plataformaMesh.Render();
	texto.Render();
}

Test::~Test() {}