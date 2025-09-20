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

void Test::Begin() {


	//=================SKYBOX======================


	//LUZCES================
	luzDireccional.Load(
		FsVector3(-0.9f, -1, 0.2f),
		FsVector3(10, 10, 10),
		FsVector3(0.9f, 0.9f, 0.9f),
		FsVector3(0.5f, 0.5f, 0.5f));
	

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


	texto.Load("Fonts/waltographUI.ttf", 50, "Holaaa", FsVector3(20, 520, 0), FsVector3(1, 1, 1));
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

	matMalla.Load({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.9f,1.0f,0.9f }, 0.5f, "Textures/nave.jpg", false);
	
	matMalla2.Load({0,1,0});
	//matMalla.Load(/*{ 0.5f,0.5f ,0.5f }*/{1,1,1}, { 0.1f, 0.1f, 0.1f }, { 1.0f, 1.0f, 1.0f }, 1, "Textures/player-ball.png", false);
	malla.Load("Models/nave.obj");
	//malla.material = matMalla;
	malla.SetMaterial(matMalla);
	malla.SetPosition({0,0,0});

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
	ControlFPS(deltaTime, time);
	
	//malla.transform.position = { 0,0,0 };
	malla.Render();
	texto.Render();

}

Test::~Test() {}


Asteroids::Asteroids() {
	gR.reset(new SpacePlataform());
}

void Asteroids::CamaraFPS(float dt, float t)
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

