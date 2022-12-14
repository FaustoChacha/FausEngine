#include"Escenario.h"

Inicio::Inicio()
{
	teclas = gameReference->GetKeys();
	gameReference.reset(new UserGame());
}

void Inicio::Begin() {
	imgenMenu.LoadImage("Textures/menu.png");
	imgenMenu.SetScale({ 2,-2,2 });

	imgMenuPress.LoadImage("Textures/PressSpace.png");
	imgMenuPress.SetPosition({ 0,-0.65f,0 });
	imgMenuPress.SetScale({ 1,0.25f,1 });
}

void Inicio::Update(float deltatime, float time) {
	if ((int)time % 2 == 0) {
		imgMenuPress.Render();
	}
	imgenMenu.Render();

	if (teclas[32]) { //space
		gameReference->SetScene(1);
	}

}

Inicio::~Inicio()
{
}



//---------------------------------------ESCENARIO4---------------------------------------------------

Plataformas::Plataformas()
{
	teclas = gameReference->GetKeys();
	gameReference.reset(new UserGame());
	//gameReference = new UserGame;
}

Plataformas::~Plataformas()
{

}


void Plataformas::Begin() {
	log.Logger("Mensaje","Escenario: ");
	log2.Logger("Mensaje2", "Escenario: ");
	//==============================MALLAS======================================

	//colMax1 = FsMesh("Models/fSphere.obj");
	//colMax1.LoadMesh();
	//colMax1.material.type = TypeMaterial::Unlit;
	//colMax1.material.color = { 1,1,1 };

	//colMin1 = colMax1;
	//colMin1.material.color = { 0.5f,0.5f,0.5f };

	//item----
	item = FsMesh("Models/fSphere.obj");
	item.LoadMesh();
	item.material.type = TypeMaterial::Unlit;
	item.material.color = { 1,1,1 };
	item.transform.position = {-77, -7,0};
	collItem = FsCollider({ 0.3f,0.3f,0.3f }, {-0.3f,-0.3f,-0.3f });
	item.SetCollider(collItem);


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

	//=================== imagenes======================
	imgVidas[0].LoadImage("Textures/vida1.png");
	imgVidas[0].SetScale({ 0.15f,0.2f,1 });
	float y = -0.7f;
	imgVidas[0].SetPosition({0.3,y,0});

	imgVidas[1] = imgVidas[0];
	imgVidas[1].SetPosition({0.55, y,0});

	imgVidas[2] = imgVidas[0];
	imgVidas[2].SetPosition({ 0.8, y,0 });

	imgGanaste.LoadImage("Textures/ganaste.png");
	imgGanaste.SetScale({2,2,2});

	imgPressEscape.LoadImage("Textures/PressEscape.png");
	imgPressEscape.SetPosition({0,-0.65f,0});
	imgPressEscape.SetScale({1,0.25f,1});

	imgPause.LoadImage("Textures/Pause.png");
	imgPause.SetScale({ 0.75f,0.2f,1 });

	//LUZCES================
	luzDireccional = FsDireciontalLight(
		FsVector3(0.2f, -1, 0.2f),
		FsVector3(2, 2, 2),
		FsVector3(0.7f, 0.7f, 0.7f),
		FsVector3(0.5f, 0.5f, 0.5f));
	luzDireccional.Load();
	//luzDireccional.on = false;

	jugador.Init(colisionalguna);
}



