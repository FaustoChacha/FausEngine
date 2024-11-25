#include"Plataforms.h"




Plataforms::Plataforms()
{
	colliderId = 0;
	movePlataform = 0;
	activateMovePlataforms = false;
}

Plataforms::~Plataforms()
{
}

bool& Plataforms::PlayertoPlataformCollision() {
	
	return collision;
}

bool Plataforms::FinishedLevel() {
	return finishedLevel;
}

void Plataforms::Init() {
	
	//plataforma grande---------------------------------------------------------
	meshes[0].Load("Models/plataforma1.obj");
	material1.Load({ 0.1f,0.1f,0.1f }, { 0.1f,0.1f,0.1f }, { 1,1,1 }, 2.5f, "Textures/plataforma1.png", false);

	meshes[0].SetMaterial(material1);
	meshes[0].SetTransform({ {0.0f, -8.0f, -2.5f}, {0,90,0},{0.5f,0.5f,0.5f } });
	complementMeshPlataform1 = meshes[0];
	complementMeshPlataform1.SetPosition({
		complementMeshPlataform1.GetTransform().position.x - 16,
		complementMeshPlataform1.GetTransform().position.y,
		complementMeshPlataform1.GetTransform().position.z });
	colliders[0].SetId(0);
	colliders[0].SetBoundMax({ 7.75f,4.0f,4.0f });
	colliders[0].SetBoundMin({ -24.1f, -4.0f, -4.0f });
	meshes[0].SetCollider(colliders[0]);

	meshes[7] = meshes[0];
	meshes[7].SetPosition({ -77,-15,-2.5f });
	colliders[7].SetId(7);
	colliders[7].SetBoundMax({ 7.75f,4.0f,4.0f });
	colliders[7].SetBoundMin({ -7.75f, -4.0f, -4.0f });
	meshes[7].SetCollider(colliders[7]);

	//plataforma mediana piramidal-----------------------------------------------------------
	meshes[1].Load("Models/plataforma2.obj");
	material2.Load({ 0.1f,0.1f,0.1f }, { 0.1f,0.1f,0.1f }, { 1,1,1 }, 5, "Textures/plataforma2.png", false);

	meshes[1].SetTransform({ {-29.0f, -2.5f, 0.0f}, {0,0,0},{1,1,1 } });
	meshes[1].SetMaterial(material2);
	colliders[1].SetId(1);
	colliders[1].SetBoundMax({ 1.5f,0.1f,1.0f });
	colliders[1].SetBoundMin({ -1.5f, -1.5f, -1.5f });
	meshes[1].SetCollider(colliders[1]);

	meshes[2] = meshes[1];
	meshes[2].SetPosition({ -35, -0.5f,0 });
	colliders[2] = colliders[1];
	colliders[2].SetId(2);
	meshes[2].SetCollider(colliders[2]);

	meshes[3] = meshes[1];
	meshes[3].SetPosition({ -43, -5,0 });
	colliders[3] = colliders[1];
	colliders[3].SetId(3);
	meshes[3].SetCollider(colliders[3]);

	meshes[8] = meshes[1];
	meshes[8].SetPosition({ -90, -8, 0 });
	colliders[8] = colliders[1];
	colliders[8].SetId(8);
	meshes[8].SetCollider(colliders[8]);

	meshes[9] = meshes[1];
	meshes[9].SetPosition({ -96, -4, 0 });
	colliders[9] = colliders[1];
	colliders[9].SetId(9);
	meshes[9].SetCollider(colliders[9]);

	meshes[10] = meshes[1];
	meshes[10].SetPosition({ -102, 0, 0 });
	colliders[10] = colliders[1];
	colliders[10].SetId(10);
	meshes[10].SetCollider(colliders[10]);

	meshes[11] = meshes[1];
	meshes[11].SetPosition({ -110, 0, 0 });
	colliders[11] = colliders[1];
	colliders[11].SetId(11);
	meshes[11].SetCollider(colliders[11]);

	meshes[12] = meshes[1];
	meshes[12].SetPosition({ -118, 0, 0 });
	colliders[12] = colliders[1];
	colliders[12].SetId(12);
	meshes[12].SetCollider(colliders[12]);

	//plataforma redonda pequena
	meshes[4].Load("Models/plataforma3.obj");
	material3.Load({ 0.1f,0.1f,0.1f }, { 0.1f,0.1f,0.1f }, { 0.5f,0.5f,0.5f }, 5, "Textures/plataforma3.png", true);

	meshes[4].SetTransform({ {-50.5f, -5.0f, 0.0f}, {0,0,0},{1,1,1 } });
	meshes[4].SetMaterial(material3);
	colliders[4].SetId(4);
	colliders[4].SetBoundMax({ 1.3f,0,1.0f });
	colliders[4].SetBoundMin({ -1.3f, -0.25f, -1.0f });
	meshes[4].SetCollider(colliders[4]);

	meshes[5] = meshes[4];
	meshes[5].SetPosition({ -56, -2.5f, 0 });
	colliders[5] = colliders[4];
	colliders[5].SetId(5);
	meshes[5].SetCollider(colliders[5]);

	meshes[6] = meshes[4];
	meshes[6].SetPosition({ -64, -7,0 });
	colliders[6] = colliders[4];
	colliders[6].SetId(6);
	meshes[6].SetCollider(colliders[6]);

	//plataforma final------------------
	meshes[13].Load("Models/plataforma4.obj");
	material4.Load({ 0.1f,0.1f,0.1f }, { 0.1f,0.1f,0.1f }, { 0.5f,0.5f,0.5f }, 5, "Textures/plataforma4.png", true);

	meshes[13].SetTransform({ {-128.0f, -10.0f, 0.0f}, {0,0,0},{1,1,1 } });
	meshes[13].SetMaterial(material4);
	colliders[13].SetId(13);
	colliders[13].SetBoundMax({ 2.0f,2,2.0f });
	colliders[13].SetBoundMin({ 1.3f, 0.25f, 1.0f });
	meshes[13].SetCollider(colliders[13]);

}

