#include<vector>
#include"UserGame.h"
#include"Escenario.h"

UserGame juego;

std::vector<FsObject*> escenario;
std::vector<FsObject*> escenario2;

int main() {
	escenario.push_back(new Escenario1);
	escenario2.push_back(new Escenario2);

	if (juego.Construct(1080, 900, "Game"))
		juego.Run(escenario);

}


