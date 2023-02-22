#include<vector>
#include"UserGame.h"
#include"Escenario.h"

UserGame juego;

std::vector<FsScene*> escenas;

int main() {

	//escenas.push_back(new Inicio());
	escenas.push_back(new Plataformas());
	//escenas.push_back(new Test);


	if (juego.Construct(1080, 720, "Space Plataform", false)) {
		juego.Run(escenas);
		//escenas[1].~shared_ptr();
	}
		

	//for (auto i = 0; i < escenas.size(); i++)
	//	delete escenas[i];
	
}


