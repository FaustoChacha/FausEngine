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

	shader = FausEngine::FsGame::GetSelfReference()->GetShader();

	//piso
	mPiso.LoadMesh(PathGame+"/Models/plane.obj");
	mPiso.material.LoadTexture(PathGame+"/Textures/Piso/PisoArena.png");
	mPiso.meshTransform = FsTransform({ 0, 0, 0 }, { 0,0,0 }, { 10,1,10 });
	mPiso.material.ambient = { 0.7f, 0.7f, 0.7f };
	mPiso.material.specular = { 0.01f, 0.01f, 0.01f };
	mPiso.material.shineness = 1;

	//barril
	mNave.LoadMesh(PathGame + "/Models/nave/nave.obj");
	mNave.material.LoadTexture(PathGame + "/Models/nave/nave.jpg");
	mNave.meshTransform = { {-15.0f, 0.0f, 0.0f}, {0,0,0},{0.5f,0.5f,0.5f} };
	mNave.material.ambient = { 0.1f, 0.1f, 0.1f };
	mNave.material.specular = { 0.1f, 0.1f, 0.1f };
	mNave.material.shineness = 5;

	//caja
	mCaja.LoadMesh(PathGame+"/Models/caja.obj");
	mCaja.material.LoadTexture(PathGame+"/Textures/cajaTex.jpg");
	mCaja.meshTransform = { {15.0f, 0.0f, 0.0f}, {0,0,0},{0.5f,0.5f,0.5f } };
	mCaja.material.ambient = { 0.1f, 0.1f, 0.1f };
	mCaja.material.specular = { 0.1f, 0.1f, 0.1f };
	mCaja.material.shineness = 5;

	//==================mallas para luces de referencia========================
	esferaLuz1.LoadMesh(PathGame+"/Models/sphere.obj");
	esferaLuz1.material.type = TypeMaterial::Unlit;
	esferaLuz1.material.color = { 0,1,0 };
	esferaLuz1.meshTransform = { {5, 1, 0},{0,0,0},{1,1,1} };
	
	esferaLuz2 = esferaLuz1;
	esferaLuz2.material.color = { 1,0,0 };
	esferaLuz2.meshTransform.position = { -5, 1, 0 };
	
	esferaLuz3 = esferaLuz1;
	esferaLuz3.material.color = { 0,0,1 };
	esferaLuz3.meshTransform.position = { 0, 1, 5 };

	conoLuz1.LoadMesh("../../../../ejemplo/Models/Cono.obj");
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



}


