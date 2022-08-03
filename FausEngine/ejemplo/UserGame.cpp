#include"UserGame.h"

UserGame::UserGame()
{
	//std::string ruta = "F:/Engine/FausEngine1.0/FausEngine1.0/MotorGrafico/";
	
	//SetPathEngine(ruta);
	camara = FsCamera(FsVector3(3.0f, 8.0f, 6.0f), FsVector3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f);

	camara.SetYaw(-90);
	SetCamera(camara);
}

UserGame::~UserGame()
{

}