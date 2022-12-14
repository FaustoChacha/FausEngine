#include"Jugador.h"


Jugador::Jugador()
{
	//transform = &malla.transform;
	transform.reset(&mallaJugador.transform);
	//gameReference = new UserGame;
	gameReference.reset(new UserGame);
	numeroVidas = 3;
	coloresVida[0] = { 1,0,0 };
	coloresVida[1] = { 1,1,0 };
	coloresVida[2] = { 0,1,0 };
	
}

void Jugador::ControlFPS(float dt, float time) {

	CamaraFPS(dt, time);

	//Teclado
	float velocidad = 3.0f;
	if (gameReference->GetKeys()[32]) {//space
		velocidad = 15;
	}
	if (gameReference->GetKeys()[87]) { // tecla W
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() += gameReference->GetCamera()->GetForward() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeys()[83]) { // tecla S
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() -= gameReference->GetCamera()->GetForward() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeys()[65]) { // tecla A
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() -= gameReference->GetCamera()->GetRight() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeys()[68]) { // tecla D
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() += gameReference->GetCamera()->GetRight() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeys()[69]) { // tecla E
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() += gameReference->GetCamera()->GetUp() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
	if (gameReference->GetKeys()[81]) { // tecla Q
		FsVector3 posicion = gameReference->GetCamera()->GetPosition() -= gameReference->GetCamera()->GetUp() * dt * velocidad;
		gameReference->GetCamera()->SetPosition(posicion);
	}
}

void Jugador::ControlTPS( float dt, float t) {

	FsVector3* targetPos = &mallaJugador.transform.position;
	CamaraTPS(dt, t);
	auto ca = gameReference->GetCamera();


	//Vector perpecdicular al frente
	FsVector3 dirForward = FsVector3::Normalize({ 10 * cos(ca->GetPitch()) * sin(ca->GetYaw()), 0, 10 * cos(ca->GetPitch()) * cos(ca->GetYaw()) });
	FsVector3 dirRight = { dirForward.z,0 ,-dirForward.x };


	//Teclado, mientras presiona tecla:
	float velocidad = 10.0f;
	if (gameReference->GetKeys()[87]) //  W
	{
		*targetPos -= dirForward * dt * velocidad;
	}

	if (gameReference->GetKeys()[83])  // S
	{
		*targetPos += dirForward * dt * velocidad;
	}


	if (gameReference->GetKeys()[65])  // A
	{
		*targetPos -= dirRight * dt * velocidad;
	}


	if (gameReference->GetKeys()[68])  // D
	{
		*targetPos += dirRight * dt * velocidad;
	}

	if (gameReference->GetKeys()[32]) { // space
		gameReference->GetKeys()[32] = false;
	}

}

void Jugador::Control2D(float dt, float t) {
	auto cam = gameReference->GetCamera();
	FsVector3 pos = { mallaJugador.transform.position.x, 0, -12 };
	cam->SetPosition(pos);
	cam->SetTarget(mallaJugador.transform.position);

	auto teclas = gameReference->GetKeys();
	auto postemp = mallaJugador.transform.position;



	if (teclas[68]) { // D
		mallaJugador.transform.rotation.y -= 0.35f; // animacion
		mallaJugador.transform.position.x -= 5 * dt;

	}

	if (teclas[65]) { //A
		mallaJugador.transform.rotation.y += 0.35f; //animacion
		mallaJugador.transform.position.x += 5 * dt;

	}

	if (teclas[32]) { // space--+
		if (colision) {
			teclas[32] = false;
			saltar = true;
			timpoSalto = t + 0.5f;
			contadorTeclaEspacio++;
			if (contadorTeclaEspacio > 1)contadorTeclaEspacio = 0;
		}
	}
	if (saltar && contadorTeclaEspacio == 1) {
		teclas[32] = false;
		transform->position.y += poderSalto * dt;
		if (t >= timpoSalto) {
			saltar = false;
			contadorTeclaEspacio = 0;
		}
	}

}

void Jugador::CamaraFPS( float dt, float t)
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

void Jugador::CamaraTPS(float dt, float t)
{
	FsVector3* targetPos = &mallaJugador.transform.position;
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

void Jugador::OrbitarLuz(float offsetX, float offsetY, float dt, float t, float vel)
{
	mallaLuzOrbital.transform.rotation.y -= FsVector3::toRadians(offsetX) * vel * dt;
	mallaLuzOrbital.transform.rotation.x -= FsVector3::toRadians(offsetY) * vel * dt;
	float distancia = 0.75f;
	mallaLuzOrbital.transform.position.x = mallaJugador.transform.position.x + distancia * cos(mallaLuzOrbital.transform.rotation.x) * sin(mallaLuzOrbital.transform.rotation.y);
	mallaLuzOrbital.transform.position.y = mallaJugador.transform.position.y + distancia * sin(mallaLuzOrbital.transform.rotation.x);
	mallaLuzOrbital.transform.position.z = mallaJugador.transform.position.z - distancia * cos(mallaLuzOrbital.transform.rotation.x) * cos(mallaLuzOrbital.transform.rotation.y);
}

void Jugador::SetColorLuz(FsVector3 color)
{
	mallaLuzOrbital.material.color = color;
}

void Jugador::Init(bool &col) {
	colision = &col;

	//jugador
	posInicialPlayer = { 0,3,0 };
	mallaJugador = FsMesh("Models/player-ball.obj");
	mallaJugador.LoadMesh();
	mallaJugador.material.LoadTexture("Textures/player-ball.png");
	mallaJugador.material.bind_TexToColor = true;
	mallaJugador.material.color = { 0.9f,1.0f,0.9f };
	mallaJugador.material.ambient = { 0.1f, 0.1f, 0.1f };
	mallaJugador.material.specular = { 0.5f, 0.5f, 0.5f };
	mallaJugador.material.shineness = 0.5f;
	mallaJugador.transform = { posInicialPlayer, {-90,0,0},{0.8f,0.8f,0.8f} };
	//collider jugador
	collider = FsCollider({ 0.6f,0.75f,0.75f }, { -0.6f,-0.8f,-0.75f });
	mallaJugador.SetCollider(collider);

	//malla luz orbital
	mallaLuzOrbital = FsMesh("Models/fSphere.obj");
	mallaLuzOrbital.LoadMesh();
	mallaLuzOrbital.material.type = TypeMaterial::Unlit;
	mallaLuzOrbital.material.color = coloresVida[2];
	mallaLuzOrbital.transform.scale = { 0.5f,0.5f,0.5f };

	//luz puntual
	luzPuntual = FsPointLight(
		FsVector3(1, 1, 1),
		FsVector3(1,0,0),
		FsVector3(1.0f, 1.5f, 1.5f),
		//player.transform.position,
		FsVector3(0, 3, 0),
		2, 0.0f, 0.0f
	);
	luzPuntual.Load();
}

void Jugador::Update(bool pausa, float dt, float t, bool col) {
	//colision = col;
	if (!pausa) {
		Control2D(dt, t);
		OrbitarLuz(-10, 10, dt, t, 20);

		
		if (numeroVidas == 3) {
			luzPuntual.SetLinear((sin(2 * t) / 4) + 0.25f);
			luzPuntual.SetDiffuse(coloresVida[2]);
			mallaLuzOrbital.material.color = coloresVida[2];
		}
		if (numeroVidas == 2) {
			luzPuntual.SetLinear((sin(4 * t) / 4) + 0.25f);
			luzPuntual.SetDiffuse(coloresVida[1]);
			mallaLuzOrbital.material.color = coloresVida[1];
		}
		if (numeroVidas == 1) {
			luzPuntual.SetLinear((sin(6 * t) / 4) + 0.25f);
			luzPuntual.SetDiffuse(coloresVida[0]);
			mallaLuzOrbital.material.color = coloresVida[0];
		}
		if (numeroVidas == 0) {
			exit(3);
		}

		//reinicio--------------
		if (transform->position.y < -15) {
			transform->position = posInicialPlayer;
			numeroVidas--;
		}

	}


	luzPuntual.SetPosition(transform->position);
	mallaLuzOrbital.Render();
	mallaJugador.Render();
}

FsCollider Jugador::GetCollider() {
	return collider;
}

void Jugador::SetNumVidas(int n) {
	numeroVidas = n;
}

int Jugador::GetNumVidas() {
	return numeroVidas;
}



Jugador::~Jugador()
{
	//delete gameReference;
}