void Escenario4::Update(float deltaTime, float time) {
	ControlesJugador(deltaTime, time);
	esferaLuz1.meshTransform.position.z = 5 * sin(5 * time);
	//mCaja.meshTransform.position.x = sin(time);
	mPiso.Render();
	mNave.Render();
	mCaja.Render();

	shader->SetUniform3f("directionalLight.direction", FsVector3(0.0f, -0.4f, -0.17f));
	shader->SetUniform3f("directionalLight.base.ambient", FsVector3(0.5f, 0.5f, 0.5f));
	shader->SetUniform3f("directionalLight.base.diffuse", FsVector3(0.5f, 0.5f, 0.5f));
	shader->SetUniform3f("directionalLight.base.specular", FsVector3(0.5f, 0.5f, 0.5f));


	esferaLuz1.Render();
	// Point Light 1
	shader->SetUniform3f("pointLights[0].base.ambient", FsVector3(1, 1.0f, 1.0f));
	shader->SetUniform3f("pointLights[0].base.diffuse",	esferaLuz1.material.color);	// verde
	shader->SetUniform3f("pointLights[0].base.specular", FsVector3(1.0f, 1.0f, 1.0f));
	shader->SetUniform3f("pointLights[0].position", esferaLuz1.meshTransform.position);
	shader->SetUniform1f("pointLights[0].constant", 1.0f);
	shader->SetUniform1f("pointLights[0].linear", 0.22f);
	shader->SetUniform1f("pointLights[0].exponent", 0.0f);


	// Point Light 2
	esferaLuz2.Render();
	shader->SetUniform3f("pointLights[1].base.ambient", FsVector3(0.2f, 0.2f, 0.2f));
	shader->SetUniform3f("pointLights[1].base.diffuse",	esferaLuz2.material.color);	//rojo
	shader->SetUniform3f("pointLights[1].base.specular", FsVector3(1.0f, 1.0f, 1.0f));
	shader->SetUniform3f("pointLights[1].position", esferaLuz2.meshTransform.position);
	shader->SetUniform1f("pointLights[1].constant", 1.0f);
	shader->SetUniform1f("pointLights[1].linear", 0.22f);
	shader->SetUniform1f("pointLights[1].exponent", 0.20f);

	// Point Light 3
	esferaLuz3.Render();
	shader->SetUniform3f("pointLights[2].base.ambient", FsVector3(0.2f, 0.2f, 0.2f));
	shader->SetUniform3f("pointLights[2].base.diffuse",	esferaLuz3.material.color);	//rojo
	shader->SetUniform3f("pointLights[2].base.specular", FsVector3(1.0f, 1.0f, 1.0f));
	shader->SetUniform3f("pointLights[2].position", esferaLuz3.meshTransform.position);
	shader->SetUniform1f("pointLights[2].constant", 1.0f);
	shader->SetUniform1f("pointLights[2].linear", 0.22f);
	shader->SetUniform1f("pointLights[2].exponent", 0.20f);


	//Spot light 1
	conoLuz1.Render();
	shader->SetUniform3f("spotLights[0].base.ambient", FsVector3(0.1f, 0.1f, 0.1f));
	shader->SetUniform3f("spotLights[0].base.diffuse", 	conoLuz1.material.color);
	shader->SetUniform3f("spotLights[0].base.specular", FsVector3(1.0f, 1.0f, 1.0f));
	shader->SetUniform3f("spotLights[0].position", conoLuz1.meshTransform.position);
	shader->SetUniform3f("spotLights[0].direction", conoLuz1.meshTransform.rotation);
	shader->SetUniform1f("spotLights[0].constant", 1.0f);
	shader->SetUniform1f("spotLights[0].linear", 0.07f);
	shader->SetUniform1f("spotLights[0].exponent", 0.017f);


	//Spot light 2
	conoLuz2.Render();
	shader->SetUniform3f("spotLights[1].base.ambient", FsVector3(0.1f, 0.1f, 0.1f));
	shader->SetUniform3f("spotLights[1].base.diffuse", conoLuz2.material.color);
	shader->SetUniform3f("spotLights[1].base.specular", FsVector3(1.0f, 1.0f, 1.0f));
	shader->SetUniform3f("spotLights[1].position", 	conoLuz2.meshTransform.position);
	shader->SetUniform3f("spotLights[1].direction", conoLuz2.meshTransform.rotation);
	shader->SetUniform1f("spotLights[1].constant", 1.0f);
	shader->SetUniform1f("spotLights[1].linear", 0.07f);
	shader->SetUniform1f("spotLights[1].exponent", 0.017f);

	//Spot light 3
	conoLuz3.Render();
	shader->SetUniform3f("spotLights[2].base.ambient", FsVector3(0.1f, 0.1f, 0.1f));
	shader->SetUniform3f("spotLights[2].base.diffuse", conoLuz3.material.color);
	shader->SetUniform3f("spotLights[2].base.specular", FsVector3(1.0f, 1.0f, 1.0f));
	shader->SetUniform3f("spotLights[2].position", conoLuz3.meshTransform.position);
	shader->SetUniform3f("spotLights[2].direction", conoLuz3.meshTransform.rotation);
	shader->SetUniform1f("spotLights[2].constant", 1.0f);
	shader->SetUniform1f("spotLights[2].linear", 0.07f);
	shader->SetUniform1f("spotLights[2].exponent", 0.017f);


}




