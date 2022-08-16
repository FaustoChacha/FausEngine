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

//---------------------------------------ESCENARIO4---------------------------------------------------

Escenario4::Escenario4()
{
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

void Escenario4::Begin() {

	//==============================MALLAS======================================
	//piso
	mPiso= FsMesh(PathGame+"/Models/plane.obj");
	mPiso.LoadMesh();
	mPiso.material.LoadTexture(PathGame+"/Textures/Piso/PisoArena.png");
	mPiso.meshTransform = FsTransform({ 0, -0.5f, 0 }, { 0,0,0 }, { 10,1,10 });
	mPiso.material.ambient = { 0.7f, 0.7f, 0.7f };
	mPiso.material.specular = { 0.01f, 0.01f, 0.01f };
	mPiso.material.shineness = 1;

	//Nave
	mNave = FsMesh(PathGame + "/Models/nave/nave.obj");
	//mNave.LoadMesh();
	//mNave.material.LoadTexture(PathGame + "/Models/nave/nave.jpg");
	mNave.meshTransform = { {-15.0f, 0.0f, 0.0f}, {0,0,0},{0.5f,0.5f,0.5f} };
	//mNave.material.ambient = { 1.1f, 1.1f, 1.1f };
	//mNave.material.specular = { 1.0f, 1.1f, 1.1f };
	//mNave.material.shineness = 500.0f;

	//caja
	mCaja = FsMesh(PathGame+"/Models/caja.obj");
	mCaja.LoadMesh();
	mCaja.material.LoadTexture(PathGame+"/Textures/cajaTex.jpg");
	mCaja.meshTransform = { {15.0f, 0.0f, 0.0f}, {0,0,0},{0.5f,0.5f,0.5f } };
	mCaja.material.ambient = { 0.1f, 0.1f, 0.1f };
	mCaja.material.specular = { 0.1f, 0.1f, 0.1f };
	mCaja.material.shineness = 5;

	//======================MOVIMIENTO===========================
	
	cuboX = FsMesh(PathGame + "/Models/fCubo.obj");
	cuboX.LoadMesh();
	cuboX.material.type = TypeMaterial::Unlit;
	cuboX.material.color = {1,0,0};
	cuboX.meshTransform = { {0, 0, 0},{0,0,0},{40,0.05f,0.05f} };

	cuboY = cuboX;
	cuboY.material.color = {0,1,0};
	cuboY.meshTransform = { {0, 0, 0},{0,0,0},{0.05f,40,0.05f} };

	cuboZ = cuboX;
	cuboZ.material.color = { 0,0,1 };
	cuboZ.meshTransform = { {0, 0, 0},{0,0,0},{0.05f,0.05f,40} };

	player= FsMesh(PathGame + "/Models/sphere.obj");
	player.LoadMesh();
	player.material.type = TypeMaterial::Unlit;
	player.material.color = {0.75f,0.1f,0.95f};
	player.meshTransform = { {0,0,0}, {0,0,0},{3,3,3} };

	//==================LUCES========================
	if (true) {
		esferaLuz1 = FsMesh(PathGame + "/Models/sphere.obj");
		esferaLuz1.LoadMesh();
		esferaLuz1.material.type = TypeMaterial::Unlit;
		esferaLuz1.material.color = { 0.8f,0.8f,0.8f };
		//esferaLuz1.meshTransform = { {5, 1, 0},{0,0,0},{1,1,1} };
		esferaLuz1.meshTransform.scale = {3,3,3};

		esferaLuz2 = esferaLuz1;
		esferaLuz2.material.color = { 1,0,0 };
		esferaLuz2.meshTransform.position = { -5, 1, 0 };

		esferaLuz3 = esferaLuz1;
		esferaLuz3.material.color = { 0,0,1 };
		esferaLuz3.meshTransform.position = { 0, 1, 5 };

		conoLuz1 = FsMesh(PathGame + "/Models/Cono.obj");
		conoLuz1.LoadMesh();
		conoLuz1.material.type = TypeMaterial::Unlit;
		conoLuz1.meshTransform.position = { 0, 3, 0 };
		conoLuz1.meshTransform.rotation = { 0, 0, 0 };
		conoLuz1.meshTransform.scale = {2,2,2};
		conoLuz1.material.color = { 1, 1, 1 };

		conoLuz2 = conoLuz1;
		conoLuz2.meshTransform.position = { 0, 3, -5 };
		conoLuz2.material.color = { 0, 1, 0 };

		conoLuz3 = conoLuz1;
		conoLuz3.meshTransform.position = { 0, 3, -10 };
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
			FsVector3(1, 1.0f, 1.0f), esferaLuz1.material.color, FsVector3(1.0f, 1.0f, 1.0f), esferaLuz1.meshTransform.position, 1, 0.22f, 0);
		pointLight[0].Load();

		pointLight[1] = FsPointLight(
			FsVector3(0.2f, 0.2f, 0.2f), esferaLuz2.material.color, FsVector3(1.0f, 1.0f, 1.0f), esferaLuz2.meshTransform.position, 1, 0.22f, 0.2f);
		pointLight[1].Load();

		pointLight[2] = FsPointLight(
			FsVector3(0.2f, 0.2f, 0.2f), esferaLuz3.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			esferaLuz3.meshTransform.position, 1, 0.27f, 0.17f);
		pointLight[2].Load();

		//Spotlights
		spotlight[0] = FsSpotLight(
			FsVector3(0.1f, 0.1f, 0.1f), conoLuz1.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			conoLuz1.meshTransform.position, conoLuz1.meshTransform.rotation, 1.0f, 0.07f, 0.017f);
		spotlight[0].Load();

		spotlight[1] = FsSpotLight(
			FsVector3(0.1f, 0.1f, 0.1f), conoLuz2.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			conoLuz2.meshTransform.position, conoLuz2.meshTransform.rotation, 1.0f, 0.07f, 0.017f);
		spotlight[1].Load();

		spotlight[2] = FsSpotLight(
			FsVector3(0.1f, 0.1f, 0.1f), conoLuz3.material.color, FsVector3(1.0f, 1.0f, 1.0f),
			conoLuz3.meshTransform.position, conoLuz3.meshTransform.rotation, 1.0f, 0.07f, 0.017f);
		spotlight[2].Load();

	}

	
}

void Escenario4::Update(float deltaTime, float time) {
	
	//ControlFPS(deltaTime, time);
	ControlTPS(player.meshTransform, deltaTime, time);
	
	//conoLuz1.meshTransform.position = {5,5,5};
	//conoLuz1.meshTransform.rotation = {45,0,-45};
	conoLuz1.Render();
	cuboX.Render();
	cuboY.Render();
	cuboZ.Render();
	player.Render();
	mPiso.Render();
	mCaja.Render();

}




