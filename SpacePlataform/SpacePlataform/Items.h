#ifndef ITEMS
#define ITEMS

#include"FausEngine/FsMesh.h"
#include"FausEngine/FsMaterial.h"
#include"FausEngine/FsCollider.h"

#include"Player.h"

using namespace FausEngine;

class Items
{
public:
	Items();
	void Init();
	void Tick(float, float, Player&, bool);
	~Items();

private:
	FsMesh mesh;
	FsMaterial material;
	FsCollider collider;
};




#endif // !ITEMS