void Asteroids::ControlFPS(float dt, float time) {

	CamaraFPS(dt, time);

	//Teclado
	float velocidad = 20.0f;
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

void Asteroids::ControlNave(float dt, float t)
{
	float vel;
	if (gR->GetKeyPress(Keys::O)) {
		vel = 20;
	}
	else {
		vel = 20;
	}

	if (gR->GetKeyPress(Keys::W)) {
		mNave.SetPosition({ mNave.GetTransform().position.x,
			mNave.GetTransform().position.y,
			mNave.GetTransform().position.z + vel * dt });
	}
	if (gR->GetKeyPress(Keys::S)) {
		mNave.SetPosition({ mNave.GetTransform().position.x,
		mNave.GetTransform().position.y,
		mNave.GetTransform().position.z - vel * dt });
	}
	if (gR->GetKeyPress(Keys::A)) {
		mNave.SetPosition({ mNave.GetTransform().position.x + vel * dt ,
		mNave.GetTransform().position.y,
		mNave.GetTransform().position.z });
	}
	if (gR->GetKeyPress(Keys::D)) {
		mNave.SetPosition({ mNave.GetTransform().position.x - vel * dt ,
		mNave.GetTransform().position.y,
		mNave.GetTransform().position.z });
	}

	if (gR->GetKeyPress(Keys::Q)) {
		mNave.SetPosition({ mNave.GetTransform().position.x,
		mNave.GetTransform().position.y - vel * dt,
		mNave.GetTransform().position.z });
	}

	if (gR->GetKeyPress(Keys::E)) {
		mNave.SetPosition({ mNave.GetTransform().position.x,
		mNave.GetTransform().position.y + vel * dt,
		mNave.GetTransform().position.z });
	}

	if (vel == 8) {
		auto cam = gR->GetCamera();
		cam->SetPosition({ mNave.GetTransform().position.x, 50, mNave.GetTransform().position.z - 30 });
		cam->SetTarget({ mNave.GetTransform().position.x, mNave.GetTransform().position.y, mNave.GetTransform().position.z + 30 });
	}
	else {
		auto cam = gR->GetCamera();
		cam->SetPosition({ mNave.GetTransform().position.x, 25, mNave.GetTransform().position.z - 30 });
		cam->SetTarget({ mNave.GetTransform().position.x, mNave.GetTransform().position.y, mNave.GetTransform().position.z + 60 });
	}

}

void Asteroids::Begin() {

	//LUCES
	luzDireccional.Load(
		FsVector3(-0.9f, -1, 0.2f),
		FsVector3(0.5f, 0.5f, 0.5f),
		FsVector3(0.9f, 0.9f, 0.9f),
		FsVector3(0.5f, 0.5f, 0.5f));
	luzDireccional.SetActive(true);

	//SKYBOX
	std::vector<std::string> caras = {
	"Textures/Sk_GalaxyRt.png",
	"Textures/Sk_GalaxyLf.png",
	"Textures/Sk_GalaxyUp.png",
	"Textures/Sk_GalaxyDn.png",
	"Textures/Sk_GalaxyBk.png",
	"Textures/Sk_GalaxyFt.png"
	};
	sky.Load(caras);
	sky.SetActive(true);
	sky.SetColour({ 1.0,1.0,1.0 });
	gR->SetSkybox(sky);


	//TEXTO
	texto.Load("Fonts/arial.ttf", 25, "Vidas", FsVector3(20, 520, 0), FsVector3(1, 1, 1));

	//NAVE
	matNave.Load({ 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f }, { 0.5f,0.5f,0.5f }, 0.01f, "Textures/nave.jpg", false);
	matNaveUnlit.Load({ 1,0,0 });

	mNave.Load("Models/nave.obj");
	mNave.SetMaterial(matNave);
	mNave.SetPosition({ 0,0,0 });
	mNave.SetRotation({ 90,0,0 });
	mNave.SetScale({ 0.5f,0.5f,0.5f });



	//Collider
	mColMaxNave.Load("Models/fSphere.obj");
	matLimitCollider.Load({ 1,0,0 });
	mColMaxNave.SetMaterial(matLimitCollider);
	mColMaxNave.SetScale({ 1, 1, 1 });
	mColMinNave = mColMaxNave;
	mColMaxNave.SetPosition({ 1,1,30 });
	mColMinNave.SetPosition({ -3,0,0 });
	colNave.SetBoundMax(mColMaxNave.GetTransform().position);
	colNave.SetBoundMin(mColMinNave.GetTransform().position);
	mNave.SetCollider(colNave);

	//ASTEROIDE
	matAsteroide.Load({ 0.5f, 0.5f, 0.5f }, { 1,1,1 }, { 1,1,1 }, 0.01f, "Textures/asteroide.png", false);
	mAsteroide.Load("Models/asteroide.obj");
	mAsteroide.SetPosition({ 0, 0, 50 });
	mAsteroide.SetScale({ 0.1f,0.1f,0.1f });
	mAsteroide.SetMaterial(matAsteroide);
	lPointAsteroide.Load(
		FsVector3(0.1f, 1, 0.1f),
		FsVector3(0, 1, 0),
		FsVector3(0.1f, 0.1f, 0.1f),
		FsVector3(0, 3, 0),
		0.5f, 0.01f, 0.01f
	);

	//Collider
	mColMaxAste.Load("Models/fSphere.obj");
	matLimitCollider.Load({ 1,0,0 });
	mColMaxAste.SetMaterial(matLimitCollider);
	mColMaxAste.SetScale({ 1, 1, 1 });
	mColMinAste = mColMaxAste;
	mColMaxAste.SetPosition({ 5,6,8 });
	mColMinAste.SetPosition({ -5,-6,-10 });
	colAsteroide.SetBoundMax(mColMaxAste.GetTransform().position);
	colAsteroide.SetBoundMin(mColMinAste.GetTransform().position);
	mAsteroide.SetCollider(colAsteroide);


	//CAMARA
	gR->GetCamera().get()->SetPosition({
		mNave.GetTransform().position.x,
		mNave.GetTransform().position.y + 15,
		mNave.GetTransform().position.z - 5 });
	gR->GetCamera().get()->SetTarget(mNave.GetTransform().position);
}



void Asteroids::Update(float deltaTime, float time) {

	if (gR->GetKeyPress(Keys::C)) {
		ControlFPS(deltaTime, time);
	}
	else {
		ControlNave(deltaTime, time);
	}




	mNave.Render();
	lSpotNave.SetPosition(gR->GetCamera()->GetPosition());
	lSpotNave.SetDirection(mNave.GetTransform().position);
	mColMaxNave.SetPosition(colNave.GetBoundMax());
	mColMaxNave.Render();
	mColMinNave.SetPosition(colNave.GetBoundMin());
	mColMinNave.Render();

	mColMaxAste.Render();
	mColMaxAste.SetPosition(colAsteroide.GetBoundMax());
	mColMinAste.Render();
	mColMinAste.SetPosition(colAsteroide.GetBoundMin());
	lPointAsteroide.SetPosition({ mAsteroide.GetTransform().position.x, mAsteroide.GetTransform().position.y + 10,mAsteroide.GetTransform().position.z });
	mAsteroide.Render();
	mAsteroide.SetRotation({ 0,0,time * 17 });


	if (colNave.CheckCollision(colAsteroide)) {
		vidas-- * 0.0001f;
		auto valor = colNave.GetDirection(colAsteroide);
		if (valor == CollisionDirection::DOWN) {
			std::cout << "abajo" << std::endl;
		}
		if (valor == CollisionDirection::UP) {
			std::cout << "arriba" << std::endl;
		}
		if (valor == CollisionDirection::LEFT) {
			std::cout << "izquierda" << std::endl;
		}
		if (valor == CollisionDirection::RIGHT) {
			std::cout << "derecha" << std::endl;
		}
		if (valor == CollisionDirection::FORWARD) {
			mNave.SetPosition({mNave.GetTransform().position.x, 
				mNave.GetTransform().position.y, 
				0});
		}
		if (valor == CollisionDirection::BACKWARD) {
			std::cout << "atras" << std::endl;
		}
	}

	texto.SetText("Energia: " + std::to_string(vidas));
	texto.Render();


}

Asteroids::~Asteroids() {}