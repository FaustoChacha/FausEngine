#ifndef USERGAME
#define USERGAME

#include"FausEngine/FsGame.h"
#include"FausEngine/FsCamera.h"

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