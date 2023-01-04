#include<vector>
#include"UserGame.h"
#include"Escenario.h"

UserGame juego;

std::vector<FsScene*> escenas;
//std::vector<Plataformas> vec;
//Plataformas plat;
int main() {

	escenas.push_back(new Inicio());
	escenas.push_back(new Plataformas());

	//vec.push_back(plat);

	if (juego.Construct(1080, 720, "Space Plataform", false))
		juego.Run(escenas);

	for (auto i = 0; i < escenas.size(); i++)
		delete escenas[i];
	
}