void Plataformas::Update(float deltaTime, float time) {
	if (teclas[81]) {//Q
		gameReference->SetScene(0);
	}

	//===========================FISICA================================
	//detector colisiones---------------------------
	for each (FsCollider var in collPlataformas)
	{
		if (jugador.GetCollider().CheckCollision(var)) {
			indexCollision = var.id;
		} 
	}
	//colisiones moneadas
	for each (FsCollider var in collMonedas)
	{
		if (jugador.GetCollider().CheckCollision(var)) {
			indexCollisionMOnedas = var.id;
		}
	}

	
	
	//gravedad----------------------------
	if (!pausa) {
		if (!jugador.GetCollider().CheckCollision(collPlataformas[indexCollision])) {
			jugador.transform->position.y -= 15 * deltaTime;
		}
	}
	
	//salto---------------
	if (!pausa) {
		//if (teclas[32]) { // space
		//	//pausa = false;
		//	if (jugador.GetCollider().CheckCollision(collPlataformas[indexCollision])) {
		//		teclas[32] = false;
		//		jump = true;
		//		jumpLap = time + 0.5f;
		//		contadorTeclaEspacio++;
		//		if (contadorTeclaEspacio > 1)contadorTeclaEspacio = 0;
		//	}
		//}
		//if (jump && contadorTeclaEspacio == 1) {
		//	teclas[32] = false;
		//	jugador.transform->position.y += powerJump * deltaTime;
		//	if (time >= jumpLap) {
		//		jump = false;
		//		contadorTeclaEspacio = 0;
		//	}
		//}
		colisionalguna = jugador.GetCollider().CheckCollision(collPlataformas[indexCollision]);
	}
	


	
	//movimiento ocsilaTORIO PLATAFORMAS 4,5,6
	if (!pausa) {
		if (moveOsci) {
			movePlataform += 0.01f;
		}
		else {
			movePlataform -= 0.01f;
		}
		if (movePlataform <= -1) {
			moveOsci = true;
		}
		if (movePlataform >= 1) {
			moveOsci = false;
		}
		//item
		item.transform.scale.x += sin(time) * deltaTime;
		item.transform.scale.y += sin(time) * deltaTime;
		item.transform.scale.z += sin(time) * deltaTime;
	}
	else {
		movePlataform = 0;
	}
	
	//direccion de colision-------------------------
	float repulsion = 5.0f;
	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision])==CollisionDirection::RIGHT){
		jugador.transform->position.x += repulsion *deltaTime;
	}

	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision]) == CollisionDirection::LEFT) {
		jugador.transform->position.x -= repulsion * deltaTime;
	}

	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision]) == CollisionDirection::UP) {
		jugador.transform->position.y += 0.0f * deltaTime;
		//para plataformas en movimiento
		if (indexCollision == 4) {
			jugador.transform->position.y += movePlataform * deltaTime;
		}

		if (indexCollision == 5) {
			jugador.transform->position.y -= movePlataform * deltaTime;
		}

		if (indexCollision == 6) {
			jugador.transform->position.y += movePlataform * deltaTime;
		}
	}
	//colision platafortmas
	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision]) == CollisionDirection::DOWN) {
		jugador.transform->position.y -= repulsion * deltaTime;
	}
	//colision monedas
	if (jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::RIGHT || jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::UP || jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::DOWN || jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::LEFT) {
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


	//item
	if (jugador.transform->position.x < -70) {
		if (jugador.GetCollider().CheckCollision(collItem)) {
			powerJump = 32;
			item.on = false;
			collItem.on = false;
		}
	}
	if (powerJump == 32) {
		timePowerJump += 0.01f;
		//pointLight[0].SetDiffuse(colorPower);
		jugador.SetColorLuz(colorPower);

		if (timePowerJump > 16) {
			powerJump = 22;
		}

	}

	//colMax1.transform.position = collItem.GetMax();
	//colMin1.transform.position = collItem.GetMin();
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

	jugador.Update(pausa, deltaTime, time, jugador.GetCollider().CheckCollision(collPlataformas[indexCollision]));

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

	item.Render();

	//pantallas

	if (indexCollision == 13) {
		pausa = true;
		if ((int)time % 2 == 0) {
			imgPressEscape.Render();
		}
		imgGanaste.Render();
	}	

	texto2.Render();
	texto2.SetText(std::to_string(puntos));

	if (jugador.GetNumVidas() ==3) {
		imgVidas[0].Render();
		imgVidas[1].Render();
		imgVidas[2].Render();
	}
	if (jugador.GetNumVidas() ==2) {
		imgVidas[1].Render();
		imgVidas[2].Render();
	}
	if (jugador.GetNumVidas() ==1) {
		imgVidas[2].Render();
	}

	if (teclas[80]) {//p
		pausa = !pausa;
		teclas[80] = false;
	}

	if (pausa)imgPause.Render();

}
