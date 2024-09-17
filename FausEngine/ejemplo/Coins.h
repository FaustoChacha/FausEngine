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
	void Tick(float deltaTime, float time, Player&, bool pause);
	int GetScore();

private:
	std::vector<FsMesh> meshes{ 15 };
	std::vector<FsCollider> colliders{ 15 };
	FsMaterial material;
	int score;
	int colliderId;
};



#endif // !COINS
