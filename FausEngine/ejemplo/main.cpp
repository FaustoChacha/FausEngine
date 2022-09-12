#include<vector>
#include"UserGame.h"
#include"Escenario.h"

UserGame juego;

std::vector<FsObject*> escePlataformas;

int main() {
	
	escePlataformas.push_back(new Plataformas);
	if(juego.Construct(1080, 720, "Space Plataform"))
		juego.Run(escePlataformas);
	
}


