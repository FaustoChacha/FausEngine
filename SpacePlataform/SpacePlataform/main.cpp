//#define _CRTDBG_MAP_ALLOC
#include<vector>
#include"SpacePlataform.h"
#include"Scenes.h"

SpacePlataform game;

std::vector<FsScene*> scenes;

int main() {

	std::unique_ptr<FsScene> test(new Mistery());

	//scenes.push_back(new Intro());
	//scenes.push_back(new Intro());
	//scenes.push_back(new Level1());
	scenes.push_back(test.get());

	if (game.Construct(1080, 720, "Space Plataform", false)) {
		game.Run(scenes);
	}
	
	//scenes.clear();
}


