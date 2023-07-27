//#define _CRTDBG_MAP_ALLOC
#include<vector>
#include"SpacePlataform.h"
#include"Scenes.h"

SpacePlataform game;

std::vector<FsScene*> scenes;

int main() {
	std::unique_ptr<FsScene> intro(new Intro());
	std::unique_ptr<FsScene> level1(new Level1());

	//scenes.push_back(new Intro());
	//scenes.push_back(intro.get());
	scenes.push_back(level1.get());
	//escenas1.push_back(new Test);

	if (game.Construct(1080, 720, "Space Plataform", false)) {
		game.Run(scenes);
	}
	
	scenes.clear();
}


