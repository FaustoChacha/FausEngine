#include"UserGame.h"

UserGame::UserGame()
{
	camara.SetPosition(FsVector3(0.0f, 0.0f, -12.0f));

	//SetCamera(camara);
	//PAUSA = true;
}

void UserGame::SetPausa(bool p) {
	prueba = p;
}

bool UserGame::GetPausa() {
	return prueba;
}
UserGame::~UserGame()
{

}