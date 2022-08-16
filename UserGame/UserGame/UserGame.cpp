#include"UserGame.h"

UserGame::UserGame()
{
	camara = FsCamera(FsVector3(0.0f, 5.0f, -5.0f));

	SetCamera(camara);
}

UserGame::~UserGame()
{

}

