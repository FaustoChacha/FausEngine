#ifndef PLATAFORMAS
#define PLATAFORMAS

#include"../Motor/Headers/FsMesh.h"
#include"../Motor/Headers/FsMaterial.h"
#include"../Motor/Headers/FsCollider.h"

#include"../ejemplo/Player.h"

using namespace FausEngine;

class Plataforms
{
public:
	Plataforms();
	~Plataforms();
	bool& PlayertoPlataformCollision();
	bool FinishedLevel();
	void Init();
	void Tick(float dt, float t,Player&, bool& pause);

private:

	//plataformas
	FsMesh meshes[14];
	FsMaterial material1, material2, material3, material4;
	FsMesh complementMeshPlataform1;
	FsCollider colliders[14];
	int colliderId = 0;
	bool activateMovePlataforms;
	float movePlataform;
	bool collision;
	bool finishedLevel;


};




#endif // !PLATAFORMAS
