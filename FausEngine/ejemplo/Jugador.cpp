#include"Jugador.h"


Jugador::Jugador()
{
	//transform = &malla.transform;
	//transform.reset(&mallaJugador.transform);
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

void Jugador::ControlTPS( float dt, float t) {

	FsVector3* targetPos = &mallaJugador.GetTransform().position;
	CamaraTPS(dt, t);
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

void Jugador::Control2D(float dt, float t) {
	auto cam = gameReference->GetCamera();
	
	
	FsVector3 pos = { mallaJugador.GetTransform().position.x, 0, -12 };
	cam->SetPosition(pos);
	//cam->SetTarget(mallaJugador.transform.position);
	cam->SetTarget(mallaJugador.GetTransform().position);

	if (gameReference->GetKeyPress(Keys::D)) { // D
		//mallaJugador.transform.rotation.y -= 0.35f; // animacion
		//mallaJugador.transform.position.x -= 5 * dt;
		mallaJugador.SetRotation({ mallaJugador.GetTransform().rotation.x,
			mallaJugador.GetTransform().rotation.y - 0.35f,
			mallaJugador.GetTransform().rotation.z }); //animacion
		//mallaJugador.transform.position.x += 5 * dt;
		mallaJugador.SetPosition({ mallaJugador.GetTransform().position.x - 5 * dt,
			mallaJugador.GetTransform().position.y,
			mallaJugador.GetTransform().position.z });

	}

	if (gameReference->GetKeyPress(Keys::A)) { //A
		//mallaJugador.transform.rotation.y += 0.35f; //animacion
		mallaJugador.SetRotation({ mallaJugador.GetTransform().rotation.x, 
			mallaJugador.GetTransform().rotation.y + 0.35f, 
			mallaJugador.GetTransform().rotation.z }); //animacion
		//mallaJugador.transform.position.x += 5 * dt;
		mallaJugador.SetPosition({mallaJugador.GetTransform().position.x + 5*dt, 
			mallaJugador.GetTransform().position.y, 
			mallaJugador.GetTransform().position.z});

	}

	if (gameReference->GetKeyPress(Keys::SPACE)) { // space--+
		if (colision) {
			gameReference->SetKeyRelease(Keys::SPACE);
			saltar = true;
			timpoSalto = t + 0.5f;
			contadorTeclaEspacio++;
			if (contadorTeclaEspacio > 1)contadorTeclaEspacio = 0;
		}
	}
	if (saltar && contadorTeclaEspacio == 1) {
		gameReference->SetKeyRelease(Keys::SPACE);
		//transform->position.y += poderSalto * dt;
		mallaJugador.SetPosition({ mallaJugador.GetTransform().position.x, 
			mallaJugador.GetTransform().position.y + poderSalto * dt,
			mallaJugador.GetTransform().position.z
			});
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
	//FsVector3* targetPos = &mallaJugador.transform.position;
	FsVector3* targetPos = &mallaJugador.GetTransform().position;
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
	//ry=ry-n
	//mallaLuzOrbital.transform.rotation.y -= FsVector3::toRadians(offsetX) * vel * dt;
	//mallaLuzOrbital.transform.rotation.x -= FsVector3::toRadians(offsetY) * vel * dt;
	mallaLuzOrbital.SetRotation(
		{mallaLuzOrbital.GetTransform().rotation.x - FsVector3::toRadians(offsetY) * vel * dt,
		mallaLuzOrbital.GetTransform().rotation.y- FsVector3::toRadians(offsetX) * vel * dt,
		mallaLuzOrbital.GetTransform().rotation.z}
	);
		
	float distancia = 0.75f;
	float posX = mallaJugador.GetTransform().position.x + distancia * cos(mallaLuzOrbital.GetTransform().rotation.x) * sin(mallaLuzOrbital.GetTransform().rotation.y);
	float posY= mallaJugador.GetTransform().position.y + distancia * sin(mallaLuzOrbital.GetTransform().rotation.x);
	float posZ = mallaJugador.GetTransform().position.z - distancia * cos(mallaLuzOrbital.GetTransform().rotation.x) * cos(mallaLuzOrbital.GetTransform().rotation.y);
	mallaLuzOrbital.SetPosition({posX, posY, posZ });
}

void Jugador::SetColorLuz(FsVector3 color)
{
	//mallaLuzOrbital.material.color = color;
}

void Jugador::SetPosition(FsVector3 v) {
	mallaJugador.SetPosition(v);
}

FsVector3 Jugador::GetPosition() {
	return mallaJugador.GetTransform().position;
}

void Jugador::Init(bool &col) {
	colision = &col;

	//jugador
	posInicialPlayer = { 0,3,0 };
	mallaJugador.Load("Models/player-ball.obj");
	//mallaJugador.Load();
	matJugador.Load({ 0.1f, 0.1f, 0.1f }, { 0.5f, 0.5f, 0.5f }, { 0.9f,1.0f,0.9f }, 0.5f, "Textures/player-ball.png", true);
	mallaJugador.SetTransform({ posInicialPlayer, {-90,0,0},{0.8f,0.8f,0.8f} });
	mallaJugador.SetMaterial(matJugador);
	//collider jugador
	collider.SetMax({ 0.6f,0.75f,0.75f }); 
	collider.SetMin({ -0.6f, -0.8f, -0.75f });
	mallaJugador.SetCollider(collider);

	//malla luz orbital
	mallaLuzOrbital.Load("Models/fSphere.obj");
	matLuz.Load(coloresVida[2]);
	mallaLuzOrbital.SetScale({ 0.5f,0.5f,0.5f });
	mallaLuzOrbital.SetMaterial(matLuz);

	//luz puntual
	luzPuntual.Load(
		FsVector3(1, 1, 1),
		FsVector3(0,1,0),
		FsVector3(1.0f, 1.5f, 1.5f),
		//player.transform.position,
		FsVector3(0, 3, 0),
		2, 0.0f, 0.0f
	);
}

void Jugador::Update(bool pausa, float dt, float t, bool col) {

	if (!pausa) {
		Control2D(dt, t);
		OrbitarLuz(-10, 10, dt, t, 20);

		
		if (numeroVidas == 3) {
			luzPuntual.SetLinear((sin(2 * t) / 4) + 0.25f);
			luzPuntual.SetDiffuse({0,1,0});
			matLuz.SetColor(coloresVida[2]);
		}
		if (numeroVidas == 2) {
			luzPuntual.SetLinear((sin(4 * t) / 4) + 0.25f);
			luzPuntual.SetDiffuse(coloresVida[1]);
			matLuz.SetColor(coloresVida[1]);
		}
		if (numeroVidas == 1) {
			luzPuntual.SetLinear((sin(6 * t) / 4) + 0.25f);
			luzPuntual.SetDiffuse(coloresVida[0]);
			matLuz.SetColor(coloresVida[0]);
		}
		if (numeroVidas == 0) {
			exit(3);
		}

		//reinicio--------------
		if (mallaJugador.GetTransform().position.y < -15) {
			mallaJugador.SetPosition(posInicialPlayer);
			numeroVidas--;
		}

	}

	luzPuntual.SetPosition(mallaJugador.GetTransform().position);
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