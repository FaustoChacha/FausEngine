#include "../ejemplo/Coins.h"

Coins::Coins()
{
	score = 0;
	colliderId = 0;
}

Coins::~Coins()
{
}

int Coins::GetScore() {
	return score;
}

void Coins::Init() {
	meshes[0].Load("Models/dona.obj");
	material.Load({ 0.9f,0.4f,0.19f });
	meshes[0].SetMaterial(material);

	meshes[0].SetTransform({ {-5, -3,0}, {0,90,0},{0.5f,0.5f,0.5f} });
	colliders[0].SetId(0);
	colliders[0].SetBoundMax({ 0.5f,0.5f,0.5f });
	colliders[0].SetBoundMin({ -0.5f, -0.5f, -0.5f });
	meshes[0].SetCollider(colliders[0]);

	meshes[1] = meshes[0];
	meshes[1].SetPosition({ -13,-3,0 });
	colliders[1] = colliders[0];
	colliders[1].SetId(1);
	meshes[1].SetCollider(colliders[1]);

	meshes[2] = meshes[0];
	meshes[2].SetPosition({ -20,-3,0 });
	colliders[2] = colliders[0];
	colliders[2].SetId(2);
	meshes[2].SetCollider(colliders[2]);

	meshes[3] = meshes[0];
	meshes[3].SetPosition({ -29,-1,0 });
	colliders[3] = colliders[0];
	colliders[3].SetId(3);
	meshes[3].SetCollider(colliders[3]);

	meshes[4] = meshes[0];
	meshes[4].SetPosition({ -35,1,0 });
	colliders[4] = colliders[0];
	colliders[4].SetId(4);
	meshes[4].SetCollider(colliders[4]);

	meshes[5] = meshes[0];
	meshes[5].SetPosition({ -43,-3,0 });
	colliders[5] = colliders[0];
	colliders[5].SetId(5);
	meshes[5].SetCollider(colliders[5]);

	meshes[6] = meshes[0];
	meshes[6].SetPosition({ -50,-3,0 });
	colliders[6] = colliders[0];
	colliders[6].SetId(6);
	meshes[6].SetCollider(colliders[6]);

	meshes[7] = meshes[0];
	meshes[7].SetPosition({ -56,-1,0 });
	colliders[7] = colliders[0];
	colliders[7].SetId(7);
	meshes[7].SetCollider(colliders[7]);

	meshes[8] = meshes[0];
	meshes[8].SetPosition({ -64,-6,0 });
	colliders[8] = colliders[0];
	colliders[8].SetId(8);
	meshes[8].SetCollider(colliders[8]);

	meshes[9] = meshes[0];
	meshes[9].SetPosition({ -77,-10,0 });
	colliders[9] = colliders[0];
	colliders[9].SetId(9);
	meshes[9].SetCollider(colliders[9]);

	meshes[10] = meshes[0];
	meshes[10].SetPosition({ -90,-6,0 });
	colliders[10] = colliders[0];
	colliders[10].SetId(10);
	meshes[10].SetCollider(colliders[10]);

	meshes[11] = meshes[0];
	meshes[11].SetPosition({ -96,-2,0 });

	colliders[11] = colliders[0];
	colliders[11].SetId(11);
	meshes[11].SetCollider(colliders[11]);

	meshes[12] = meshes[0];
	meshes[12].SetPosition({ -102,2,0 });
	colliders[12] = colliders[0];
	colliders[12].SetId(12);
	meshes[12].SetCollider(colliders[12]);

	meshes[13] = meshes[0];
	meshes[13].SetPosition({ -110,2,0 });
	colliders[13] = colliders[0];
	colliders[13].SetId(13);
	meshes[13].SetCollider(colliders[13]);

	meshes[14] = meshes[0];
	meshes[14].SetPosition({ -118,2,0 });
	colliders[14] = colliders[0];
	colliders[14].SetId(14);
	meshes[14].SetCollider(colliders[14]);
}

void Coins::Tick(float deltaTime, float time, Player& player, bool pausa) {
	
	//se averigua con que moneda se esta colisionando (a traves de indexCollisionMonedas)
	for each (FsCollider var in colliders)
	{
		if (player.GetCollider().CheckCollision(var)) {
			colliderId = var.GetId();
		}
	}
	
	//si colisiona con la moneda en cuestion por cualquier lado se suma puntos 
	if (player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::RIGHT ||
		player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::UP ||
		player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::DOWN ||
		player.GetCollider().GetDirection(colliders[colliderId]) == CollisionDirection::LEFT) {

		if (meshes[colliderId].GetVisibility()) {
			score += 10;
		}
		meshes[colliderId].SetVisibility(false);
	
	}

	//animacion monedas y renderizado
	for (int i = 0; i < 15; i++) {
		meshes[i].SetRotation({ meshes[i].GetTransform().rotation.x,
			meshes[i].GetTransform().rotation.y + 0.2f,
			meshes[i].GetTransform().rotation.z });
		meshes[i].Render();
	}

}