#include"Escenario.h"

Inicio::Inicio()
{
	//teclas = gameReference->GetKeys();
	gameReference.reset(new UserGame());
}

void Inicio::Begin() {
	imgenMenu.Load("Textures/menu.png");
	imgenMenu.SetScale({ 2,-2,2 });

	imgMenuPress.Load("Textures/PressSpace.png");
	imgMenuPress.SetPosition({ 0,-0.65f,0 });
	imgMenuPress.SetScale({ 1,0.25f,1 });
}

void Inicio::Update(float deltatime, float time) {
	if ((int)time % 2 == 0) {
		imgMenuPress.Render();
	}
	imgenMenu.Render();

	if (gameReference->GetKeyPress(Keys::SPACE)) { //space
		gameReference->SetScene(1);
	}

}

Inicio::~Inicio()
{
}



//---------------------------------------PLATAFORMAS---------------------------------------------------

Plataformas::Plataformas()
{
	//teclas = gameReference->GetKeys();
	gameReference.reset(new UserGame());
	//gameReference = new UserGame;
}

Plataformas::~Plataformas()
{

}

void Plataformas::Begin() {
	
	//==============================MALLAS======================================

	//item----
	item.Load("Models/fSphere.obj");
	//item.Load();
	matItem.Load({1,1,1});
	//item.material.type = TypeMaterial::Unlit;
	//item.material.color = { 1,1,1 };
	item.SetPosition({ -77, -7,0 });
	item.SetMaterial(matItem);
	collItem.SetBoundMax({ 0.3f,0.3f,0.3f }); 
	collItem.SetBoundMin({-0.3f, -0.3f, -0.3f });
	item.SetCollider(collItem);


	//=======PLATAFORMAS======
	
	if (true) {
	
	//plataforma grande---------------------------------------------------------
	plataformas[0].Load("Models/plataforma1.obj");
	//plataformas[0].Load();
	matPla1.Load({0.1f,0.1f,0.1f}, {0.1f,0.1f,0.1f}, {1,1,1}, 2.5f,"Textures/plataforma1.png" ,false);
	plataformas[0].SetMaterial(matPla1);
	plataformas[0].SetTransform({ {0.0f, -8.0f, -2.5f}, {0,90,0},{0.5f,0.5f,0.5f } });
	complemento0 = plataformas[0];
	complemento0.SetPosition({ 
		complemento0.GetTransform().position.x - 16, 
		complemento0.GetTransform().position.y, 
		complemento0.GetTransform().position.z });
	//Collider 
	collPlataformas[0].Load(0);
	collPlataformas[0].SetBoundMax({ 7.75f,4.0f,4.0f }); 
	collPlataformas[0].SetBoundMin({ -24.1f, -4.0f, -4.0f });
	//collPlataformas[0].id = 0;
	plataformas[0].SetCollider(collPlataformas[0]);

	plataformas[7] = plataformas[0];
	plataformas[7].SetPosition( {-77,-15,-2.5f});
	collPlataformas[7].Load(7);
	collPlataformas[7].SetBoundMax({ 7.75f,4.0f,4.0f }); 
	collPlataformas[7].SetBoundMin({ -7.75f, -4.0f, -4.0f });
	plataformas[7].SetCollider(collPlataformas[7]);

	//plataforma mediana piramidal-----------------------------------------------------------
	plataformas[1].Load("Models/plataforma2.obj");
	matPla2.Load({0.1f,0.1f,0.1f}, {0.1f,0.1f,0.1f}, {1,1,1}, 5, "Textures/plataforma2.png", false);
	//plataformas[1].Load();
	//plataformas[1].material.LoadTexture("Textures/plataforma2.png");
	plataformas[1].SetTransform({ {-29.0f, -2.5f, 0.0f}, {0,0,0},{1,1,1 } });
	//plataformas[1].material.ambient = { 0.1f, 0.1f, 0.1f };
	//plataformas[1].material.specular = { 0.1f, 0.1f, 0.1f };
	//plataformas[1].material.shineness = 5;
	plataformas[1].SetMaterial(matPla2);
	//Collider 
	collPlataformas[1].Load(1);
	collPlataformas[1].SetBoundMax({ 1.5f,0.1f,1.0f }); 
	collPlataformas[1].SetBoundMin({ -1.5f, -1.5f, -1.5f});
	plataformas[1].SetCollider(collPlataformas[1]);
	//Referencia
	refRight.Load("Models/fSphere.obj");
	//refRight.Load();
	
	//refRight.material.type= TypeMaterial::Unlit;
	//refRight.material.color = {0,0,1};

	refLeft.Load("Models/fSphere.obj");
	//refLeft.Load();
	//refLeft.material.type = TypeMaterial::Unlit;
	//refLeft.material.color = { 0,1,0 };

	plataformas[2] = plataformas[1];
	plataformas[2].SetPosition({-35, -0.5f,0});
	collPlataformas[2] = collPlataformas[1];
	collPlataformas[2].Load(2);
	plataformas[2].SetCollider(collPlataformas[2]);

	plataformas[3] = plataformas[1];
	plataformas[3].SetPosition({ -43, -5,0 });
	collPlataformas[3] = collPlataformas[1];
	collPlataformas[3].Load(3);
	plataformas[3].SetCollider(collPlataformas[3]);

	plataformas[8] = plataformas[1];
	plataformas[8].SetPosition({-90, -8, 0});
	
	collPlataformas[8] = collPlataformas[1];
	collPlataformas[8].Load(8);
	plataformas[8].SetCollider(collPlataformas[8]);

	plataformas[9] = plataformas[1];
	plataformas[9].SetPosition( { -96, -4, 0 });
	
	collPlataformas[9] = collPlataformas[1];
	collPlataformas[9].Load(9);
	plataformas[9].SetCollider(collPlataformas[9]);

	plataformas[10] = plataformas[1];
	plataformas[10].SetPosition({ -102, 0, 0 });
	
	collPlataformas[10] = collPlataformas[1];
	collPlataformas[10].Load(10);
	plataformas[10].SetCollider(collPlataformas[10]);

	plataformas[11] = plataformas[1];
	plataformas[11].SetPosition({ -110, 0, 0 });
	collPlataformas[11].Load(11);
	collPlataformas[11] = collPlataformas[1];
	plataformas[11].SetCollider(collPlataformas[11]);

	plataformas[12] = plataformas[1];
	plataformas[12].SetPosition( { -118, 0, 0 });
	
	collPlataformas[12] = collPlataformas[1];
	collPlataformas[12].Load(12);
	plataformas[12].SetCollider(collPlataformas[12]);

	//plataforma redonda pequena
	plataformas[4].Load("Models/plataforma3.obj");
	//plataformas[4].Load();
	matPla3.Load({ 0.1f,0.1f,0.1f }, { 0.1f,0.1f,0.1f }, { 0.5f,0.5f,0.5f }, 5, "Textures/plataforma3.png", true);
	//plataformas[4].material.LoadTexture("Textures/plataforma3.png");
	//plataformas[4].material.bind_TexToColor = true;
	//plataformas[4].material.color = {0.5f,0.5f,0.5f};
	plataformas[4].SetTransform({ {-50.5f, -5.0f, 0.0f}, {0,0,0},{1,1,1 } });
	//plataformas[4].material.ambient = { 0.1f, 0.1f, 0.1f };
	//plataformas[4].material.specular = { 0.1f, 0.1f, 0.1f };
	//plataformas[4].material.shineness = 5;
	plataformas[4].SetMaterial(matPla3);
	//Collider 
	collPlataformas[4].Load(4);
	collPlataformas[4].SetBoundMax({ 1.3f,0,1.0f }); 
	collPlataformas[4].SetBoundMin({ -1.3f, -0.25f, -1.0f });
	plataformas[4].SetCollider(collPlataformas[4]);

	plataformas[5] = plataformas[4];
	plataformas[5].SetPosition({-56, -2.5f, 0});
	
	collPlataformas[5] = collPlataformas[4];
	collPlataformas[5].Load(5);
	//collPlataformas[5].id = 5;
	plataformas[5].SetCollider(collPlataformas[5]);

	plataformas[6] = plataformas[4];
	plataformas[6].SetPosition({-64, -7,0});
	
	collPlataformas[6] = collPlataformas[4];
	collPlataformas[6].Load(6);
	//collPlataformas[6].id = 6;
	plataformas[6].SetCollider(collPlataformas[6]);

	//plataforma final------------------
	plataformas[13].Load("Models/plataforma4.obj");
	matPla4.Load({ 0.1f,0.1f,0.1f }, { 0.1f,0.1f,0.1f }, { 0.5f,0.5f,0.5f }, 5, "Textures/plataforma4.png", true);
	//plataformas[13].Load();
	//plataformas[13].material.LoadTexture("Textures/plataforma4.png");
	//plataformas[13].material.bind_TexToColor = true;
	//plataformas[13].material.color = { 0.5f,0.5f,0.5f };
	plataformas[13].SetTransform({ {-128.0f, -10.0f, 0.0f}, {0,0,0},{1,1,1 } });
	//plataformas[13].material.ambient = { 0.1f, 0.1f, 0.1f };
	//plataformas[13].material.specular = { 0.1f, 0.1f, 0.1f };
	//plataformas[13].material.shineness = 5;
	plataformas[13].SetMaterial(matPla4);
	//Collider 
	collPlataformas[13].Load(13);
	collPlataformas[13].SetBoundMax({ 2.0f,2,2.0f }); 
	collPlataformas[13].SetBoundMin({ 1.3f, 0.25f, 1.0f });
	//collPlataformas[13].id = 13;
	plataformas[13].SetCollider(collPlataformas[13]);
	}

	//-----referencia mallas coliders-------
	colMax2.Load("Models/fSphere.obj");
	//colMax2.Load();
	//colMax2.material.type = TypeMaterial::Unlit;
	//colMax2.material.color = { 1,1,1 };
	//colMin2 = colMax2;
	//colMin2.material.type = TypeMaterial::Unlit;
	//colMin2.material.color = { 1.0f,0.0f,0.0f };

	//==============Monedas=======================
	if (true) {
		monedas[0].Load("Models/dona.obj");
		//monedas[0].Load();
		matMoneda.Load({ 0.9f,0.4f,0.19f });
		//monedas[0].material.type = TypeMaterial::Unlit;
		//monedas[0].material.color = { 0.9f,0.4f,0.19f };
		monedas[0].SetTransform({ {-5, -3,0}, {0,90,0},{0.5f,0.5f,0.5f} });
		monedas->SetMaterial(matMoneda);
		collMonedas[0].Load(0);
		collMonedas[0].SetBoundMax({ 0.5f,0.5f,0.5f }); 
		collMonedas[0].SetBoundMin({ -0.5f, -0.5f, -0.5f });
		//collMonedas[0].id = 0;
		monedas[0].SetCollider(collMonedas[0]);

		monedas[1] = monedas[0];
		monedas[1].SetPosition( { -13,-3,0 });
		
		collMonedas[1] = collMonedas[0];
		//collMonedas[1].id = 1;
		collMonedas[1].Load(1);
		monedas[1].SetCollider(collMonedas[1]);

		monedas[2] = monedas[0];
		monedas[2].SetPosition( { -20,-3,0 });
		
		collMonedas[2] = collMonedas[0];
		//collMonedas[2].id = 2;
		collMonedas[2].Load(2);
		monedas[2].SetCollider(collMonedas[2]);

		monedas[3] = monedas[0];
		monedas[3].SetPosition({ -29,-1,0 });
		
		collMonedas[3] = collMonedas[0];
		//collMonedas[3].id = 3;
		collMonedas[3].Load(3);
		monedas[3].SetCollider(collMonedas[3]);

		monedas[4] = monedas[0];
		monedas[4].SetPosition({ -35,1,0 });
		
		collMonedas[4] = collMonedas[0];
		//collMonedas[4].id = 4;
		collMonedas[4].Load(4);
		monedas[4].SetCollider(collMonedas[4]);

		monedas[5] = monedas[0];
		monedas[5].SetPosition({ -43,-3,0 });
		
		collMonedas[5] = collMonedas[0];
		//collMonedas[5].id = 5;
		collMonedas[5].Load(5);
		monedas[5].SetCollider(collMonedas[5]);

		monedas[6] = monedas[0];
		monedas[6].SetPosition({ -50,-3,0 });
		
		collMonedas[6] = collMonedas[0];
		collMonedas[6].Load(6);
		//collMonedas[6].id = 6;
		monedas[6].SetCollider(collMonedas[6]);

		monedas[7] = monedas[0];
		monedas[7].SetPosition({ -56,-1,0 });
		
		collMonedas[7] = collMonedas[0];
		//collMonedas[7].id = 7;
		collMonedas[7].Load(7);
		monedas[7].SetCollider(collMonedas[7]);

		monedas[8] = monedas[0];
		monedas[8].SetPosition({ -64,-6,0 });
		
		collMonedas[8] = collMonedas[0];
		//collMonedas[8].id = 8;
		collMonedas[8].Load(8);
		monedas[8].SetCollider(collMonedas[8]);

		monedas[9] = monedas[0];
		monedas[9].SetPosition( { -77,-10,0 });
		
		collMonedas[9] = collMonedas[0];
		//collMonedas[9].id = 9;
		collMonedas[9].Load(9);
		monedas[9].SetCollider(collMonedas[9]);

		monedas[10] = monedas[0];
		monedas[10].SetPosition({ -90,-6,0 });
		
		collMonedas[10] = collMonedas[0];
		//collMonedas[10].id = 10;
		collMonedas[10].Load(10);
		monedas[10].SetCollider(collMonedas[10]);

		monedas[11] = monedas[0];
		monedas[11].SetPosition({ -96,-2,0 });
		
		collMonedas[11] = collMonedas[0];
		//collMonedas[11].id = 11;
		collMonedas[11].Load(11);
		monedas[11].SetCollider(collMonedas[11]);

		monedas[12] = monedas[0];
		monedas[12].SetPosition({ -102,2,0 });
		
		collMonedas[12] = collMonedas[0];
		//collMonedas[12].id = 12;
		collMonedas[12].Load(12);
		monedas[12].SetCollider(collMonedas[12]);

		monedas[13] = monedas[0];
		monedas[13].SetPosition({ -110,2,0 });
		
		collMonedas[13] = collMonedas[0];
		//collMonedas[13].id = 13;
		collMonedas[13].Load(13);
		monedas[13].SetCollider(collMonedas[13]);

		monedas[14] = monedas[0];
		monedas[14].SetPosition({ -118,2,0 });
		
		collMonedas[14] = collMonedas[0];
		//collMonedas[14].id = 14;
		collMonedas[14].Load(14);
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

	sky.Load(caras);
	//sky.Load();

	//===================== TEXTO =====================

	//texto1= FsText("Fonts/SpaceMission-rgyw9.otf", 50, "P r e s s  S p a c e", FsVector2(150, 500), FsVector3(1, 0, 1));
	//texto3 = FsText("Fonts/SpaceMission-rgyw9.otf", 50, "A - D  t o  m o v e", FsVector2(150, 400), FsVector3(1, 0, 1));
	texto2.Load("Fonts/waltographUI.ttf", 50, std::to_string(puntos), FsVector3(20, 520,0), FsVector3(1, 1, 1));

	//=================== imagenes======================
	imgVidas[0].Load("Textures/vida1.png");
	imgVidas[0].SetScale({ 0.15f,0.2f,1 });
	float y = -0.7f;
	imgVidas[0].SetPosition({0.3,y,0});

	imgVidas[1] = imgVidas[0];
	imgVidas[1].SetPosition({0.55, y,0});

	imgVidas[2] = imgVidas[0];
	imgVidas[2].SetPosition({ 0.8, y,0 });

	imgGanaste.Load("Textures/ganaste.png");
	imgGanaste.SetScale({2,2,2});

	imgPressEscape.Load("Textures/PressEscape.png");
	imgPressEscape.SetPosition({0,-0.65f,0});
	imgPressEscape.SetScale({1,0.25f,1});

	imgPause.Load("Textures/Pause.png");
	imgPause.SetScale({ 0.75f,0.2f,1 });

	//LUZCES================
	luzDireccional.Load(
		FsVector3(0.2f, -1, 0.2f),
		FsVector3(0.2f, 0.2f, 0.2f),
		//FsVector3(5,5,5),
		FsVector3(0.2f, 0.2f, 0.2f),
		FsVector3(0.2f, 0.2f, 0.2f));
	//luzDireccional.on = false;
	//luzDireccional.Load();
	//luzDireccional.on = false;

	lucesPuntuales.push_back(
		std::shared_ptr<FsPointLight>(
		new FsPointLight()));

	lucesPuntuales[0]->Load(FsVector3(1, 1, 1),
		FsVector3(0, 0, 1),
		FsVector3(1, 1, 1),
		//player.transform.position,
		FsVector3(-3, 2, 0),
		2, 0.0f, 0.0f);

	luzLinterna.Load(
		FsVector3(1, 0, 1),
		FsVector3(1, 0, 1),
		FsVector3(1,0 , 1),
		FsVector3(0,2,0),
		FsVector3(0,-1,0),
		0.5f,0.0f,0.0f	);

	jugador.Init(colisionalguna);
}

void Plataformas::Update(float deltaTime, float time) {
	
	if (gameReference->GetKeyPress(Keys::L)) {
		//luzDireccional.SetAmbient(FsVector3(0,0,0));
	}
	//===========================FISICA================================
	//detector colisiones---------------------------
	for each (FsCollider var in collPlataformas)
	{
		if (jugador.GetCollider().CheckCollision(var)) {
			indexCollision = var.GetId();
		} 
	}
	//colisiones moneadas
	for each (FsCollider var in collMonedas)
	{
		if (jugador.GetCollider().CheckCollision(var)) {
			indexCollisionMOnedas = var.GetId();
		}
	}

	
	
	//gravedad----------------------------
	if (!pausa) {
		if (!jugador.GetCollider().CheckCollision(collPlataformas[indexCollision])) {
			//jugador.transform->position.y -= 15 * deltaTime;
			jugador.SetPosition({ jugador.GetPosition().x, 
				jugador.GetPosition().y - 15* deltaTime,
				jugador.GetPosition().z
				});
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
		//item.transform.scale.x += sin(time) * deltaTime;
		item.SetScale({ item.GetTransform().scale.x + sin(time) * deltaTime,
			item.GetTransform().scale.y + sin(time) * deltaTime, 
			item.GetTransform().scale.z + sin(time) * deltaTime
			});
		//item.transform.scale.y += sin(time) * deltaTime;

		//item.transform.scale.z += sin(time) * deltaTime;
	}
	else {
		movePlataform = 0;
	}
	
	//direccion de colision-------------------------
	float repulsion = 5.0f;
	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision])==CollisionDirection::RIGHT){
		//jugador.transform->position.x += repulsion *deltaTime;
		jugador.SetPosition({jugador.GetPosition().x + repulsion * deltaTime,
			jugador.GetPosition().y,
			jugador.GetPosition().z
			});
	}

	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision]) == CollisionDirection::LEFT) {
		//jugador.transform->position.x -= repulsion * deltaTime;
		jugador.SetPosition({ jugador.GetPosition().x - repulsion * deltaTime,
			jugador.GetPosition().y,
			jugador.GetPosition().z
		});
	}

	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision]) == CollisionDirection::UP) {
		//jugador.transform->position.y += 0.0f * deltaTime;
		jugador.SetPosition({ jugador.GetPosition().x,
			jugador.GetPosition().y + 0.0f * deltaTime,
			jugador.GetPosition().z
		});

		//para plataformas en movimiento
		if (indexCollision == 4) {
			//jugador.transform->position.y += movePlataform * deltaTime;
			jugador.SetPosition({ jugador.GetPosition().x,
				jugador.GetPosition().y + movePlataform * deltaTime,
				jugador.GetPosition().z
			});
		}

		if (indexCollision == 5) {
			//jugador.transform->position.y -= movePlataform * deltaTime;
			jugador.SetPosition({ jugador.GetPosition().x,
				jugador.GetPosition().y - movePlataform * deltaTime,
				jugador.GetPosition().z
			});
		}

		if (indexCollision == 6) {
			//jugador.transform->position.y += movePlataform * deltaTime;
			jugador.SetPosition({ jugador.GetPosition().x,
				jugador.GetPosition().y + movePlataform * deltaTime,
				jugador.GetPosition().z
			});
		}
	}
	//colision platafortmas
	if (jugador.GetCollider().GetDirection(collPlataformas[indexCollision]) == CollisionDirection::DOWN) {
		//jugador.transform->position.y -= repulsion * deltaTime;
		jugador.SetPosition({jugador.GetPosition().x,
			jugador.GetPosition().y - repulsion * deltaTime,
			jugador.GetPosition().z
		});
	}
	//colision monedas
	if (jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::RIGHT || jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::UP || jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::DOWN || jugador.GetCollider().GetDirection(collMonedas[indexCollisionMOnedas]) == CollisionDirection::LEFT) {
		if (indexCollisionMOnedas == 0) {
			if (monedas[0].GetVisibility()) {
				puntos+=10;
			}
			monedas[0].SetVisibility(false);
		} 
		if (indexCollisionMOnedas == 1) {
			if (monedas[1].GetVisibility()) {
				puntos+=10;
			}
			monedas[1].SetVisibility(false);
		} 
		if (indexCollisionMOnedas == 2) {
			if (monedas[2].GetVisibility()) {
				puntos+=10;
			}
			monedas[2].SetVisibility(false);
		} 
		if (indexCollisionMOnedas == 3) {
			if (monedas[3].GetVisibility()) {
				puntos += 10;
			}
			monedas[3].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 4) {
			if (monedas[4].GetVisibility()) {
				puntos += 10;
			}
			monedas[4].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 5) {
			if (monedas[5].GetVisibility()) {
				puntos += 10;
			}
			monedas[5].SetVisibility(false);
		}

		if (indexCollisionMOnedas == 6) {
			if (monedas[6].GetVisibility()) {
				puntos += 10;
			}
			monedas[6].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 7) {
			if (monedas[7].GetVisibility()) {
				puntos += 10;
			}
			monedas[7].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 8) {
			if (monedas[8].GetVisibility()) {
				puntos += 10;
			}
			monedas[8].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 9) {
			if (monedas[9].GetVisibility()) {
				puntos += 10;
			}
			monedas[9].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 10) {
			if (monedas[10].GetVisibility()) {
				puntos += 10;
			}
			monedas[10].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 11) {
			if (monedas[11].GetVisibility()) {
				puntos += 10;
			}
			monedas[11].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 12) {
			if (monedas[12].GetVisibility()) {
				puntos += 10;
			}
			monedas[12].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 13) {
			if (monedas[13].GetVisibility()) {
				puntos += 10;
			}
			monedas[13].SetVisibility(false);
		}
		if (indexCollisionMOnedas == 14) {
			if (monedas[14].GetVisibility()) {
				puntos += 10;
			}
			monedas[14].SetVisibility(false);
		}


	}


	//item
	if (jugador.GetPosition().x < -70) {
		if (jugador.GetCollider().CheckCollision(collItem)) {
			powerJump = 32;
			item.SetVisibility(false);
			//collItem.active = false;
			collItem.SetActive(false);
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
	//plataformas[4].transform.position.y += movePlataform * deltaTime;
	plataformas[4].SetPosition({ plataformas[4].GetTransform().position.x, 
		plataformas[4].GetTransform().position.y + movePlataform * deltaTime,
		plataformas[4].GetTransform().position.z });
	plataformas[4].Render();
	//plataformas[5].transform.position.y -= movePlataform * deltaTime;
	plataformas[5].SetPosition({ plataformas[5].GetTransform().position.x,
		plataformas[5].GetTransform().position.y - movePlataform * deltaTime,
		plataformas[5].GetTransform().position.z
		});
	plataformas[5].Render();
	//plataformas[6].transform.position.y += movePlataform * deltaTime;
	plataformas[6].SetPosition({ plataformas[6].GetTransform().position.x,
		plataformas[6].GetTransform().position.y + movePlataform * deltaTime,
		plataformas[6].GetTransform().position.z
		});
	plataformas[6].Render();
	plataformas[7].Render();
	plataformas[8].Render();
	plataformas[9].Render();
	plataformas[10].Render();
	plataformas[11].Render();
	plataformas[12].Render();
	plataformas[13].Render();


	for (int i = 0; i < 15; i++) {
		monedas[i].SetRotation({ monedas[i].GetTransform().rotation.x,
			monedas[i].GetTransform().rotation.y + 0.2f,
			monedas[i].GetTransform().rotation.z });
		monedas[i].Render();
	}

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

	if (gameReference->GetKeyPress(Keys::P)) {//p
		pausa = !pausa;
		gameReference->SetKeyRelease(Keys::P);
	}

	if (pausa)imgPause.Render();

}

//=============================== Test ================================

Test::Test() {
	gameReference.reset(new UserGame());
}

void Test::Begin() {


	//=================SKYBOX======================


	//LUZCES================
	luzDireccional.Load(
		FsVector3(-0.9f, -1, 0.2f),
		FsVector3(5, 5, 5),
		FsVector3(0.9f, 0.9f, 0.9f),
		FsVector3(0.5f, 0.5f, 0.5f));
	//luzDireccional.Load();

	std::vector<std::string> caras = {
	"Textures/Sk_GalaxyRt.png",
	"Textures/Sk_GalaxyLf.png",
	"Textures/Sk_GalaxyUp.png",
	"Textures/Sk_GalaxyDn.png",
	"Textures/Sk_GalaxyBk.png",
	"Textures/Sk_GalaxyFt.png"
	};
	sky.Load(caras);
	//sky.Load();

	//jugador.Init(colisionalguna);

	//malla = FsMesh("Models/player-ball.obj");
	//malla.LoadMesh();
	//malla.material.type = TypeMaterial::Unlit;
	//malla.material.color = { 1,1,1 };
	//malla.transform.scale = { 0.5f,0.5f,0.5f };
	//std::shared_ptr<FsMesh> malla(new FsMesh("Models/player-ball.obj"));
	
	//malla.reset(new FsMesh("Models/player-ball.obj"));
	//malla->material.LoadTexture("Textures/player-ball.png");
	//malla->Load();
	//malla->material.type = TypeMaterial::Lit;
	//malla->material.color = { 1,1,1 };
	//malla->transform.scale = { 0.5f,0.5f,0.5f };

	matMalla.Load({0,0,1});
	
	matMalla2.Load({1,1,1});
	//matMalla.Load(/*{ 0.5f,0.5f ,0.5f }*/{1,1,1}, { 0.1f, 0.1f, 0.1f }, { 1.0f, 1.0f, 1.0f }, 1, "Textures/player-ball.png", false);
	malla.Load("Models/player-ball.obj");
	//malla.material = matMalla;
	malla.SetMaterial(matMalla);
	
}

void Test::CamaraFPS(float dt, float t)
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

void Test::ControlFPS(float dt, float time) {

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

void Test::Update(float deltaTime, float time) {
	ControlFPS(deltaTime, time);
	
	//malla.transform.position = { 0,0,0 };
	malla.Render();
	
}

Test::~Test() {}