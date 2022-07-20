#ifndef USERGAME
#define USERGAME

#include"../MotorGrafico/Headers/FsGame.h"
#include"../MotorGrafico/Headers/FsCamera.h"

using namespace FausEngine;

class UserGame : public FsGame
{
public:
	UserGame();
	~UserGame();



private:
	FsCamera camara;
	std::string ruta = "../../../../MotorGrafico/";
};

#endif // !USERGAME