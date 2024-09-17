#include"../ejemplo/Items.h"
#include<cmath>

Items::Items()
{
}

void Items::Init() {
	mesh.Load("Models/fSphere.obj");
	material.Load({ 1,1,1 });
	mesh.SetPosition({ -77, -7,0 });
	mesh.SetMaterial(material);
	collider.SetBoundMax({ 0.3f,0.3f,0.3f });
	collider.SetBoundMin({ -0.3f, -0.3f, -0.3f });
	mesh.SetCollider(collider);
}

void Items::Tick(float dt, float t, Player& player, bool pause) {

	if (!pause) {
		mesh.SetScale({ mesh.GetTransform().scale.x + sin(t) * dt,
			mesh.GetTransform().scale.y + sin(t) * dt,
			mesh.GetTransform().scale.z + sin(t) * dt
			});
	}
	if (player.GetPosition().x < -70) {
		if (player.GetCollider().CheckCollision(collider)) {
			player.ActivatePower(true);
			mesh.SetVisibility(false);
			collider.SetActive(false);
		}
	}

	mesh.Render();
}

Items::~Items()
{
}