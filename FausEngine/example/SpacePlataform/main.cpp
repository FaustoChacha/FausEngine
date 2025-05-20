#include<vector>
#include"SpacePlataform.h"
#include"Scenes.h"

SpacePlataform game;

std::vector<FsScene*> scenes;
std::vector<std::shared_ptr<FsScene>> ptrScenes;

int main() {

	//scenes.push_back(new Intro());
	scenes.push_back(new Level1());
	auto l1 = std::make_shared<Level1>();
	ptrScenes.push_back(l1);


	//escenas.push_back(new Test);


	if (game.Construct(1080, 720, "Space Plataform", false)) {
		game.Run(scenes);
		//escenas[1].~shared_ptr();
	}
		

	//for (auto i = 0; i < escenas.size(); i++)
	//	delete escenas[i];
	
}


