#include"Escenario.h"

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

void orbitar(float offsetX, float offsetY, FsTransform& target, FsTransform center, float dt, float t, float vel ) {
	target.rotation.y -= FsVector3::toRadians(offsetX) * vel * dt;
	target.rotation.x -= FsVector3::toRadians(offsetY) * vel * dt;
	float distancia = 0.75f;
	target.position.x = center.position.x + distancia * cos(target.rotation.x) * sin(target.rotation.y);
	target.position.y = center.position.y + distancia * sin(target.rotation.x);
	target.position.z = center.position.z - distancia * cos(target.rotation.x) * cos(target.rotation.y);
}

//---------------------------------------ESCENARIO4---------------------------------------------------

Plataformas::Plataformas()
{
	teclas = gamereference->GetKeys();
	colorVida = FsVector3(0,1,0);
}

Plataformas::~Plataformas()
{
}

void Plataformas::ControlFPS(float dt, float time) {

	CamaraFPS(gamereference->GetMouseX(), gamereference->GetMouseY(), gamereference->GetCamera(), dt, time);
	
	//Teclado
	float velocidad = 3.0f;
	if (gamereference->GetKeys()[32]) {//space
		velocidad = 15;
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

void Plataformas::ControlTPS(FsTransform& targetPos, float dt, float t) {
	
	CamaraTPS(gamereference->GetMouseX(), gamereference->GetMouseY(), gamereference->GetCamera(), targetPos, dt, t);
	auto ca = gamereference->GetCamera();

	//Vector perpecdicular al frente
	FsVector3 dirForward = FsVector3::Normalize({ 10 * cos(ca->GetPitch()) * sin(ca->GetYaw()), 0, 10 * cos(ca->GetPitch()) * cos(ca->GetYaw()) });
	FsVector3 dirRight = { dirForward.z,0 ,-dirForward.x };

	
	//Teclado, mientras presiona tecla:
	float velocidad = 10.0f;
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

void Plataformas::Control2D(FsTransform& targetPos, float dt, float t) {
	auto cam=gamereference->GetCamera();
	FsVector3 pos = { targetPos.position.x, 0, -12};
	cam->SetPosition(pos);
	cam->SetTarget(targetPos.position);

	auto teclas = gamereference->GetKeys();
	auto postemp = targetPos.position;

	if (teclas[32]) {// space
		iniciar = true;
	}


	if (iniciar) {
		if (teclas[68]) { // D
			player.transform.rotation.y -= 0.35f; // animacion
			targetPos.position.x -= 5 * dt;

		}

		if (teclas[65]) { //A
			player.transform.rotation.y += 0.35f; //animacion
			targetPos.position.x += 5 * dt;

		}
	}


	//if (teclas[87]) { //w
	//	player.transform.position.y += 5*dt;
	//}

	//if (teclas[83]) {//s
	//	player.transform.position.y -= 5*dt;
	//}

	//if (teclas[79]) {//O
	//	std::cout << player.transform.position.x << " " <<
	//		player.transform.position.y << " " <<
	//		player.transform.position.z << std::endl;
	//}
}


void Plataformas::Begin() {

	//==============================MALLAS======================================
	
	//PLAYER
	posInicialPlayer = { 0,3,0 };
	player = FsMesh("Models/player-ball.obj");
	player.LoadMesh();
	player.material.LoadTexture("Textures/player-ball.png");
	player.material.bind_TexToColor = true;
	player.material.color = { 0.9f,1.0f,0.9f };
	player.material.ambient= { 0.1f, 0.1f, 0.1f };
	player.material.specular = { 0.5f, 0.5f, 0.5f };
	player.material.shineness = 0.5f;
	player.transform = { posInicialPlayer, {-90,0,0},{0.8f,0.8f,0.8f} };
	//COllider player
	collPlayer = FsCollider({ 0.6f,0.75f,0.75f }, { -0.6f,-0.8f,-0.75f });
	player.SetCollider(collPlayer);

	mLuzPlayer = FsMesh("Models/fSphere.obj");
	mLuzPlayer.LoadMesh();
	mLuzPlayer.material.type = TypeMaterial::Unlit;
	mLuzPlayer.material.color = colorVida;
	mLuzPlayer.transform.scale = {0.5f,0.5f,0.5f};

	colMax1 = FsMesh("Models/fSphere.obj");
	colMax1.LoadMesh();
	colMax1.material.type = TypeMaterial::Unlit;
	colMax1.material.color = { 1,1,1 };

	colMin1 = colMax1;
	colMin1.material.color = { 0.5f,0.5f,0.5f };


	//=======PLATAFORMAS======
	
	if (true) {
	
	//plataforma grande---------------------------------------------------------
	plataformas[0] = FsMesh("Models/plataforma1.obj");
	plataformas[0].LoadMesh();
	plataformas[0].material.LoadTexture("Textures/plataforma1.png");
	plataformas[0].transform = { {0.0f, -8.0f, -2.5f}, {0,90,0},{0.5f,0.5f,0.5f } };
	plataformas[0].material.ambient = { 0.1f, 0.1f, 0.1f };
	plataformas[0].material.specular = { 0.1f, 0.1f, 0.1f };
	plataformas[0].material.shineness = 5;
	complemento0 = plataformas[0];
	complemento0.transform.position.x -= 16;
	//Collider 
	collPlataformas[0] = FsCollider({ 7.75f,4.0f,4.0f }, { -24.1f,-4.0f,-4.0f });
	collPlataformas[0].id = 0;
	plataformas[0].SetCollider(collPlataformas[0]);

	plataformas[7] = plataformas[0];
	plataformas[7].transform.position = {-77,-15,-2.5f};
	collPlataformas[7] = FsCollider({ 7.75f,4.0f,4.0f }, { -7.75f,-4.0f,-4.0f });
	collPlataformas[7].id = 7;
	plataformas[7].SetCollider(collPlataformas[7]);

	//plataforma mediana piramidal-----------------------------------------------------------
	plataformas[1] = FsMesh("Models/plataforma2.obj");
	plataformas[1].LoadMesh();
	plataformas[1].material.LoadTexture("Textures/plataforma2.png");
	plataformas[1].transform = { {-29.0f, -2.5f, 0.0f}, {0,0,0},{1,1,1 } };
	plataformas[1].material.ambient = { 0.1f, 0.1f, 0.1f };
	plataformas[1].material.specular = { 0.1f, 0.1f, 0.1f };
	plataformas[1].material.shineness = 5;
	//Collider 
	collPlataformas[1] = FsCollider({ 1.5f,0.1f,1.0f }, { -1.5f,-1.5f,-1.5f});
	collPlataformas[1].id = 1;
	plataformas[1].SetCollider(collPlataformas[1]);
	//Referencia
	refRight = FsMesh("Models/fSphere.obj");
	refRight.LoadMesh();
	refRight.material.type= TypeMaterial::Unlit;
	refRight.material.color = {0,0,1};

	refLeft = FsMesh("Models/fSphere.obj");
	refLeft.LoadMesh();
	refLeft.material.type = TypeMaterial::Unlit;
	refLeft.material.color = { 0,1,0 };

	plataformas[2] = plataformas[1];
	plataformas[2].transform.position = {-35, -0.5f,0};
	collPlataformas[2] = collPlataformas[1];
	collPlataformas[2].id = 2;
	plataformas[2].SetCollider(collPlataformas[2]);

	plataformas[3] = plataformas[1];
	plataformas[3].transform.position = { -43, -5,0 };
	collPlataformas[3] = collPlataformas[1];
	collPlataformas[3].id = 3;
	plataformas[3].SetCollider(collPlataformas[3]);

	plataformas[8] = plataformas[1];
	plataformas[8].transform.position = {-90, -8, 0};
	collPlataformas[8] = collPlataformas[1];
	collPlataformas[8].id = 8;
	plataformas[8].SetCollider(collPlataformas[8]);

	plataformas[9] = plataformas[1];
	plataformas[9].transform.position = { -96, -4, 0 };
	collPlataformas[9] = collPlataformas[1];
	collPlataformas[9].id = 9;
	plataformas[9].SetCollider(collPlataformas[9]);

	plataformas[10] = plataformas[1];
	plataformas[10].transform.position = { -102, 0, 0 };
	collPlataformas[10] = collPlataformas[1];
	collPlataformas[10].id = 10;
	plataformas[10].SetCollider(collPlataformas[10]);

	plataformas[11] = plataformas[1];
	plataformas[11].transform.position = { -110, 0, 0 };
	collPlataformas[11] = collPlataformas[1];
	collPlataformas[11].id = 11;
	plataformas[11].SetCollider(collPlataformas[11]);

	plataformas[12] = plataformas[1];
	plataformas[12].transform.position = { -118, 0, 0 };
	collPlataformas[12] = collPlataformas[1];
	collPlataformas[12].id = 12;
	plataformas[12].SetCollider(collPlataformas[12]);

	//plataforma redonda pequena
	plataformas[4] = FsMesh("Models/plataforma3.obj");
	plataformas[4].LoadMesh();
	plataformas[4].material.LoadTexture("Textures/plataforma3.png");
	plataformas[4].material.bind_TexToColor = true;
	plataformas[4].material.color = {0.5f,0.5f,0.5f};
	plataformas[4].transform = { {-50.5f, -5.0f, 0.0f}, {0,0,0},{1,1,1 } };
	plataformas[4].material.ambient = { 0.1f, 0.1f, 0.1f };
	plataformas[4].material.specular = { 0.1f, 0.1f, 0.1f };
	plataformas[4].material.shineness = 5;
	//Collider 
	collPlataformas[4] = FsCollider({ 1.3f,0,1.0f }, { -1.3f,-0.25f,-1.0f });
	collPlataformas[4].id = 4;
	plataformas[4].SetCollider(collPlataformas[4]);

	plataformas[5] = plataformas[4];
	plataformas[5].transform.position = {-56, -2.5f, 0};
	collPlataformas[5] = collPlataformas[4];
	collPlataformas[5].id = 5;
	plataformas[5].SetCollider(collPlataformas[5]);

	plataformas[6] = plataformas[4];
	plataformas[6].transform.position = {-64, -7,0};
	collPlataformas[6] = collPlataformas[4];
	collPlataformas[6].id = 6;
	plataformas[6].SetCollider(collPlataformas[6]);

	//plataforma final------------------
	plataformas[13] = FsMesh("Models/plataforma4.obj");
	plataformas[13].LoadMesh();
	plataformas[13].material.LoadTexture("Textures/plataforma4.png");
	plataformas[13].material.bind_TexToColor = true;
	plataformas[13].material.color = { 0.5f,0.5f,0.5f };
	plataformas[13].transform = { {-128.0f, -10.0f, 0.0f}, {0,0,0},{1,1,1 } };
	plataformas[13].material.ambient = { 0.1f, 0.1f, 0.1f };
	plataformas[13].material.specular = { 0.1f, 0.1f, 0.1f };
	plataformas[13].material.shineness = 5;
	//Collider 
	collPlataformas[13] = FsCollider({ 2.0f,2,2.0f }, { 1.3f,0.25f,1.0f });
	collPlataformas[13].id = 13;
	plataformas[13].SetCollider(collPlataformas[13]);
	}

	//-----referencia mallas coliders-------
	colMax2 = FsMesh("Models/fSphere.obj");
	colMax2.LoadMesh();
	colMax2.material.type = TypeMaterial::Unlit;
	colMax2.material.color = { 1,1,1 };
	colMin2 = colMax2;
	colMin2.material.type = TypeMaterial::Unlit;
	colMin2.material.color = { 1.0f,0.0f,0.0f };

	//==============Monedas=======================
	if (true) {
		monedas[0] = FsMesh("Models/dona.obj");
		monedas[0].LoadMesh();
		monedas[0].material.type = TypeMaterial::Unlit;
		monedas[0].material.color = { 0.9f,0.4f,0.19f };
		monedas[0].transform = { {-5, -3,0}, {0,90,0},{0.5f,0.5f,0.5f} };
		collMonedas[0] = FsCollider({ 0.5f,0.5f,0.5f }, { -0.5f,-0.5f,-0.5f });
		collMonedas[0].id = 0;
		monedas[0].SetCollider(collMonedas[0]);

		monedas[1] = monedas[0];
		monedas[1].transform.position = { -13,-3,0 };
		collMonedas[1] = collMonedas[0];
		collMonedas[1].id = 1;
		monedas[1].SetCollider(collMonedas[1]);

		monedas[2] = monedas[0];
		monedas[2].transform.position = { -20,-3,0 };
		collMonedas[2] = collMonedas[0];
		collMonedas[2].id = 2;
		monedas[2].SetCollider(collMonedas[2]);

		monedas[3] = monedas[0];
		monedas[3].transform.position = { -29,-1,0 };
		collMonedas[3] = collMonedas[0];
		collMonedas[3].id = 3;
		monedas[3].SetCollider(collMonedas[3]);

		monedas[4] = monedas[0];
		monedas[4].transform.position = { -35,1,0 };
		collMonedas[4] = collMonedas[0];
		collMonedas[4].id = 4;
		monedas[4].SetCollider(collMonedas[4]);

		monedas[5] = monedas[0];
		monedas[5].transform.position = { -43,-3,0 };
		collMonedas[5] = collMonedas[0];
		collMonedas[5].id = 5;
		monedas[5].SetCollider(collMonedas[5]);

		monedas[6] = monedas[0];
		monedas[6].transform.position = { -50,-3,0 };
		collMonedas[6] = collMonedas[0];
		collMonedas[6].id = 6;
		monedas[6].SetCollider(collMonedas[6]);

		monedas[7] = monedas[0];
		monedas[7].transform.position = { -56,-1,0 };
		collMonedas[7] = collMonedas[0];
		collMonedas[7].id = 7;
		monedas[7].SetCollider(collMonedas[7]);

		monedas[8] = monedas[0];
		monedas[8].transform.position = { -64,-6,0 };
		collMonedas[8] = collMonedas[0];
		collMonedas[8].id = 8;
		monedas[8].SetCollider(collMonedas[8]);

		monedas[9] = monedas[0];
		monedas[9].transform.position = { -77,-10,0 };
		collMonedas[9] = collMonedas[0];
		collMonedas[9].id = 9;
		monedas[9].SetCollider(collMonedas[9]);

		monedas[10] = monedas[0];
		monedas[10].transform.position = { -90,-6,0 };
		collMonedas[10] = collMonedas[0];
		collMonedas[10].id = 10;
		monedas[10].SetCollider(collMonedas[10]);

		monedas[11] = monedas[0];
		monedas[11].transform.position = { -96,-2,0 };
		collMonedas[11] = collMonedas[0];
		collMonedas[11].id = 11;
		monedas[11].SetCollider(collMonedas[11]);

		monedas[12] = monedas[0];
		monedas[12].transform.position = { -102,2,0 };
		collMonedas[12] = collMonedas[0];
		collMonedas[12].id = 12;
		monedas[12].SetCollider(collMonedas[12]);

		monedas[13] = monedas[0];
		monedas[13].transform.position = { -110,2,0 };
		collMonedas[13] = collMonedas[0];
		collMonedas[13].id = 13;
		monedas[13].SetCollider(collMonedas[13]);

		monedas[14] = monedas[0];
		monedas[14].transform.position = { -118,2,0 };
		collMonedas[14] = collMonedas[0];
		collMonedas[14].id = 14;
		monedas[14].SetCollider(collMonedas[14]);
	}
	

	//=================SKYBOX======================
	std::vector<std::string> caras = {
	"Textures/Sk_GalaxyRt.png",
	"Textures/Sk_GalaxyLf.png",
	"Textures/Sk_GalaxyUp.png",
	"Textures/Sk_GalaxyDn.png",
	"Textures/Sk_GalaxyBk.png",
	"Textures/Sk_GalaxyFt.png"
	};

	sky = FsSkybox(caras);
	sky.Load();

	//===================== TEXTO =====================

	texto1= FsText("Fonts/SpaceMission-rgyw9.otf", 50, "P r e s s  S p a c e", FsVector2(150, 500), FsVector3(1, 0, 1));
	texto3 = FsText("Fonts/SpaceMission-rgyw9.otf", 50, "A - D  t o  m o v e", FsVector2(150, 400), FsVector3(1, 0, 1));
	texto2= FsText("Fonts/waltographUI.ttf", 50, std::to_string(puntos), FsVector2(20, 520), FsVector3(1, 1, 1));

	//LUZCES================
	luzDireccional = FsDireciontalLight(
		FsVector3(0.2f, -1, 0.2f),
		FsVector3(2, 2, 2),
		FsVector3(0.7f, 0.7f, 0.7f),
		FsVector3(0.5f, 0.5f, 0.5f));
	luzDireccional.Load();

	pointLight[0] = FsPointLight(
		FsVector3(1, 1, 1),
		colorVida,
		FsVector3(1.0f, 1.5f, 1.5f),
		//player.transform.position,
		FsVector3(0,-4,0),
		2,0.0f,0.0f
	);
	pointLight[0].Load();
}



void Plataformas::Update(float deltaTime, float time) {

	

	

	if (vidasPlayer==3) {
		moveLinear = (sin(2 * time) / 4) + 0.25f;
	}
	if (vidasPlayer == 2) {
		moveLinear = (sin(4 * time) / 4) + 0.25f;
	}
	if (vidasPlayer == 1) {
		moveLinear = (sin(6 * time) / 4) + 0.25f;
	}
	
	Control2D(player.transform, deltaTime, time);
	//if (teclas[86]) { // v
	//	swCam = !swCam;
	//	teclas[86] = false;
	//}
	//if (!swCam)	Control2D(player.transform, deltaTime, time);
	//else ControlTPS(player.transform, deltaTime, time);

	//===========================FISICA================================
	//detector colisiones---------------------------
	for each (FsCollider var in collPlataformas)
	{
		if (collPlayer.CheckCollision(var)) {
			indexCollision = var.id;
			if (indexCollision == 13) {
				exit(3);
			}
		} 
	}
	//colisiones moneadas
	for each (FsCollider var in collMonedas)
	{
		if (collPlayer.CheckCollision(var)) {
			indexCollisionMOnedas = var.id;
		}
	}
	
	//gravedad----------------------------
	if (!collPlayer.CheckCollision(collPlataformas[indexCollision])) {
		player.transform.position.y -= 15 * deltaTime;
	}
	//salto---------------
	if (teclas[32]) { // space
		if (collPlayer.CheckCollision(collPlataformas[indexCollision])) {
		teclas[32] = false;
		jump = true;
		jumpLap = time + 0.5f;
		contadorTeclaEspacio++;
		if (contadorTeclaEspacio > 1)contadorTeclaEspacio = 0;
		}
	}
	if (jump && contadorTeclaEspacio==1) {
		teclas[32] = false;
		player.transform.position.y += 22 * deltaTime;
		if (time >= jumpLap) {
			jump = false;
			contadorTeclaEspacio = 0;
		}
	}

	//reinicio--------------
	if (player.transform.position.y < -15) {
		player.transform.position = posInicialPlayer;
		vidasPlayer--;
		if (vidasPlayer==2) {
			colorVida = FsVector3(1,1,0);
		}
		if (vidasPlayer==1) {
			colorVida = FsVector3(1, 0, 0);
		}
		if (vidasPlayer==0) {
			exit(3);
		}
	}
	
	//movimiento ocsilaTORIO PLATAFORMAS 4,5,6
	if (moveOsci) {
		movePlataform += 0.01f;
	}
	else {
		movePlataform -= 0.01f;
	}

	if (movePlataform <= -3) {
		moveOsci = true;
	}
	if (movePlataform>=3) {
		moveOsci = false;
	}
	//direccion de colision-------------------------
	float repulsion = 5.0f;
	if (collPlayer.GetDirection(collPlataformas[indexCollision])==CollisionDirection::RIGHT){
		player.transform.position.x += repulsion *deltaTime;
	}

	if (collPlayer.GetDirection(collPlataformas[indexCollision]) == CollisionDirection::LEFT) {
		player.transform.position.x -= repulsion * deltaTime;
	}

	if (collPlayer.GetDirection(collPlataformas[indexCollision]) == CollisionDirection::UP) {
		player.transform.position.y += 0.0f * deltaTime;
		if (indexCollision == 4) {
			player.transform.position.y += movePlataform * deltaTime;
		}

		if (indexCollision == 5) {
			player.transform.position.y -= movePlataform * deltaTime;
		}

		if (indexCollision == 6) {
			player.transform.position.y += movePlataform * deltaTime;
		}
	}

	if (collPlayer.GetDirection(collPlataformas[indexCollision]) == CollisionDirection::DOWN) {
		player.transform.position.y -= repulsion * deltaTime;
	}

	if (collPlayer.GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::RIGHT || collPlayer.GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::UP || collPlayer.GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::DOWN || collPlayer.GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::LEFT) {
		if (indexCollisionMOnedas == 0) {
			if (monedas[0].on) {
				puntos+=10;
			}
			monedas[0].on = false;
		} 
		if (indexCollisionMOnedas == 1) {
			if (monedas[1].on) {
				puntos+=10;
			}
			monedas[1].on = false;
		} 
		if (indexCollisionMOnedas == 2) {
			if (monedas[2].on) {
				puntos+=10;
			}
			monedas[2].on = false;
		} 
		if (indexCollisionMOnedas == 3) {
			if (monedas[3].on) {
				puntos += 10;
			}
			monedas[3].on = false;
		}
		if (indexCollisionMOnedas == 4) {
			if (monedas[4].on) {
				puntos += 10;
			}
			monedas[4].on = false;
		}
		if (indexCollisionMOnedas == 5) {
			if (monedas[5].on) {
				puntos += 10;
			}
			monedas[5].on = false;
		}

		if (indexCollisionMOnedas == 6) {
			if (monedas[6].on) {
				puntos += 10;
			}
			monedas[6].on = false;
		}
		if (indexCollisionMOnedas == 7) {
			if (monedas[7].on) {
				puntos += 10;
			}
			monedas[7].on = false;
		}
		if (indexCollisionMOnedas == 8) {
			if (monedas[8].on) {
				puntos += 10;
			}
			monedas[8].on = false;
		}
		if (indexCollisionMOnedas == 9) {
			if (monedas[9].on) {
				puntos += 10;
			}
			monedas[9].on = false;
		}
		if (indexCollisionMOnedas == 10) {
			if (monedas[10].on) {
				puntos += 10;
			}
			monedas[10].on = false;
		}
		if (indexCollisionMOnedas == 11) {
			if (monedas[11].on) {
				puntos += 10;
			}
			monedas[11].on = false;
		}
		if (indexCollisionMOnedas == 12) {
			if (monedas[12].on) {
				puntos += 10;
			}
			monedas[12].on = false;
		}
		if (indexCollisionMOnedas == 13) {
			if (monedas[13].on) {
				puntos += 10;
			}
			monedas[13].on = false;
		}
		if (indexCollisionMOnedas == 14) {
			if (monedas[14].on) {
				puntos += 10;
			}
			monedas[14].on = false;
		}


	}


	//colMax1.transform.position = collMonedas[0].GetMax();
	//colMin1.transform.position = collMonedas[0].GetMin();
	//colMax1.Render();
	//colMin1.Render();
	//colMax2.transform.position = collPlataformas[0].GetMax();
	//colMin2.transform.position = collPlataformas[0].GetMin();
	//colMax2.Render();
	//colMin2.Render();
	//refLeft.transform.position = collPlayer.GetUp();
	//refLeft.Render();
	//refRight.transform.position = collPlataformas[1].GetDown();
	//refRight.Render();
	
	orbitar(-10, 10, mLuzPlayer.transform, player.transform, deltaTime, time,  20);
	mLuzPlayer.material.color = colorVida;
	mLuzPlayer.Render();
	pointLight[0].SetDiffuse(colorVida);
	pointLight[0].SetLinear(moveLinear);
	pointLight[0].SetPosition(player.transform.position);

	player.Render();

	plataformas[0].Render();
	complemento0.Render();
	plataformas[1].Render();
	plataformas[2].Render();
	plataformas[3].Render();
	plataformas[4].transform.position.y += movePlataform * deltaTime;
	plataformas[4].Render();
	plataformas[5].transform.position.y -= movePlataform * deltaTime;
	plataformas[5].Render();
	plataformas[6].transform.position.y += movePlataform * deltaTime;
	plataformas[6].Render();
	plataformas[7].Render();
	plataformas[8].Render();
	plataformas[9].Render();
	plataformas[10].Render();
	plataformas[11].Render();
	plataformas[12].Render();
	plataformas[13].Render();


	monedas[0].transform.rotation.y += 0.2f;
	monedas[0].Render();
	monedas[1].transform.rotation.y += 0.2f;
	monedas[1].Render();
	monedas[2].transform.rotation.y += 0.2f;
	monedas[2].Render();
	monedas[3].transform.rotation.y += 0.2f;
	monedas[3].Render();
	monedas[4].transform.rotation.y += 0.2f;
	monedas[4].Render();
	monedas[5].transform.rotation.y += 0.2f;
	monedas[5].Render();
	monedas[6].transform.rotation.y += 0.2f;
	monedas[6].Render();
	monedas[7].transform.rotation.y += 0.2f;
	monedas[7].Render();
	monedas[8].transform.rotation.y += 0.2f;
	monedas[8].Render();
	monedas[9].transform.rotation.y += 0.2f;
	monedas[9].Render();
	monedas[10].transform.rotation.y += 0.2f;
	monedas[10].Render();
	monedas[11].transform.rotation.y += 0.2f;
	monedas[11].Render();
	monedas[12].transform.rotation.y += 0.2f;
	monedas[12].Render();
	monedas[13].transform.rotation.y += 0.2f;
	monedas[13].Render();
	monedas[14].transform.rotation.y += 0.2f;
	monedas[14].Render();

	if (!iniciar) {
		texto1.Render();
		texto3.Render();
	} 

	texto2.Render();
	texto2.SetText(std::to_string(puntos));

}

