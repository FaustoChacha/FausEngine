#ifndef JUGADOR
#define JUGADOR

#include"../Motor/Headers/FsMesh.h"
#include"../Motor/Headers/FsCollider.h"
#include"../Motor/Headers/FsPointLight.h"

#include"../ejemplo/SpacePlataform.h"

using namespace FausEngine;

class Player
{
public:
	Player();
	void Init();
	void Tick(bool pause, float deltaTime, float time, bool collision);
	void ControlFPS(float deltaTime, float time);
	void ControlTPS(float deltaTime, float time);
	void Control2D(float deltaTime, float time);
	void CameraFPS(float deltaTime, float time);
	void CameraTPS(float deltaTime, float time);
	void OrbitMeshLight(float offsetX, float offsetY, float dt, float t, float vel);
	void ActivatePower(bool);
	void SetMeshLightColor(FsVector3 color);
	void SetPosition(FsVector3);
	void SetNumberLifes(int);
	int GetNumberLifes();
	FsVector3 GetPosition();
	FsCollider GetCollider();
	~Player();

private:
	void HandleColor();

	std::unique_ptr<SpacePlataform> gameReference;
	
	FsMesh playerMesh, orbitalLightMesh;
	FsMaterial playerMaterial, lightMaterial;
	FsCollider collider;
	FsPointLight pointLight;

	FsVector3 color;
	int speedPointLight;
	int numberLifes;
	FsVector3 startPlayerPosition;
	bool colision;

	//salto---
	bool activatePower, jump;
	float timePowerJump, timeJump, intesityPowerJump;
	int countSpaceKey;
};



#endif // !JUGADOR

