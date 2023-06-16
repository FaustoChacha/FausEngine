#ifndef COINS
#define COINS

#include"../Motor/Headers/FsMesh.h"
#include"../Motor/Headers/FsCollider.h"

#include"../ejemplo/Player.h"

using namespace FausEngine;


class Coins
{
public:
	Coins();
	~Coins();
	void Init();
	void Tick(float, float, Player&, bool);
	int GetScore();

private:
	FsMesh meshes[15];
	FsCollider colliders[15];
	FsMaterial material;
	int score;
	int colliderId;
};



#endif // !COINS
