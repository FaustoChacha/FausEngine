#include<vector>
#include"UserGame.h"
#include"Escenario.h"

UserGame juego;

std::vector<FsObject*> escePlataformas;

int main() {

	escePlataformas.push_back(new Plataformas);
	if (juego.Construct(1920, 1080, "Space Plataform", true))
		juego.Run(escePlataformas);

}


