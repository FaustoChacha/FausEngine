#include"Escenario.h"

void MouseControl(float xMouseOffset, float yMouseOffset, FsCamera* cam) {
	float velocidad = 0.2f;

	xMouseOffset *= velocidad;
	yMouseOffset *= velocidad;

	auto yaw = cam->GetYaw();
	yaw += xMouseOffset;
	cam->SetYaw(yaw);

	auto pitch = cam->GetPitch();
	pitch += yMouseOffset;
	cam->SetPitch(pitch);

	if (cam->GetPitch() > 89.0f) {
		cam->SetPitch(89.0);
	}
	if (cam->GetPitch() < -89.0f) {
		cam->SetPitch(-89.0);
	}

	//Para Primera persona, por el momento
	cam->updateCameraVectors();

}




//---------------------------------------ESCENARIO4---------------------------------------------------

Escenario4::Escenario4()
{
}

Escenario4::~Escenario4()
{
}

void Escenario4::ControlesJugador(float dt, float time) {
	//Teclado
	float velocidad = 0.6f;
	if (gamereference->GetKeys()[32]) {//space
		velocidad = 5;
	}
	//codigo ASCII
	if (gamereference->GetKeys()[87]) { // tecla W
		FsVector3 posicion =
			gamereference->GetCamera()->GetCameraPosition() +=
			gamereference->GetCamera()->getForward() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[83]) { // tecla S
		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getForward() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[65]) { // tecla A
		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getRight() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[68]) { // tecla D
		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() += gamereference->GetCamera()->getRight() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[69]) { // tecla E
		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() += gamereference->GetCamera()->getUp() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}
	if (gamereference->GetKeys()[81]) { // tecla Q
		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getUp() * dt * velocidad;
		gamereference->GetCamera()->SetPosition(posicion);
	}


	//Primera persona
	MouseControl(gamereference->GetMouseX(), gamereference->GetMouseY(), gamereference->GetCamera());

	//Editor.........................
	//Posicion camara!
	if (gamereference->GetKeys()[80]) {
		std::cout << "Posicion: " <<
			gamereference->GetCamera()->GetCameraPosition().x << ", " <<
			gamereference->GetCamera()->GetCameraPosition().y << ", " <<
			gamereference->GetCamera()->GetCameraPosition().z << std::endl;
		std::cout << "Direccion: " <<
			gamereference->GetCamera()->GetRoll() << ", " <<
			gamereference->GetCamera()->GetYaw() << ", " <<
			gamereference->GetCamera()->GetPitch() << std::endl;
		gamereference->GetKeys()[80] = false;
	}
}

void Escenario4::Begin() {

	//piso
	mPiso= FsMesh(PathGame+"/Models/plane.obj");
	mPiso.LoadMesh();
	mPiso.material.LoadTexture(PathGame+"/Textures/Piso/PisoArena.png");
	mPiso.meshTransform = FsTransform({ 0, 0, 0 }, { 0,0,0 }, { 10,1,10 });
	mPiso.material.ambient = { 0.7f, 0.7f, 0.7f };
	mPiso.material.specular = { 0.01f, 0.01f, 0.01f };
	mPiso.material.shineness = 1;

	//Nave
	mNave = FsMesh(PathGame + "/Models/nave/nave.obj");
	mNave.LoadMesh();
	mNave.material.LoadTexture(PathGame + "/Models/nave/nave.jpg");
	mNave.meshTransform = { {-15.0f, 0.0f, 0.0f}, {0,0,0},{0.5f,0.5f,0.5f} };
	//mNave.material.ambient = { 1.1f, 1.1f, 1.1f };
	//mNave.material.specular = { 1.0f, 1.1f, 1.1f };
	//mNave.material.shineness = 500.0f;

	//caja
	mCaja = FsMesh(PathGame+"/Models/caja.obj");
	mCaja.LoadMesh();
	mCaja.material.LoadTexture(PathGame+"/Textures/acajaTex.jpg");
	mCaja.meshTransform = { {15.0f, 0.0f, 0.0f}, {0,0,0},{0.5f,0.5f,0.5f } };
	//mCaja.material.ambient = { 0.1f, 0.1f, 0.1f };
	//mCaja.material.specular = { 0.1f, 0.1f, 0.1f };
	//mCaja.material.shineness = 5;

	//==================mallas para luces de referencia========================
	esferaLuz1 = FsMesh(PathGame+"/Models/sphere.obj");
	esferaLuz1.LoadMesh();
	esferaLuz1.material.type = TypeMaterial::Unlit;
	esferaLuz1.material.color = { 0,1,0 };
	esferaLuz1.meshTransform = { {5, 1, 0},{0,0,0},{1,1,1} };
	
	esferaLuz2 = esferaLuz1;
	esferaLuz2.material.color = { 1,0,0 };
	esferaLuz2.meshTransform.position = { -5, 1, 0 };
	
	esferaLuz3 = esferaLuz1;
	esferaLuz3.material.color = { 0,0,1 };
	esferaLuz3.meshTransform.position = { 0, 1, 5 };

	conoLuz1 = FsMesh("../../../../ejemplo/Models/Cono.obj");
	conoLuz1.LoadMesh();
	conoLuz1.material.type = TypeMaterial::Unlit;
	conoLuz1.meshTransform.position = { 0, 3, 0 };
	conoLuz1.meshTransform.rotation = { 0, -1, 0 };
	conoLuz1.material.color = { 1, 0, 0 };

	conoLuz2 = conoLuz1;
	conoLuz2.meshTransform.position = { 0, 3, -5 };
	conoLuz2.material.color = { 0, 1, 0 };

	conoLuz3 = conoLuz1;
	conoLuz3.meshTransform.position = { 0, 3, -10 };
	conoLuz3.material.color = { 0, 0, 1 };

	//luces
	luzDireccional = FsDireciontalLight(FsVector3(0.0f, -0.4f, -0.17f), FsVector3(2, 2, 2), FsVector3(0.5f, 0.5f, 0.5f), FsVector3(0.5f, 0.5f, 0.5f));
	luzDireccional.Load();

	//Pointlights
	pointLight[0] = FsPointLight(
		FsVector3(1, 1.0f, 1.0f), esferaLuz1.material.color, FsVector3(1.0f, 1.0f, 1.0f), esferaLuz1.meshTransform.position, 1,0.22f, 0);
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


void Escenario4::Update(float deltaTime, float time) {
	ControlesJugador(deltaTime, time);
	esferaLuz1.meshTransform.position.z = 5 * sin(5 * time);
	
	mPiso.Render();
	mNave.Render();
	mCaja.Render();

	esferaLuz1.Render();
	pointLight[0].GetPosition()->z = esferaLuz1.meshTransform.position.z;

	// Point Light 2
	esferaLuz2.Render();

	// Point Light 3
	esferaLuz3.Render();

	//Spot light 1
	conoLuz1.Render();

	//Spot light 2
	conoLuz2.Render();

	//Spot light 3
	conoLuz3.Render();

}




