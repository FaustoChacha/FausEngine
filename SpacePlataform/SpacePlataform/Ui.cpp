
#include"Ui.h"

Ui::Ui()
{
}

void Ui::Init() {
	//===================== TEXTO =====================

	//texto1= FsText("Fonts/SpaceMission-rgyw9.otf", 50, "P r e s s  S p a c e", FsVector2(150, 500), FsVector3(1, 0, 1));
	//texto3 = FsText("Fonts/SpaceMission-rgyw9.otf", 50, "A - D  t o  m o v e", FsVector2(150, 400), FsVector3(1, 0, 1));
	scoretext.Load("Fonts/waltographUI.ttf", 50, std::to_string(0), FsVector3(20, 520, 0), FsVector3(1, 1, 1));

	//=================== imagenes======================
	lifeImages[0].Load("Textures/vida1.png");
	lifeImages[0].SetScale({ 0.15f,0.2f,1 });
	float y = -0.7f;
	lifeImages[0].SetPosition({ 0.3,y,0 });

	lifeImages[1] = lifeImages[0];
	lifeImages[1].SetPosition({ 0.55, y,0 });

	lifeImages[2] = lifeImages[0];
	lifeImages[2].SetPosition({ 0.8, y,0 });

	winImage.Load("Textures/ganaste.png");
	winImage.SetScale({ 2,2,2 });

	finishImage.Load("Textures/PressEscape.png");
	finishImage.SetPosition({ 0,-0.65f,0 });
	finishImage.SetScale({ 1,0.25f,1 });

	pauseImage.Load("Textures/Pause.png");
	pauseImage.SetScale({ 0.75f,0.2f,1 });
}

void Ui::Tick(Plataforms& plataforms, Player& jugador,Coins& coins, bool pause) {
	//pantallas
	if (plataforms.FinishedLevel()) {
		pause = true;
		if ((int)time % 2 == 0) {
			finishImage.Render();
		}
		winImage.Render();
	}

	scoretext.Render();
	scoretext.SetText(std::to_string(coins.GetScore()));

	if (jugador.GetNumberLifes() == 3) {
		lifeImages[0].Render();
		lifeImages[1].Render();
		lifeImages[2].Render();
	}
	if (jugador.GetNumberLifes() == 2) {
		lifeImages[1].Render();
		lifeImages[2].Render();
	}
	if (jugador.GetNumberLifes() == 1) {
		lifeImages[2].Render();
	}

	if (pause)pauseImage.Render();
}

Ui::~Ui()
{

}