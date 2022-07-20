#include<vector>
#include"UserGame.h"
#include"Escenario.h"

UserGame juego;

std::vector<FsObject*> escenario4;

int main() {

	escenario4.push_back(new Escenario4);

	if(juego.Construct(1080, 900, "Game"))
		juego.Run(escenario4);
	
}


