#ifndef USERGAME
#define USERGAME

#include"../Motor/Headers/FsGame.h"
#include"../Motor/Headers/FsCamera.h"

using namespace FausEngine;

class SpacePlataform : public FsGame
{
public:
	SpacePlataform();
	~SpacePlataform();

private:
	
	FsCamera cam;

};

#endif // !USERGAME