void Plataforms::Tick(float deltaTime, float time, Player& player, bool& pausa) {

	//Se detecta con que plataforma se esta colisionando y se avisa con indexCollision	
	for each (FsCollider var in colliders)
	{
		if (player.GetCollider().CheckCollision(var)) {
			colliderId = var.GetId();
		}
	}

	//segun la plataforma con la que colisiona (indexCollision) se aplican difenretes fuerzas 
	float repulsion = 5.0f;
	if (player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::RIGHT) {
		player.SetPosition({ player.GetPosition().x + repulsion * deltaTime,
			player.GetPosition().y,
			player.GetPosition().z
			});
	}

	if (player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::LEFT) {
		player.SetPosition({ player.GetPosition().x - repulsion * deltaTime,
			player.GetPosition().y,
			player.GetPosition().z
			});
	}

	if (player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::DOWN) {
		player.SetPosition({ player.GetPosition().x,
			player.GetPosition().y - repulsion * deltaTime,
			player.GetPosition().z
			});
	}

	if (player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::UP) {
		player.SetPosition({ player.GetPosition().x,
			player.GetPosition().y + 0.0f * deltaTime,
			player.GetPosition().z
			});

		//para plataformas en movimiento
		if (colliderId == 4) {
			player.SetPosition({ player.GetPosition().x,
				player.GetPosition().y + movePlataform * deltaTime,
				player.GetPosition().z
				});
		}

		if (colliderId == 5) {
			player.SetPosition({ player.GetPosition().x,
				player.GetPosition().y - movePlataform * deltaTime,
				player.GetPosition().z
				});
		}

		if (colliderId == 6) {
			player.SetPosition({ player.GetPosition().x,
				player.GetPosition().y + movePlataform * deltaTime,
				player.GetPosition().z
				});
		}
	}
	

	if (!pausa) {
		//movimiento ocsilaTORIO PLATAFORMAS 4,5,6
		if (activateMovePlataforms) {
			movePlataform += 0.01f;
		}
		else {
			movePlataform -= 0.01f;
		}
		if (movePlataform <= -1) {
			activateMovePlataforms = true;
		}
		if (movePlataform >= 1) {
			activateMovePlataforms = false;
		}

		//Se aplica fuerza de GRAVEDAD y se avisa si hay alguna cvolision con "collision"
		if (!player.GetCollider().CheckCollision(colliders[colliderId])) {
			player.SetPosition({ player.GetPosition().x,
				player.GetPosition().y - 15 * deltaTime,
				player.GetPosition().z
				});
			collision = false;
		}
		else
		{
			collision = true;
		}
	}
	else {
		movePlataform = 0;
	}

	//se dibuja
	meshes[0].Render();
	complementMeshPlataform1.Render();
	meshes[1].Render();
	meshes[2].Render();
	meshes[3].Render();
	meshes[4].SetPosition({ meshes[4].GetTransform().position.x,
		meshes[4].GetTransform().position.y + movePlataform * deltaTime,
		meshes[4].GetTransform().position.z });
	meshes[4].Render();
	meshes[5].SetPosition({ meshes[5].GetTransform().position.x,
		meshes[5].GetTransform().position.y - movePlataform * deltaTime,
		meshes[5].GetTransform().position.z
		});
	meshes[5].Render();
	meshes[6].SetPosition({ meshes[6].GetTransform().position.x,
		meshes[6].GetTransform().position.y + movePlataform * deltaTime,
		meshes[6].GetTransform().position.z
		});
	meshes[6].Render();
	meshes[7].Render();
	meshes[8].Render();
	meshes[9].Render();
	meshes[10].Render();
	meshes[11].Render();
	meshes[12].Render();
	meshes[13].Render();

	//finaliza el nivel
	if (colliderId==13) {
		finishedLevel = true;
	}
	else {
		finishedLevel = false;
	}
}