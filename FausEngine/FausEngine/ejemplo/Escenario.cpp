#include"Escenario.h"

//Escenario1::Escenario1()
//{
//
//}
//
//void Escenario1::CreacionLuces() {
//	mainLight = FsDirectionalLight(1024, 1024,
//		1.0f, 1.0f, 1.0f,
//		0.05f, 0.05f,
//		0.0f, -15.0f, -10.0f);
//	mainLight.Load();
//
//	FsVector3 posicionPoint0 = FsVector3(0, 12, 2);
//	//izquierda
//	pointLights[0] = FsPointLight(
//		2048, 2048, //sombras
//		0.01, 100, //near, far
//		0.0f, 1.0f, 0.0f, //color
//		1.0f, 1.0f, //ambien diffuse
//		posicionPoint0.x, posicionPoint0.y, posicionPoint0.z, //position
//		-0.4, 0.1f, 0.1f); //constante linael exponente
//	pointLights[0].Load();
//	pointLights[0].SetActive(false);
//
//	//derecha
//	pointLights[1] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		1.0f, 0.5f, 0.0f, //color
//		1.0f, 1.0f, //ambien diffuse
//		posicionPoint0.x, posicionPoint0.y, -posicionPoint0.z, //position
//		-0.4, 0.1f, 0.1f); //constante linael exponente
//	pointLights[1].Load();
//	pointLights[1].SetActive(false);
//
//	//media
//	pointLights[2] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		0.53, 0.12f, 0.47f, //color
//		1.0f, 1.0f, //ambien diffuse
//		-2,11,0, //position
//		-0.1, 0.1f, 0.1f); //constante linael exponente
//	pointLights[2].Load();
//	pointLights[2].SetActive(false);
//
//	//turbinas
//	pointLights[3] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		1.0f, 0.0f, 0.0f, //color
//		1.0f, 1.0f, //ambien diffuse
//		0, -2.5, 0, //position
//		-0.4, 0.05f, 0.05f); //constante linael exponente
//	pointLights[3].Load();
//
//	//punta nave
//	pointLights[4] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		1.0f, 0.0f, 0.0f, //color
//		1.0f, 1.0f, //ambien diffuse
//		0, 18, 0, //position
//		-0.4, 0.05f, 0.05f); //constante linael exponente
//	pointLights[4].Load();
//	pointLights[4].SetActive(false);
//
//	//linterna
//	spotLights[0] = FsSpotLight(
//		1024, 1024, //shadow
//		0.01f, 100.0f, //near far
//		1.0f, 1.0f, 0.5f, //color
//		0.5f, 1, //ambient diffuse
//		0.0f, 10.0f, 0.0f, //position
//		0.0f, -1.0f, 0.0f, //direction
//		1, 0.0f, 0.0f, 25.0f); //const lin exp edg
//	spotLights[0].Load();
//	spotLights[0].SetActive(false);
//
//	FsVector3 posicionSpot1 = FsVector3(30,50,25);
//	float constante = 5;
//	//izquierda
//	spotLights[1] = FsSpotLight(
//		1024, 1024, //shadow
//		0.01f, 100.0f, //near far
//		1.0f, 1.0f, 1, //color
//		0.5f, 1, //ambient diffuse
//		posicionSpot1.x, posicionSpot1.y, posicionSpot1.z, //position
//		-0.65f, -1.0f, -0.5f, //direction
//		constante, 0.0f, 0.0f, 15.0f); //const lin exp edg
//	spotLights[1].Load();
//	spotLights[1].SetActive(false);
//
//	//esferaSpot1 = FsModel(PathGame+"Models/fSphere.obj",pathEngine);
//	//esferaSpot1.LoadModel();
//	esferaSpot1.SetPosition(posicionSpot1 + FsVector3(0,1,0));
//
//	//derecha
//	spotLights[2] = FsSpotLight(
//		1024, 1024, //shadow
//		0.01f, 100.0f, //near far
//		1.0f, 1.0f, 0.5f, //color
//		0.5f, 1, //ambient diffuse
//		30.0f, 50.0f, -25.0f, //position
//		-0.65f, -1.0f, 0.5f, //direction
//		constante, 0.0f, 0.0f, 15.0f); //const lin exp edg
//	spotLights[2].Load();
//	spotLights[2].SetActive(false);
//
//	//linterna cohete
//	spotLights[3] = FsSpotLight(
//		1024, 1024, //shadow
//		0.01f, 100.0f, //near far
//		1.0f, 1.0f, 1.0f, //color
//		0.5f, 1, //ambient diffuse
//		0.25f, -12, 0.0f, //position         
//		0, 1.0f, 0, //direction 
//		0.25f, 0.0f, 0.0f, 10.0f); //const lin exp edg
//	spotLights[3].Load();
//	spotLights[3].SetActive(false);
//
//
//}
//
//void Escenario1::CreacionMallas() {
//	//cuboPiso = FsModel(PathGame + "/Models/PlanoPiso.fbx",
//	//	PathGame + "/Textures/Piso/");
//	//cuboPiso.LoadAuxTexure(PathGame + "/Textures/Piso/PisoArena.png");
//	//cuboPiso.LoadModel();
//	//cuboPiso.SetPosition(FsVector3(0.0f, 0.0f, 0));
//	//cuboPiso.SetRotation(FsVector3(-90.f,0,0));
//	//cuboPiso.SetScale(FsVector3(5.0f, 5.0f, 5));
//
//	//baseNave = FsModel(PathGame + "Models/nave/basenave.obj", pathEngine);
//	//baseNave.LoadAuxTexure(PathGame + "Models/nave/nave.jpg");
//	//baseNave.LoadModel();
//	//baseNave.SetTransform(FsTransform({ 0,0.1f,0 }, { 0,0,0 }, { 0.25f,0.25f,0.25f }));
//
//	//nave = FsModel(PathGame+"Models/nave/nave.obj", PathGame+"Models/nave/");
//	//nave.LoadAuxTexure(PathGame+"Models/nave/nave.jpg");
//	//nave.LoadModel();
//	//nave.SetTransform(FsTransform({0,0.1f,0}, {0,0,0}, {0.25f,0.25f,0.25f}));
//
//}
//
//void Escenario1::Mover(FsPointLight* luz) {
//
//	if (gamereference->GetKeys()[73]) { //i
//		std::cout << "Posicion: " <<luz->GetPosition()->x <<", " <<
//			luz->GetPosition()->y<<", "<<luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x, luz->GetPosition()->y + 0.5f,luz->GetPosition()->z));
//		gamereference->GetKeys()[73] = false;
//
//	}
//	if (gamereference->GetKeys()[74]) { //j
//		std::cout << "Posicion: " << luz->GetPosition()->x << ", " <<
//			luz->GetPosition()->y << ", " << luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x-0.5f, luz->GetPosition()->y, luz->GetPosition()->z));
//		gamereference->GetKeys()[74] = false;
//	}
//	if (gamereference->GetKeys()[75]) { //k
//		std::cout << "Posicion: " << luz->GetPosition()->x << ", " <<
//			luz->GetPosition()->y << ", " << luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x , luz->GetPosition()->y - 0.5f, luz->GetPosition()->z));
//		gamereference->GetKeys()[75] = false;
//
//	}
//	if (gamereference->GetKeys()[76]) { //l
//		std::cout << "Posicion: " << luz->GetPosition()->x << ", " <<
//			luz->GetPosition()->y << ", " << luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x+0.5f, luz->GetPosition()->y - 0.5f, luz->GetPosition()->z));
//		gamereference->GetKeys()[76] = false;
//	}
//
//	
//}
//
//void Escenario1::Mover(FsModel* model) {
//
//	if (gamereference->GetKeys()[73]) { //i
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//			model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//		model->SetPosition(FsVector3(
//			model->GetTransform()->position.x, model->GetTransform()->position.y + 0.5f, model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//
//	}
//	if (gamereference->GetKeys()[74]) { //j
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//			model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//		model->SetPosition(FsVector3(
//			model->GetTransform()->position.x-0.5f, model->GetTransform()->position.y, model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//	}
//	if (gamereference->GetKeys()[75]) { //k
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//			model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//		model->SetPosition(FsVector3(
//			model->GetTransform()->position.x, model->GetTransform()->position.y - 0.5f, model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//
//	}
//	if (gamereference->GetKeys()[76]) { //l
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//		model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//
//		model->SetPosition(
//			FsVector3(
//		model->GetTransform()->position.x+0.5f, model->GetTransform()->position.y , 
//				model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//	}
//
//
//}
//
//void Escenario1::Begin()
//{
//	CreacionMallas();
//	CreacionLuces();
//
//	std::vector<std::string> skyboxFaces;
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyRt.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyLf.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/g.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyDn.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyBk.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyFt.png");
//	skybox = FsSkybox(skyboxFaces);
//	skybox.Load();
//
//}
//
//void MouseControl(float xMouseOffset, float yMouseOffset, FsCamera* cam) {
//	float velocidad = 0.2f;
//
//	xMouseOffset *= velocidad;
//	yMouseOffset *= velocidad;
//
//	auto yaw = cam->GetYaw();
//	yaw += xMouseOffset;
//	cam->SetYaw(yaw);
//
//	auto pitch = cam->GetPitch();
//	pitch += yMouseOffset;
//	cam->SetPitch(pitch);
//
//	if (cam->GetPitch() > 89.0f) {
//		cam->SetPitch(89.0);
//	}
//	if (cam->GetPitch() < -89.0f) {
//		cam->SetPitch(-89.0);
//	}
//
//	//Para Primera persona, por el momento
//	cam->updateCameraVectors();
//
//}
//
//void Escenario1::ControlesJugador(float dt, float time) {
//	//Teclado
//	float velocidad = 0.25f;
//	if (gamereference->GetKeys()[32]) {//space
//		velocidad = 5;
//	}
//	//codigo ASCII
//	if (gamereference->GetKeys()[87]) { // tecla W
//		FsVector3 posicion = 
//			gamereference->GetCamera()->GetCameraPosition() += 
//				gamereference->GetCamera()->getForward() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[83]) { // tecla S
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getForward() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[65]) { // tecla A
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getRight() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[68]) { // tecla D
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() += gamereference->GetCamera()->getRight() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[69]) { // tecla E
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() += gamereference->GetCamera()->getUp() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[81]) { // tecla Q
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getUp() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//
//	
//	//Primera persona
//	MouseControl(gamereference->GetMouseX(), gamereference->GetMouseY(), gamereference->GetCamera());
//
//	//Switch Linterna
//	if (gamereference->GetKeys()[70]) { //F 
//		spotLights[0].SetActive(swLinterna);
//		swLinterna = !swLinterna;
//		gamereference->GetKeys()[70] = false;
//	}
//
//	//switch linternas costados
//	if (gamereference->GetKeys()[49]) { //1
//		spotLights[1].SetActive(swLinternasCostados);
//		spotLights[2].SetActive(swLinternasCostados);
//		swLinternasCostados = !swLinternasCostados;
//		gamereference->GetKeys()[49] = false;
//	}
//	//switch puntuales base
//	if (gamereference->GetKeys()[50]) {//2
//		pointLights[0].SetActive(swPuntualesBase);
//		pointLights[1].SetActive(swPuntualesBase);
//		swPuntualesBase = !swPuntualesBase;
//		gamereference->GetKeys()[50] = false;
//	}
//	//switch Puntual media base
//	if (gamereference->GetKeys()[51]) {//3
//		pointLights[2].SetActive(swPuntualMediaBase);
//		swPuntualMediaBase = !swPuntualMediaBase;
//		gamereference->GetKeys()[51] = false;
//	}
//
//	//switch linterna nave
//	if (gamereference->GetKeys()[52]) {//4
//		spotLights[3].SetActive(swLinternaNave);
//		swLinternaNave = !swLinternaNave;
//		gamereference->GetKeys()[52] = false;
//	}
//
//	//nave despegar.....................
//	if (gamereference->GetKeys()[53]) {//5
//		swDespegue = true;
//	}
//
//	if (swDespegue) {
//
//		cont += 0.1f;
//		pointLights[2].SetActive(false);
//
//		if (velocidadNave < 0.05f) velocidadNave=abs(pow(cont, 2))* dt * 0.001f;
//
//		nave.SetPosition(
//			FsVector3(
//			nave.GetTransform()->position.x, 
//			nave.GetTransform()->position.y /*+= dt / 7*/+= velocidadNave,
//			nave.GetTransform()->position.z));
//
//		pointLights[3].SetPosition(FsVector3(nave.GetTransform()->position.x,
//			nave.GetTransform()->position.y-2.0f,
//			nave.GetTransform()->position.z));
//
//		pointLights[3].SetColour(FsVector3(1,1,0));
//		pointLights[4].SetActive(true);
//		pointLights[4].SetPosition(
//			FsVector3(0, pointLights[4].GetPosition()->y += velocidadNave,0));
//		//pointLights[4].SetAttenuation(-abs(sin(time * 5)/2.5f), 0.0f, 0.0f);
//
//		spotLights[3].SetPosition(nave.GetTransform()->position);
//	}
//
//
//
//	//Editor.........................
//	//Posicion camara!
//	if (gamereference->GetKeys()[80]) {
//		std::cout << "Posicion: " << 
//			gamereference->GetCamera()->GetCameraPosition().x <<", "<<
//			gamereference->GetCamera()->GetCameraPosition().y << ", " <<
//			gamereference->GetCamera()->GetCameraPosition().z << std::endl;
//		std::cout << "Direccion: " <<
//			gamereference->GetCamera()->GetRoll() << ", " <<
//			gamereference->GetCamera()->GetYaw() << ", " <<
//			gamereference->GetCamera()->GetPitch() << std::endl;
//		gamereference->GetKeys()[80] = false;
//	}
//}
//
//void Escenario1::mod(float valor) {
//	if (gamereference->GetKeys()[77]) { //M
//		valor += 0.1f;
//		std::cout << "Valor: " << valor << std::endl;
//		gamereference->GetKeys()[77] = false;
//	}
//	if (gamereference->GetKeys()[78]) { //N
//		valor -= 0.1f;
//		std::cout << "Valor: " << valor << std::endl;
//		gamereference->GetKeys()[77] = false;
//	}
//}
//
//
//void Escenario1::Update(float deltaTime, float time) {
//	//Ajuste linterna
//	FsVector3 umbral = gamereference->GetCamera()->GetCameraPosition();
//	umbral.y -= 0.3f;
//	spotLights[0].SetPosition(umbral);
//	spotLights[0].SetDirection(gamereference->GetCamera()->GetCameraDirection());
//	
//	ControlesJugador(deltaTime, time);
//	//Mover(&nave);
//	Mover(&pointLights[4]);
//	pointLights[0].SetAttenuation(sin(time *5)+0.6f,0.2f,0.1f);
//	pointLights[1].SetAttenuation(sin(time * 5 +3) + 0.6f, 0.2f, 0.1f);
//	pointLights[2].SetPosition(FsVector3(-2,4*sin(8*time)+9,0));
//
//
//	esferaPoint0.Render();
//	esferaSpot1.Render(),
//	cuboPiso.Render();
//	baseNave.Render(),
//	nave.Render();
//
//}
//
//Escenario1::~Escenario1(){}
//
//
////----------------------------------------Escenario2--------------------------------------------
//
//Escenario2::Escenario2()
//{
//
//}
//
//void Escenario2::CrearLuces() {
//	mainLight = FsDirectionalLight(1024, 1024,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 0.3f,
//		0.0f, -15.0f, -10.0f);
//	mainLight.Load();
//
//	FsVector3 posicionPoint0 = FsVector3(0, 12, 2);
//
//	//tierra
//	pointLights[0] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		0.6588f, 0.6588f, 0.6588f, //color
//		1.0f, 1.0f, //ambien diffuse
//		0, -30, 0, //position
//		0.0f, 0.05f, 0.05f); //constante linael exponente
//	pointLights[0].Load();
//
//	pointLights[1] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		0,1,0, //color
//		1.0f, 1.0f, //ambien diffuse
//		0, -30, 0, //position
//		0.0f, 0.05f, 0.05f); //constante linael exponente
//	pointLights[1].Load();
//
//	//turbinas
//	pointLights[3] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		1.0f, 1.0f, 0.0f, //color
//		1.0f, 1.0f, //ambien diffuse
//		0, -2.5, 0, //position
//		-0.4, 0.05f, 0.05f); //constante linael exponente
//	pointLights[3].Load();
//
//	//punta nave
//	pointLights[4] = FsPointLight(
//		1024, 1024, //sombras
//		0.01, 100, //near, far
//		1.0f, 0.0f, 0.0f, //color
//		1.0f, 1.0f, //ambien diffuse
//		0, 18, 0, //position
//		-0.4, 0.05f, 0.05f); //constante linael exponente
//	pointLights[4].Load();
//	//pointLights[4].SetActive(false);
//
//	//linterna
//	spotLights[0] = FsSpotLight(
//		1024, 1024, //shadow
//		0.01f, 100.0f, //near far
//		1.0f, 1.0f, 0.5f, //color
//		0.5f, 1, //ambient diffuse
//		0.0f, 10.0f, 0.0f, //position
//		0.0f, -1.0f, 0.0f, //direction
//		1, 0.0f, 0.0f, 25.0f); //const lin exp edg
//	spotLights[0].Load();
//	spotLights[0].SetActive(false);
//
//	
//
//	//linterna cohete
//	spotLights[3] = FsSpotLight(
//		1024, 1024, //shadow
//		0.01f, 100.0f, //near far
//		1.0f, 1.0f, 1.0f, //color
//		0.5f, 1, //ambient diffuse
//		0.25f, -12, 0.0f, //position         
//		0, 1.0f, 0, //direction 
//		0.25f, 0.0f, 0.0f, 10.0f); //const lin exp edg
//	//spotLights[3].Load();
//	//spotLights[3].SetActive(false);
//
//
//}
//
//void Escenario2::CrearMallas() {
//	//cuboPiso = FsModel(PathGame + "/Models/PlanoPiso.fbx",
//	//	PathGame + "/Textures/Piso/");
//	//cuboPiso.LoadAuxTexure(PathGame + "/Textures/Piso/PisoArena.png");
//	//cuboPiso.LoadModel();
//	//cuboPiso.SetPosition(FsVector3(0.0f, 0.0f, 0));
//	//cuboPiso.SetRotation(FsVector3(-90.f, 0, 0));
//	//cuboPiso.SetScale(FsVector3(1.0f, 1.0f, 1));
//
//	//baseNave = FsModel(PathGame + "Models/nave/basenave.obj", pathEngine);
//	//baseNave.LoadAuxTexure(PathGame + "Models/nave/nave.jpg");
//	//baseNave.LoadModel();
//	//baseNave.SetTransform(FsTransform({ 0,0.1f,0 }, { 0,0,0 }, { 0.25f,0.25f,0.25f }));
//
//	//nave = FsModel(PathGame + "Models/nave/nave.obj", PathGame + "Models/nave/");
//	//nave.LoadAuxTexure(PathGame + "Models/nave/nave.jpg");
//	//nave.LoadModel();
//	//nave.SetTransform(FsTransform({ 0,0.1f,0 }, { 0,0,0 }, { 0.25f,0.25f,0.25f }));
//
//	//tierra = FsModel(PathGame+"Models/fSphere.obj", PathGame);
//	//tierra.LoadAuxTexure(PathGame+"Textures/Tierra/Tierra.png");
//	//tierra.LoadModel();
//	//tierra.SetTransform(FsTransform({ 0,-30,0 }, { 0,0,0 }, { 15,15,15 }));
//}
//
//void Escenario2::Mover(FsPointLight* luz) {
//
//	if (gamereference->GetKeys()[73]) { //i
//		std::cout << "Posicion: " << luz->GetPosition()->x << ", " <<
//			luz->GetPosition()->y << ", " << luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x, luz->GetPosition()->y + 0.5f, luz->GetPosition()->z));
//		gamereference->GetKeys()[73] = false;
//
//	}
//	if (gamereference->GetKeys()[74]) { //j
//		std::cout << "Posicion: " << luz->GetPosition()->x << ", " <<
//			luz->GetPosition()->y << ", " << luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x - 0.5f, luz->GetPosition()->y, luz->GetPosition()->z));
//		gamereference->GetKeys()[74] = false;
//	}
//	if (gamereference->GetKeys()[75]) { //k
//		std::cout << "Posicion: " << luz->GetPosition()->x << ", " <<
//			luz->GetPosition()->y << ", " << luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x, luz->GetPosition()->y - 0.5f, luz->GetPosition()->z));
//		gamereference->GetKeys()[75] = false;
//
//	}
//	if (gamereference->GetKeys()[76]) { //l
//		std::cout << "Posicion: " << luz->GetPosition()->x << ", " <<
//			luz->GetPosition()->y << ", " << luz->GetPosition()->z << std::endl;
//		luz->SetPosition(FsVector3(
//			luz->GetPosition()->x + 0.5f, luz->GetPosition()->y - 0.5f, luz->GetPosition()->z));
//		gamereference->GetKeys()[76] = false;
//	}
//
//
//}
//
//void Escenario2::Mover(FsModel* model) {
//
//	if (gamereference->GetKeys()[73]) { //i
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//			model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//		model->SetPosition(FsVector3(
//			model->GetTransform()->position.x, model->GetTransform()->position.y + 0.5f, model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//
//	}
//	if (gamereference->GetKeys()[74]) { //j
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//			model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//		model->SetPosition(FsVector3(
//			model->GetTransform()->position.x - 0.5f, model->GetTransform()->position.y, model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//	}
//	if (gamereference->GetKeys()[75]) { //k
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//			model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//		model->SetPosition(FsVector3(
//			model->GetTransform()->position.x, model->GetTransform()->position.y - 0.5f, model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//
//	}
//	if (gamereference->GetKeys()[76]) { //l
//		std::cout << "Posicion: " << model->GetTransform()->position.x << ", " <<
//			model->GetTransform()->position.y << ", " << model->GetTransform()->position.z << std::endl;
//
//		model->SetPosition(
//			FsVector3(
//				model->GetTransform()->position.x + 0.5f, model->GetTransform()->position.y,
//				model->GetTransform()->position.z));
//		gamereference->GetKeys()[73] = false;
//	}
//
//
//}
//
//void Escenario2::Begin()
//{
//	CrearMallas();
//	CrearLuces();
//
//	std::vector<std::string> skyboxFaces;
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyRt.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyLf.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/g.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyDn.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyBk.png");
//	skyboxFaces.push_back(PathGame + "/Textures/Skybox/GalaxyFt.png");
//	skybox = FsSkybox(skyboxFaces);
//	skybox.Load();
//
//}
//
//void Escenario2::ControlesJugador(float dt, float time) {
//	//Teclado
//	float velocidad = 0.6f;
//	if (gamereference->GetKeys()[32]) {//space
//		velocidad = 5;
//	}
//	//codigo ASCII
//	if (gamereference->GetKeys()[87]) { // tecla W
//		FsVector3 posicion =
//			gamereference->GetCamera()->GetCameraPosition() +=
//			gamereference->GetCamera()->getForward() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[83]) { // tecla S
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getForward() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[65]) { // tecla A
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getRight() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[68]) { // tecla D
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() += gamereference->GetCamera()->getRight() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[69]) { // tecla E
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() += gamereference->GetCamera()->getUp() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//	if (gamereference->GetKeys()[81]) { // tecla Q
//		FsVector3 posicion = gamereference->GetCamera()->GetCameraPosition() -= gamereference->GetCamera()->getUp() * dt * velocidad;
//		gamereference->GetCamera()->SetPosition(posicion);
//	}
//
//
//	//Primera persona
//	MouseControl(gamereference->GetMouseX(), gamereference->GetMouseY(), gamereference->GetCamera());
//
//	//Switch Linterna
//	if (gamereference->GetKeys()[70]) { //F 
//		spotLights[0].SetActive(swLinterna);
//		swLinterna = !swLinterna;
//		gamereference->GetKeys()[70] = false;
//	}
//
//	//switch linternas costados
//	if (gamereference->GetKeys()[49]) { //1
//		spotLights[1].SetActive(swLinternasCostados);
//		spotLights[2].SetActive(swLinternasCostados);
//		swLinternasCostados = !swLinternasCostados;
//		gamereference->GetKeys()[49] = false;
//	}
//	//switch puntuales base
//	if (gamereference->GetKeys()[50]) {//2
//		pointLights[0].SetActive(swPuntualesBase);
//		pointLights[1].SetActive(swPuntualesBase);
//		swPuntualesBase = !swPuntualesBase;
//		gamereference->GetKeys()[50] = false;
//	}
//	//switch Puntual media base
//	if (gamereference->GetKeys()[51]) {//3
//		pointLights[2].SetActive(swPuntualMediaBase);
//		swPuntualMediaBase = !swPuntualMediaBase;
//		gamereference->GetKeys()[51] = false;
//	}
//
//	//switch linterna nave
//	if (gamereference->GetKeys()[52]) {//4
//		spotLights[3].SetActive(swLinternaNave);
//		swLinternaNave = !swLinternaNave;
//		gamereference->GetKeys()[52] = false;
//	}
//
//	//nave despegar.....................
//	if (gamereference->GetKeys()[53]) {//5
//		swDespegue = true;
//	}
//
//	if (swDespegue) {
//		pointLights[2].SetActive(false);
//		cont += 0.01f;
//		if (velocidadNave < 0.02f) velocidadNave = abs(pow(cont, 2)) * dt * 0.001f;
//
//		nave.SetPosition(
//			FsVector3(
//				nave.GetTransform()->position.x,
//				nave.GetTransform()->position.y /*+= dt / 7*/ += velocidadNave,
//				nave.GetTransform()->position.z));
//
//		pointLights[3].SetPosition(FsVector3(nave.GetTransform()->position.x,
//			nave.GetTransform()->position.y - 2.0f,
//			nave.GetTransform()->position.z));
//
//		pointLights[3].SetColour(FsVector3(1, 1, 0));
//		pointLights[4].SetActive(true);
//		pointLights[4].SetPosition(
//			FsVector3(0, pointLights[4].GetPosition()->y += velocidadNave, 0));
//		//pointLights[4].SetAttenuation(-abs(sin(time * 5)/2.5f), 0.0f, 0.0f);
//
//		spotLights[3].SetPosition(nave.GetTransform()->position);
//	}
//
//
//
//	//Editor.........................
//	//Posicion camara!
//	if (gamereference->GetKeys()[80]) {
//		std::cout << "Posicion: " <<
//			gamereference->GetCamera()->GetCameraPosition().x << ", " <<
//			gamereference->GetCamera()->GetCameraPosition().y << ", " <<
//			gamereference->GetCamera()->GetCameraPosition().z << std::endl;
//		std::cout << "Direccion: " <<
//			gamereference->GetCamera()->GetRoll() << ", " <<
//			gamereference->GetCamera()->GetYaw() << ", " <<
//			gamereference->GetCamera()->GetPitch() << std::endl;
//		gamereference->GetKeys()[80] = false;
//	}
//}
//
//void Escenario2::Update(float deltaTime, float time) {
//	//Ajuste linterna
//	FsVector3 umbral = gamereference->GetCamera()->GetCameraPosition();
//	umbral.y -= 0.3f;
//	spotLights[0].SetPosition(umbral);
//	spotLights[0].SetDirection(gamereference->GetCamera()->GetCameraDirection());
//
//	ControlesJugador(deltaTime, time);
//	//Mover(&nave);
//	Mover(&pointLights[4]);
//	//pointLights[0].SetAttenuation(sin(time * 5) + 0.6f, 0.2f, 0.1f);
//	//pointLights[1].SetAttenuation(sin(time * 5 + 3) + 0.6f, 0.2f, 0.1f);
//	//pointLights[2].SetPosition(FsVector3(-2, 4 * sin(8 * time) + 9, 0));
//
//
//	//esferaPoint0.RenderModel();
//	//esferaSpot1.RenderModel(),
//		//cuboPiso.RenderModel();
//	//baseNave.RenderModel();
//		nave.Render();
//		tierra.Render();
//}
//
//Escenario2::~Escenario2() {}

//---------------------------------------ESCENARIO3---------------------------------------------------

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

Escenario3::Escenario3()
{
}

Escenario3::~Escenario3()
{
}

void Escenario3::ControlesJugador(float dt, float time) {
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

void Escenario3::Begin() {

	//BT.........INCIALIZAR
	//Inicializar fisicas
	btBroadphaseInterface* broadphase = new btDbvtBroadphase(); // fase ancha 
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration(); // para configurar la memoria
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration); // colision entre objetos con gran probabilidad de colisionar a traves de su forma real
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver(); // para restricciones de movimiento

	// se pasa todos los objetos requeridos para el dynamicsWorld
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0)); // se crea parametros para la fisica, en este caso la gravedad


	//Rigid Body Esfera
	btCollisionShape* sphereCollider = new btSphereShape(1.0f); // radio 1
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(
		btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 25, 0)));
	btScalar mass = 1.0;
	btVector3 sphereInertia(0, 0, 0);
	sphereCollider->calculateLocalInertia(mass, sphereInertia);

	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereCollider, sphereInertia);

	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);

	sphereRigidBody->setRestitution(1.0f);
	sphereRigidBody->setFriction(1.0f);

	dynamicsWorld->addRigidBody(sphereRigidBody);

	//piso
	btCollisionShape* groundShape = new btBoxShape(btVector3(24, 1.0f, 24)); // largo, altura y profundidad
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(
		btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0.0f, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, new btDefaultMotionState(), groundShape,
		btVector3(0, 0, 0));

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setFriction(1.0f);
	groundRigidBody->setRestitution(0.9f);
	groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	dynamicsWorld->addRigidBody(groundRigidBody);

	// enlace con el motor

	//cuboPiso = FsModel(PathGame + "/Models/PlanoPiso.fbx",
	//	PathGame + "/Textures/Piso/", nullptr);
	
	//cuboPiso.LoadAuxTexure(PathGame + "/Textures/Piso/PisoArena.png");
	//cuboPiso.Load();
	//cuboPiso.SetPosition(FsVector3(0.0f, 0.0f, 0));
	//cuboPiso.SetRotation(FsVector3(-90.f, 0, 0));
	//cuboPiso.SetScale(FsVector3(1.0f, 1.0f, 1));
	//
	////groundRigidBody->setUserPointer(&cuboPiso);

	//sphere = FsModel(PathGame + "/Models/fSphere.obj",
	//	PathGame + "/Textures/Piso/", sphereRigidBody);

	//sphere.Load();
	//sphere.SetPosition(FsVector3(0,10,0));

	//sphereRigidBody->setUserPointer(&sphere);


	// efera2
	//Rigid Body Esfera
	btCollisionShape* sphereCollider2 = new btSphereShape(1.0f); // radio 1
	btDefaultMotionState* sphere2MotionState = new btDefaultMotionState(
		btTransform(btQuaternion(0, 0, 0, 1), btVector3(25, 25, 0)));
	btScalar mass2 = 3.0;
	btVector3 sphere2Inertia(0, 0, 0);
	sphereCollider2->calculateLocalInertia(mass2, sphere2Inertia);

	btRigidBody::btRigidBodyConstructionInfo sphere2RigidBodyCI(mass2, sphere2MotionState, sphereCollider2, sphere2Inertia);

	btRigidBody* sphere2RigidBody = new btRigidBody(sphere2RigidBodyCI);

	sphere2RigidBody->setRestitution(1.0f);
	sphere2RigidBody->setFriction(1.0f);

	dynamicsWorld->addRigidBody(sphere2RigidBody);

	//sphere2 = FsModel(PathGame + "/Models/fSphere.obj",
	//	PathGame + "/Textures/Piso/", nullptr);
	//sphere2.Load();
	//sphere2.SetPosition(FsVector3(10, 10, 0));

	//sphere2RigidBody->setUserPointer(&sphere2);
	//cubo2= FsModel(PathGame + "/Models/fCubo.obj",
	//	PathGame + "/Textures/Piso/", cubeRigidBody);




	
}


void Escenario3::Update(float deltaTime, float time) {
	ControlesJugador(deltaTime, time);

	dynamicsWorld->stepSimulation(deltaTime);
	//cuboPiso.Render();
	//sphere.Render();
	//sphere2.Render();
	//std::cout << cubo1.GetTransform()->position.y << std::endl;
}




