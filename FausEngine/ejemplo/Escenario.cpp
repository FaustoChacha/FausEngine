#include"Escenario.h"
//#include<iostream>
//#include<filesystem>
//namespace fs = std::filesystem;
//#include <btBulletDynamicsCommon.h>

//btDiscreteDynamicsWorld* dynamicsWorld;



void CamaraFPS(float xMouseOffset, float yMouseOffset, FsCamera* cam, float dt, float t) {
	float velocidad = 0.2f;

	auto yaw = cam->GetYaw();
	yaw -= FsVector3::toRadians(xMouseOffset) * velocidad ;
	cam->SetYaw(yaw);

	auto pitch = cam->GetPitch();
	pitch += FsVector3::toRadians(yMouseOffset) * velocidad ;
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

void CamaraTPS(float xMouseOffset, float yMouseOffset, FsCamera* cam, FsTransform& targetTransform, float dt, float t) {
	float velocidad = 8.0f;

	auto yaw = cam->GetYaw();
	yaw -= FsVector3::toRadians(xMouseOffset) * velocidad*dt;
	cam->SetYaw(yaw);

	auto pitch = cam->GetPitch();
	pitch += FsVector3::toRadians(yMouseOffset) * velocidad*dt;
	cam->SetPitch(FsVector3::Clamp(pitch, -3.14f / 2, 3.14f / 2 ));

	FsVector3 pos;
	pos.x = targetTransform.position.x + 10 * cosf(cam->GetPitch()) * sinf(cam->GetYaw());
	pos.y = targetTransform.position.y + 10 * sinf(cam->GetPitch());
	pos.z = targetTransform.position.z + 10 * cosf(cam->GetPitch()) * cosf(cam->GetYaw());
	cam->SetPosition(pos);

	cam->SetTarget(targetTransform.position);

}

bool Colision(FsVector3 colMax1, FsVector3 colMin1, FsVector3 colMax2, FsVector3 colMin2) {
	return(
		colMax1.x >= colMin2.x &&
		colMin1.x <= colMax2.x &&
		colMax1.y >= colMin2.y &&
		colMin1.y <= colMax2.y);
	//colMax1.z > colMin2.z &&
	//colMin1.z < colMax2.z );
}

//---------------------------------------ESCENARIO4---------------------------------------------------

Escenario4::Escenario4()
{
	teclas = gamereference->GetKeys();
	colisiones[0] = false;
	colisiones[1] = false;
	colisiones[2] = false;
	colisiones[3] = false;
}

Escenario4::~Escenario4()
{
}

void Escenario4::ControlFPS(float dt, float time) {

	CamaraFPS(gamereference->GetMouseX(), gamereference->GetMouseY(), gamereference->GetCamera(), dt, time);
	
	//Teclado
	float velocidad = 3.0f;
	if (gamereference->GetKeys()[32]) {//space
		velocidad = 5;
	}
	if (gamereference->GetKeys()[87]) { // tecla W
		FsVector3 posicion = gamereference->GetCamera()->GetPosition() += gamereference->GetCamera()->GetForward() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[83]) { // tecla S
		FsVector3 posicion = gamereference->GetCamera()->GetPosition() -= gamereference->GetCamera()->GetForward() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[65]) { // tecla A
		FsVector3 posicion = gamereference->GetCamera()->GetPosition() -= gamereference->GetCamera()->GetRight() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[68]) { // tecla D
		FsVector3 posicion = gamereference->GetCamera()->GetPosition() += gamereference->GetCamera()->GetRight() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[69]) { // tecla E
		FsVector3 posicion = gamereference->GetCamera()->GetPosition() += gamereference->GetCamera()->GetUp() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[81]) { // tecla Q
		FsVector3 posicion = gamereference->GetCamera()->GetPosition() -= gamereference->GetCamera()->GetUp() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
}

void Escenario4::ControlTPS(FsTransform& targetPos, float dt, float t) {
	
	CamaraTPS(gamereference->GetMouseX(), gamereference->GetMouseY(), gamereference->GetCamera(), targetPos, dt, t);
	auto ca = gamereference->GetCamera();

	//Vector perpecdicular al frente
	FsVector3 dirForward = FsVector3::Normalize({ 10 * cos(ca->GetPitch()) * sin(ca->GetYaw()), 0, 10 * cos(ca->GetPitch()) * cos(ca->GetYaw()) });
	FsVector3 dirRight = { dirForward.z,0 ,-dirForward.x };

	
	//Teclado, mientras presiona tecla:
	float velocidad = 6.0f;
	if (gamereference->GetKeys()[87]) //  W
	{
		targetPos.position -= dirForward * dt * velocidad;
		std::cout << "x: " << targetPos.position.x<<"y: " << targetPos.position.y<<"z: " << targetPos.position.z << std::endl;
	}
	
	if (gamereference->GetKeys()[83])  // S
	{
		targetPos.position += dirForward * dt * velocidad;
	}
		
	
	if (gamereference->GetKeys()[65])  // A
	{
		targetPos.position -= dirRight * dt * velocidad;
	}
		
	
	if (gamereference->GetKeys()[68])  // D
	{
		targetPos.position += dirRight * dt * velocidad;
	}

	if (gamereference->GetKeys()[32]) { // space
		gamereference->GetKeys()[32] = false;
	}

}

void Escenario4::Control2D(FsTransform& targetPos, float dt, float t) {
	auto cam=gamereference->GetCamera();
	FsVector3 pos = { targetPos.position.x, 3, 10};
	cam->SetPosition(pos);
	cam->SetTarget(targetPos.position);

	auto teclas = gamereference->GetKeys();
	auto postemp = targetPos.position;

	colMax1.transform.position = collPlayer.GetMax();
	colMin1.transform.position = collPlayer.GetMin();
	colMax2.transform.position = collCaja[0].GetMax();
	colMin2.transform.position = collCaja[0].GetMin();


	for each (FsCollider var in collCaja)
	{
		if (collPlayer.CheckCollision(var)) {
			indexCollision = var.id;
			//std::cout << "indexCollision: " << indexCollision << std::endl;
		}
	}

	//std::cout << "D " << teclas[68] << std::endl;
	if (teclas[68]) { // D

		targetPos.position.x += 5 * dt;
		//if (collPlayer.CheckCollision(collCaja[indexCollision])) {
		//	targetPos.position.x += 0;
		//}
		//else {
		//	
		//}
		//if (collPlayer.CheckCollision(collCaja[indexCollision]) && !colisiones[1] /*&& !colisiones[2] && !colisiones[3]*/) {
		//	colisiones[0] = true;
		//	std::cout << "Entrando " << std::endl;
		//}
		//else {
		//	targetPos.position.x += 5 * dt;
		//	colisiones[0] = false;
		//}
	}

	if (teclas[65]) { //A
		targetPos.position.x -= 5 * dt;
		//if (collPlayer.CheckCollision(collCaja[indexCollision])) {
		//	targetPos.position.x += 0;
		//}
		//else {
		//	
		//}
		//if (collPlayer.CheckCollision(collCaja[indexCollision]) && !colisiones[0] /*&& !colisiones[2] && !colisiones[3]*/) {
		//	colisiones[1] = true;
		//}
		//else {
		//	targetPos.position.x -= 5 * dt;
		//	colisiones[1] = false;
		//}
		
	}

	//if (teclas[87]) { //W
	//	if (collPlayer.CheckCollision(collCaja[indexCollision]) && !colisiones[0] && !colisiones[1] && !colisiones[3]) {
	//		colisiones[2] = true;
	//	}
	//	else {
	//		targetPos.position.y += 5 * dt;
	//		colisiones[2] = false;
	//	}
	//	
	//}

	//if (teclas[83]) { //S
	//	if (collPlayer.CheckCollision(collCaja[indexCollision]) && !colisiones[0] && !colisiones[1] && !colisiones[2]) {
	//		colisiones[3] = true;
	//	}
	//	else {
	//		targetPos.position.y -= 5 * dt;
	//		colisiones[3] = false;
	//	}
	//	
	//}

	if (teclas[32]) { // space
		//targetPos.position.y += 15*dt;
		jump = true;
		jumpLap = t + 0.5f;
		teclas[32] = false;

	}

	
	if (jump) {
		teclas[32] = false;
		//std::cout << "entro" <<t+3 <<std::endl;
		targetPos.position.y += 22 * dt;
		//targetPos.position.y += abs( log10(1.1f));
		if (t >= jumpLap)
			jump = false;
	}

	
}


void Escenario4::Begin() {

	//==============================MALLAS======================================
	//piso
	//mPiso= FsMesh("Models/plane.obj");
	//mPiso.LoadMesh();
	//mPiso.material.LoadTexture("Textures/PisoArena.png");
	//mPiso.transform = FsTransform({ 0, -1.0f, 0 }, { 0,0,0 }, { 10,1,10 });
	//mPiso.material.ambient = { 0.7f, 0.7f, 0.7f };
	//mPiso.material.specular = { 0.01f, 0.01f, 0.01f };
	//mPiso.material.shineness = 1;

	//Nave
	//mNave = FsMesh("Models/nave.obj");
	//mNave.LoadMesh();
	//mNave.material.LoadTexture(PathGame + "/Models/nave/nave.jpg");
	//mNave.meshTransform = { {-15.0f, 0.0f, 0.0f}, {0,0,0},{0.5f,0.5f,0.5f} };
	//mNave.material.ambient = { 1.1f, 1.1f, 1.1f };
	//mNave.material.specular = { 1.0f, 1.1f, 1.1f };
	//mNave.material.shineness = 500.0f;

	//caja
	mCaja = FsMesh("Models/caja.obj");
	mCaja.LoadMesh();
	mCaja.material.LoadTexture("Textures/cajaTex.jpg");
	mCaja.transform = { {3.0f, 0.0f, 0.0f}, {0,0,0},{0.70f,0.70f,0.70f } };
	mCaja.material.ambient = { 0.1f, 0.1f, 0.1f };
	mCaja.material.specular = { 0.1f, 0.1f, 0.1f };
	mCaja.material.shineness = 5;
	//Collider caja
	collCaja[0] = FsCollider({ 0.75f,1.4f,0.75f }, { -0.75f,0,-0.75f });
	collCaja[0].id = 0;
	mCaja.SetCollider(collCaja[0]);

	colMax2 = FsMesh("Models/sphere.obj");
	colMax2.LoadMesh();
	colMax2.material.type = TypeMaterial::Unlit;
	colMax2.material.color = { 1,1,1 };

	colMin2 = colMax2;
	colMin2.material.type = TypeMaterial::Unlit;
	colMin2.material.color = { 0.5f,0.5f,0.5f };

	mCaja2 = mCaja;
	collCaja[1] = FsCollider({ 0.75f,1.4f,0.75f }, { -0.75f,0,-0.75f });
	collCaja[1].id = 1;
	mCaja2.SetCollider(collCaja[1]);
	mCaja2.transform.position = {9,0,0};

	mCaja3 = mCaja;
	collCaja[2]= FsCollider({ 0.75f,1.4f,0.75f }, { -0.75f,0,-0.75f });
	collCaja[2].id = 2;
	mCaja3.SetCollider(collCaja[2]);
	mCaja3.transform.position = {12,3,0};

	//======================MOVIMIENTO===========================

	player= FsMesh("Models/sphere.obj");
	player.LoadMesh();
	player.material.type = TypeMaterial::Unlit;
	player.material.color = {0.0f,0.7f,0.2f};
	player.transform = { {3,6,0}, {0,0,0},{3,3,3} };
	//COllider player
	collPlayer = FsCollider({ 0.75f,0.75f,0.75f }, { -0.75f,-0.75f,-0.75f });
	player.SetCollider(collPlayer);

	colMax1 = FsMesh("Models/sphere.obj");
	colMax1.LoadMesh();
	colMax1.material.type = TypeMaterial::Unlit;
	colMax1.material.color = {1,1,1};

	colMin1 = colMax1;
	colMin1.material.color = {0.5f,0.5f,0.5f};


	//cuboX = FsMesh("Models/fCubo.obj");
	//cuboX.LoadMesh();
	//cuboX.material.type = TypeMaterial::Unlit;
	//cuboX.material.color = { 1,0,0 };
	//cuboX.transform = { {0, 0, 0},{0,0,0},{40,0.05f,0.05f} };

	//cuboY = cuboX;
	//cuboY.material.color = { 0,1,0 };
	//cuboY.transform = { {0, 0, 0},{0,0,0},{0.05f,40,0.05f} };

	//cuboZ = cuboX;
	//cuboZ.material.color = { 0,0,1 };
	//cuboZ.transform = { {0, 0, 0},{0,0,0},{0.05f,0.05f,40} };

	//==================LUCES========================
	if (true) {
		esferaLuz1 = FsMesh("Models/sphere.obj");
		esferaLuz1.LoadMesh();
		esferaLuz1.material.type = TypeMaterial::Unlit;
		esferaLuz1.material.color = { 0.8f,0.8f,0.8f };
		//esferaLuz1.meshTransform = { {5, 1, 0},{0,0,0},{1,1,1} };
		esferaLuz1.transform.scale = {3,3,3};

		esferaLuz2 = esferaLuz1;
		esferaLuz2.material.color = { 1,0,0 };
		esferaLuz2.transform.position = { -5, 1, 0 };

		esferaLuz3 = esferaLuz1;
		esferaLuz3.material.color = { 0,0,1 };
		esferaLuz3.transform.position = { 0, 1, 5 };

		conoLuz1 = FsMesh("Models/Cono.obj");
		conoLuz1.LoadMesh();
		conoLuz1.material.type = TypeMaterial::Unlit;
		conoLuz1.transform.position = { 0, 3, 0 };
		conoLuz1.transform.rotation = { 0, 0, 0 };
		conoLuz1.transform.scale = {2,2,2};
		conoLuz1.material.color = { 1, 1, 1 };

		conoLuz2 = conoLuz1;
		conoLuz2.transform.position = { 0, 3, -5 };
		conoLuz2.material.color = { 0, 1, 0 };

		conoLuz3 = conoLuz1;
		conoLuz3.transform.position = { 0, 3, -10 };
		conoLuz3.material.color = { 0, 0, 1 };

		//luces
		luzDireccional = FsDireciontalLight(
			FsVector3(0.0f, -0.4f, -0.17f), 
			FsVector3(2, 2, 2), 
			FsVector3(0.5f, 0.5f, 0.5f), 
			FsVector3(0.5f, 0.5f, 0.5f));
		luzDireccional.Load();

		//Pointlights
		pointLight[0] = FsPointLight(
			FsVector3(1, 1.0f, 1.0f), esferaLuz1.material.color, FsVector3(1.0f, 1.0f, 1.0f), esferaLuz1.transform.position, 1, 0.22f, 0);
		pointLight[0].Load();

		pointLight[1] = FsPointLight(
			FsVector3(0.2f, 0.2f, 0.2f), esferaLuz2.material.color, FsVector3(1.0f, 1.0f, 1.0f), esferaLuz2.transform.position, 1, 0.22f, 0.2f);
		pointLight[1].Load();

		pointLight[2] = FsPointLight(
			FsVector3(0.2f, 0.2f, 0.2f), esferaLuz3.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			esferaLuz3.transform.position, 1, 0.27f, 0.17f);
		pointLight[2].Load();

		//Spotlights
		spotlight[0] = FsSpotLight(
			FsVector3(0.1f, 0.1f, 0.1f), conoLuz1.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			conoLuz1.transform.position, conoLuz1.transform.rotation, 1.0f, 0.07f, 0.017f);
		spotlight[0].Load();

		spotlight[1] = FsSpotLight(
			FsVector3(0.1f, 0.1f, 0.1f), conoLuz2.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			conoLuz2.transform.position, conoLuz2.transform.rotation, 1.0f, 0.07f, 0.017f);
		spotlight[1].Load();

		spotlight[2] = FsSpotLight(
			FsVector3(0.1f, 0.1f, 0.1f), conoLuz3.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			conoLuz3.transform.position, conoLuz3.transform.rotation, 1.0f, 0.07f, 0.017f);
		spotlight[2].Load();

	}

	//=================SKYBOX======================
	std::vector<std::string> caras = {
	"Textures/GalaxyRt.png",
	"Textures/GalaxyLf.png",
	"Textures/GalaxyUp.png",
	"Textures/GalaxyDn.png",
	"Textures/GalaxyBk.png",
	"Textures/GalaxyFt.png"
	};

	sky = FsSkybox(caras);
	sky.Load();
	sky.colour = { 1,1,1 };

	//===================== fisica =====================

	texto1= FsText("Fonts/gooddog.ttf", 32, "Juego Fausto", FsVector2(320, 500), FsVector3(1, 0, 0));
	texto2= FsText("Fonts/gooddog.ttf", 64, "Puntaje", FsVector2(10, 500), FsVector3(0, 0, 1));

}



void Escenario4::Update(float deltaTime, float time) {
	//sky.Render();
	//ControlFPS(deltaTime, time);
	//sky.on = false;
	//ControlTPS(player.meshTransform, deltaTime, time);
	if (teclas[86]) { // v
		swCam = !swCam;
		teclas[32] = false;
		std::cout << swCam << std::endl;
	}
	if (!swCam) {
		Control2D(player.transform, deltaTime, time);
	}
	else {
		ControlTPS(player.transform, deltaTime, time);
	}
	
	if (!collPlayer.CheckCollision(collCaja[indexCollision])) {
		player.transform.position.y -= 15*deltaTime;
	}
	//player.transform.position.x += 1*deltaTime;


	
	//conoLuz1.meshTransform.position = {5,5,5};
	//conoLuz1.meshTransform.rotation = {45,0,-45};
	//conoLuz1.Render();
	//cuboX.Render();
	//cuboY.Render();
	//cuboZ.Render();



	//colMax1.Render();
	//colMin1.Render();
	player.Render();

	//colMax2.Render();
	//colMin2.Render();
	mCaja.Render();

	mCaja2.Render();
	mCaja3.Render();

	//mPiso.Render();

	if (player.transform.position.y < -30) {
		player.transform.position = {3,6,0};
	}

	texto1.Render();
	texto2.Render();
}




