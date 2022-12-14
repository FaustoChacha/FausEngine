#ifndef USERGAME
#define USERGAME

#include"../Motor/Headers/FsGame.h"
#include"../Motor/Headers/FsCamera.h"

using namespace FausEngine;

class UserGame : public FsGame
{
public:
	UserGame();
	~UserGame();
	bool PAUSA;
	bool prueba;

	void SetPausa(bool);
	bool GetPausa();

private:
	
	FsCamera camara;

};

#endif // !USERGAME