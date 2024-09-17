#include"Player.h"
#include<cmath>
#include"../Motor/Headers/FsCamera.h"

Player::Player()
{
	//transform = &malla.transform;
	//transform.reset(&mallaJugador.transform);
	//gameReference = new UserGame;
	gameReference.reset(new SpacePlataform);
	numberLifes = 3;
	color = {0,1,0};
	speedPointLight = 2;
	startPlayerPosition = { 0,0,0 }; // 
	//startPlayerPosition = { -73,0,0 };

	activatePower = false;
	jump = false;
	timePowerJump = 0.0f;
	intesityPowerJump = 22;
	countSpaceKey = 0;
}

void Player::ControlFPS(float dt, float time) {

	CameraFPS(dt, time);

	//Teclado
	float velocidad = 3.0f;
	if (gameReference->GetKeyPress(Keys::SPACE)) {//space
		velocidad = 15;
	}
	if (gameReference->GetKeyPress(Keys::W)) { // tecla W
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() += gameReference->GetCamera()->GetForward() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeyPress(Keys::S)) { // tecla S
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() -= gameReference->GetCamera()->GetForward() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeyPress(Keys::A)) { // tecla A
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() -= gameReference->GetCamera()->GetRight() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeyPress(Keys::D)) { // tecla D
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() += gameReference->GetCamera()->GetRight() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeyPress(Keys::E)) { // tecla E
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() += gameReference->GetCamera()->GetUp() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeyPress(Keys::Q)) { // tecla Q
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() -= gameReference->GetCamera()->GetUp() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
}

void Player::ControlTPS( float dt, float t) {

	FsVector3* targetPos = &playerMesh.GetTransform().position;
	CameraTPS(dt, t);
	auto ca = gameReference->GetCamera();


	//Vector perpecdicular al frente
	FsVector3 dirForward = FsVector3::Normalize({ 10 * cos(ca->GetPitch()) * sin(ca->GetYaw()), 0, 10 * cos(ca->GetPitch()) * cos(ca->GetYaw()) });
	FsVector3 dirRight = { dirForward.z,0 ,-dirForward.x };


	//Teclado, mientras presiona tecla:
	float velocidad = 10.0f;
	if (gameReference->GetKeyPress(Keys::W)) //  W
	{
		*targetPos -= dirForward * dt * velocidad;
	}

	if (gameReference->GetKeyPress(Keys::S))  // S
	{
		*targetPos += dirForward * dt * velocidad;
	}


	if (gameReference->GetKeyPress(Keys::A))  // A
	{
		*targetPos -= dirRight * dt * velocidad;
	}


	if (gameReference->GetKeyPress(Keys::D))  // D
	{
		*targetPos += dirRight * dt * velocidad;
	}

	//if (gameReference->GetKeys()[32]) { // space
	//	gameReference->GetKeys()[32] = false;
	//}

}

void Player::Control2D(float dt, float t) {
	auto cam = gameReference->GetCamera();
	
	FsVector3 pos = { playerMesh.GetTransform().position.x, 0, -12 };
	cam->SetPosition(pos);
	//cam->SetTarget(mallaJugador.transform.position);
	cam->SetTarget(playerMesh.GetTransform().position);

	if (gameReference->GetKeyPress(Keys::D)) { // D
		playerMesh.SetRotation({ playerMesh.GetTransform().rotation.x,
			playerMesh.GetTransform().rotation.y - 0.35f,
			playerMesh.GetTransform().rotation.z }); //animacion
		playerMesh.SetPosition({ playerMesh.GetTransform().position.x - 5 * dt,
			playerMesh.GetTransform().position.y,
			playerMesh.GetTransform().position.z });

	}

	if (gameReference->GetKeyPress(Keys::A)) { //A
		playerMesh.SetRotation({ playerMesh.GetTransform().rotation.x, 
			playerMesh.GetTransform().rotation.y + 0.35f, 
			playerMesh.GetTransform().rotation.z }); //animacion
		playerMesh.SetPosition({playerMesh.GetTransform().position.x + 5*dt, 
			playerMesh.GetTransform().position.y, 
			playerMesh.GetTransform().position.z});

	}

	//Salto-------------
	if (gameReference->GetKeyPress(Keys::SPACE) && colision) { // space--+
		gameReference->SetKeyRelease(Keys::SPACE);
		jump = true;
		timeJump = t + 0.5f;
		countSpaceKey++;
		if (countSpaceKey > 1)countSpaceKey = 0;
	}

	if (jump && countSpaceKey == 1) {
		gameReference->SetKeyRelease(Keys::SPACE);
		//transform->position.y += poderSalto * dt;
		playerMesh.SetPosition({ playerMesh.GetTransform().position.x, 
			playerMesh.GetTransform().position.y + intesityPowerJump * dt,
			playerMesh.GetTransform().position.z
			});
		if (t >= timeJump) {
			jump = false;
			countSpaceKey = 0;
		}
	}

}

void Player::CameraFPS( float dt, float t)
{
	auto cam = gameReference->GetCamera();
	float velocidad = 0.2f;

	auto yaw = cam->GetYaw();
	yaw -= FsVector3::toRadians(gameReference->GetMouseX()) * velocidad;
	cam->SetYaw(yaw);

	auto pitch = cam->GetPitch();
	pitch += FsVector3::toRadians(gameReference->GetMouseY()) * velocidad;
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

void Player::CameraTPS(float dt, float t)
{
	//FsVector3* targetPos = &mallaJugador.transform.position;
	FsVector3* targetPos = &playerMesh.GetTransform().position;
	auto cam = gameReference->GetCamera();
	float velocidad = 8.0f;

	auto yaw = cam->GetYaw();
	yaw -= FsVector3::toRadians(gameReference->GetMouseX()) * velocidad * dt;
	cam->SetYaw(yaw);

	auto pitch = cam->GetPitch();
	pitch += FsVector3::toRadians(gameReference->GetMouseY()) * velocidad * dt;
	cam->SetPitch(FsVector3::Clamp(pitch, -3.14f / 2, 3.14f / 2));

	FsVector3 pos;
	pos.x = targetPos->x + 10 * cosf(cam->GetPitch()) * sinf(cam->GetYaw());
	pos.y = targetPos->y + 10 * sinf(cam->GetPitch());
	pos.z = targetPos->z + 10 * cosf(cam->GetPitch()) * cosf(cam->GetYaw());
	cam->SetPosition(pos);

	cam->SetTarget(*targetPos);
}

void Player::OrbitMeshLight(float offsetX, float offsetY, float dt, float t, float vel)
{
	//ry=ry-n
	//mallaLuzOrbital.transform.rotation.y -= FsVector3::toRadians(offsetX) * vel * dt;
	//mallaLuzOrbital.transform.rotation.x -= FsVector3::toRadians(offsetY) * vel * dt;
	orbitalLightMesh.SetRotation(
		{orbitalLightMesh.GetTransform().rotation.x - FsVector3::toRadians(offsetY) * vel * dt,
		orbitalLightMesh.GetTransform().rotation.y- FsVector3::toRadians(offsetX) * vel * dt,
		orbitalLightMesh.GetTransform().rotation.z}
	);
		
	float distancia = 0.75f;
	float posX = playerMesh.GetTransform().position.x + distancia * cos(orbitalLightMesh.GetTransform().rotation.x) * sin(orbitalLightMesh.GetTransform().rotation.y);
	float posY= playerMesh.GetTransform().position.y + distancia * sin(orbitalLightMesh.GetTransform().rotation.x);
	float posZ = playerMesh.GetTransform().position.z - distancia * cos(orbitalLightMesh.GetTransform().rotation.x) * cos(orbitalLightMesh.GetTransform().rotation.y);
	orbitalLightMesh.SetPosition({posX, posY, posZ });
}

void Player::SetMeshLightColor(FsVector3 color)
{
	lightMaterial.SetColor(color);

}

void Player::SetPosition(FsVector3 v) {
	playerMesh.SetPosition(v);
}

FsVector3 Player::GetPosition() {
	return playerMesh.GetTransform().position;
}

void Player::ActivatePower(bool on) {
	if (on) {
		color = { 1,1,1 };
		//matLuz.SetColor({1,1,1});
		//luzPuntual.SetDiffuse({1,1,1});
		intesityPowerJump = 32;
		activatePower = true;
	}
	else {
		intesityPowerJump = 22;
		HandleColor();
	}
}

void Player::Init() {

	//jugadorz
	
	playerMesh.Load("Models/player-ball.obj");
	//mallaJugador.Load();
	//playerMaterial.Load({ 1.1f, 1.1f, 1.1f }, { 1.5f, 1.5f, 1.5f }, { 0.9f,1.0f,0.9f }, 0.5f, "Textures/player-ball.png", false);
	playerMaterial.Load({ 0.1f, 0.1f, 0.1f }, { 0.5f, 0.5f, 0.5f }, { 0.9f,1.0f,0.9f }, 0.5f, "Textures/player-ball.png");
	playerMesh.SetTransform({ startPlayerPosition, {-90,0,0},{0.8f,0.8f,0.8f} });
	playerMesh.SetMaterial(playerMaterial);
	//collider jugador
	collider.SetBoundMax({ 0.6f,0.75f,0.75f }); 
	collider.SetBoundMin({ -0.6f, -0.8f, -0.75f });
	playerMesh.SetCollider(collider);

	//malla luz orbital
	orbitalLightMesh.Load("Models/fSphere.obj");
	lightMaterial.Load(color);
	orbitalLightMesh.SetScale({ 0.5f,0.5f,0.5f });
	orbitalLightMesh.SetMaterial(lightMaterial);

	//luz puntual
	pointLight.Load(
		FsVector3(1, 1, 1),
		FsVector3(0,1,0),
		FsVector3(1.0f, 1.5f, 1.5f),
		//player.transform.position,
		FsVector3(0, 3, 0),
		2, 0.0f, 0.0f
	);
}



void Player::Tick(bool pause, float dt, float t, bool col) {
	colision = col;

	//if (gameReference->GetKeyPress(Keys::C)) {
	//	ControlTPS(dt, t);
	//}
	//else
	//{
	//	Control2D(dt, t);
	//}

	if (!pause) {

		//if (gameReference->GetKeyPress(Keys::C)) {
		//	ControlTPS(dt, t);
		//}
		//else
		//{
		Control2D(dt, t);
		//}

		OrbitMeshLight(-10, 10, dt, t, 20);
		
		pointLight.SetLinear((sin(speedPointLight * t) / 4) + 0.25f);
		pointLight.SetDiffuse(color);
		lightMaterial.SetColor(color);

		//poder activado
		if (activatePower) {
			timePowerJump += 0.01f;
			if (timePowerJump>16) {
				activatePower = false;
				ActivatePower(false);
			}
		}

		//reinicio--------------
		if (playerMesh.GetTransform().position.y < -15) {
			playerMesh.SetPosition(startPlayerPosition);
			//playerMesh.SetPosition({-70, playerMesh.GetTransform().position.y + 10, playerMesh.GetTransform().position.z });
			numberLifes--;
			HandleColor();
		}

	}

	pointLight.SetPosition(playerMesh.GetTransform().position);
	orbitalLightMesh.Render();
	playerMesh.Render();
}

void Player::HandleColor() {
	switch (numberLifes)
	{
	case 3:
		color = { 0,1,0 };
		speedPointLight = 2;
		break;
	case 2:
		color = { 1,1,0 };
		speedPointLight = 4;
		break;
	case 1:
		color = { 1,0,0 };
		speedPointLight = 6;
		break;
	case 0:
		exit(3);
	}
}

FsCollider Player::GetCollider() {
	return collider;
}

void Player::SetNumberLifes(int n) {
	numberLifes = n;
}

int Player::GetNumberLifes() {
	return numberLifes;
}



Player::~Player()
{
	//delete gameReference;
}