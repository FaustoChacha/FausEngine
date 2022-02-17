#ifndef USERGAME
#define USERGAME

#include"FausEngine/FsGame.h"
#include"FausEngine/FsCamera.h"

using namespace FausEngine;

class UserGame : public FsGame
{
public:
	UserGame();
	~UserGame();



private:
	FsCamera camara;
	std::string ruta = "../../../../UserGame/FausEngine/";
};

#endif // !USERGAME