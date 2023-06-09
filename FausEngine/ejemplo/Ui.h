#ifndef UI
#define UI

#include"../ejemplo/Plataforms.h"
#include"../ejemplo/Player.h"
#include"../ejemplo/Coins.h"

#include"../Motor/Headers/FsText.h"
#include"../Motor/Headers/FsImage.h"

using namespace FausEngine;

class Ui
{
public:
	Ui();
	void Init();
	void Tick(Plataforms&,Player&, Coins& ,bool);
	~Ui();

private:
	FsText scoreText;
	FsImage lifeImages[3];
	FsImage winImage, finishImage, pauseImage;

};



#endif // !UI
