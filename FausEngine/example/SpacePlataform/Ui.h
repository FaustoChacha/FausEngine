#ifndef UI
#define UI

#include"Plataforms.h"
#include"Player.h"
#include"Coins.h"

#include"FausEngine/FsText.h"
#include"FausEngine/FsImage.h"

using namespace FausEngine;

class Ui
{
public:
	Ui();
	void Init();
	void Tick(Plataforms&,Player&, Coins& ,bool);
	~Ui();

private:
	FsText scoretext;
	FsImage lifeImages[3];
	FsImage winImage, finishImage, pauseImage;

};



#endif // !UI
