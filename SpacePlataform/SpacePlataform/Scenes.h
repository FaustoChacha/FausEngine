#include"FausEngine/FsScene.h"
#include"SpacePlataform.h"
#include"FausEngine/FsSkybox.h"
#include"FausEngine/FsImage.h"
#include"FausEngine/FsImage.h"
#include"FausEngine/FsMaterial.h"
#include"FausEngine//FsMesh.h"
#include"FausEngine/FsCollider.h"
#include"FausEngine/FsPointLight.h"
#include"FausEngine/FsDirectionalLight.h"
#include"FausEngine/FsSpotLight.h"
#include"FausEngine/FsText.h"

#include <iostream>

using namespace std;
using namespace FausEngine;






class Asteroids : public FsScene
{
public:
	Asteroids();
	void Begin()override;
	void CamaraFPS(float, float);
	void ControlFPS(float, float);
	void ControlNave(float, float);
	void Update(float, float)override;
	~Asteroids();

private:
	unique_ptr<SpacePlataform> gR;
	FsMaterial matNave, matAsteroide, matNaveUnlit;
	FsMesh mNave, mAsteroide;
	FsCollider colNave, colAsteroide;
	FsMesh mColMaxNave, mColMinNave, mColMaxAste, mColMinAste;
	FsMaterial matLimitCollider;
	FsPointLight lPointAsteroide;
	FsSpotLight lSpotNave;
	FsSkybox sky;
	FsDireciontalLight luzDireccional;
	FsText texto;
	int vidas = 1000;

};





class Mistery : public FsScene {
public:
	Mistery();
	void Begin()override;
	void CamaraFPS(float, float);
	void ControlFPS(float, float);
	void Update(float, float)override;
	~Mistery();
private: 
	unique_ptr<SpacePlataform> gR;
	FsMesh mPiso, mCasa;
	FsMaterial matPiso, matCasa;
	FsSkybox sky;
	FsSpotLight lSpot;

	FsDireciontalLight lDireccional;

};







