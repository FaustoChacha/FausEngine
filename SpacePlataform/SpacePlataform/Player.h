#ifndef JUGADOR
#define JUGADOR

#include"FausEngine/FsMesh.h"
#include"FausEngine/FsCollider.h"
#include"FausEngine/FsPointLight.h"

#include"SpacePlataform.h"

using namespace FausEngine;

class Player
{
public:
	Player();
	void Init();
	void Tick(bool, float, float, bool);
	void ControlFPS(float, float);
	void ControlTPS(float, float);
	void Control2D(float, float);
	void CameraFPS(float dt, float t);
	void CameraTPS(float dt, float t);
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

