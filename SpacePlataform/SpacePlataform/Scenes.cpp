#include"Scenes.h"

Asteroids::Asteroids() {
	//gR.reset(new SpacePlataform());
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
			mNave.SetPosition({ mNave.GetTransform().position.x,
				mNave.GetTransform().position.y,
				0 });
		}
		if (valor == CollisionDirection::BACKWARD) {
			std::cout << "atras" << std::endl;
		}
	}

	texto.SetText("Energia: " + std::to_string(vidas));
	texto.Render();
}

Asteroids::~Asteroids() {}

// Mistery--------------------------------------------------

Mistery::Mistery()
{
}

void Mistery::Begin()
{
	lDireccional.Load(
		FsVector3(-0.9f, -1, 0.2f),
		FsVector3(0.05f, 0.05f, 0.05f),
		FsVector3(0.05f, 0.05f, 0.05f),
		FsVector3(0.05f, 0.05f, 0.05f));
	lDireccional.SetActive(true);

	std::vector<std::string> caras = {
	"Textures/oasisnight_rt.tga",
	"Textures/oasisnight_lf.tga",
	"Textures/oasisnight_up.tga",
	"Textures/oasisnight_dn.tga",
	"Textures/oasisnight_bk.tga",
	"Textures/oasisnight_ft.tga"
	};

	sky.Load(caras);
	sky.SetActive(true);
	sky.SetColour({ 1,1,1 });
	gR->GetReference()->SetSkybox(sky);

	mPiso.Load("Models/fPlane.obj");
	mPiso.SetScale({ 50,1,50 });
	matPiso.Load({ 0.5f, 0.5f, 0.5f }, { 0.1f,0.1f,0.1f }, { 1,1,1 }, 0.01f, "Textures/SueloRoca.jpg", false);
	matCasa.Load({ 0.5f, 0.5f, 0.5f }, { 0.1f,0.1f,0.1f }, { 1,1,1 }, 0.01f, "Textures/casa.png", false);
	//matPiso.Load({1,0,1});
	mPiso.SetMaterial(matPiso);
	mCasa.Load("Models/casa.obj");
	mCasa.SetMaterial(matCasa);

	lSpot.Load(
		FsVector3(1, 1, 1),
		FsVector3(1, 1, 1),
		FsVector3(1, 1, 1),
		FsVector3(0, 2, 0),
		FsVector3(0, -1, 0),
		1.9f, 0.01f, 0.01f);
	lSpot.SetActive(true);

	
}


void Mistery::Update(float dt, float t)
{
	ControlFPS(dt, t);
	mPiso.Render();

	auto cam = gR->GetCamera();
	lSpot.SetPosition(cam->GetPosition());
	//lSpot.SetDirection({ gR->GetMouseX(), gR->GetMouseY(), 0 });
	//lSpot.SetDirection({ cam->GetRoll(),cam->GetYaw(),cam->GetPitch()+20});
	lSpot.SetDirection(cam->GetForward());
	mCasa.Render();
}

void Mistery::CamaraFPS(float, float)
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

void Mistery::ControlFPS(float dt, float t)
{
	CamaraFPS(dt, t);
	auto cam = gR->GetCamera();
	//Teclado
	float velocidad = 7.0f;
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


Mistery::~Mistery()
{
}
