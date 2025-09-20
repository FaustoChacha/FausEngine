#ifndef ITEMS
#define ITEMS

#include"../Motor/Headers/FsMesh.h"
#include"../Motor/Headers/FsMaterial.h"
#include"../Motor/Headers/FsCollider.h"

#include"../ejemplo/Player.h"

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
