#include"../ejemplo/Ilumination.h"

Ilumination::Ilumination()
{
}

void Ilumination::Init() {
	//LUZCES================
	directionalLight.Load(
		FsVector3(0.2f, -1, 0.2f),
		FsVector3(1.2f, 1.2f, 1.2f),
		//FsVector3(1,0,0), //diffuse
		//FsVector3(0.2f, 0.2f, 0.2f),
		FsVector3(1.7f, 1.7f, 1.7f),
		FsVector3(0.2f, 0.2f, 0.2f));
	//directionalLight.SetActive(false);

	//pointLights.push_back(
	//	std::shared_ptr<FsPointLight>(
	//		new FsPointLight()));

	//pointLights[0]->Load(FsVector3(1, 1, 1),
	//	FsVector3(0, 0, 1),
	//	FsVector3(1, 1, 1),
	//	//player.transform.position,
	//	FsVector3(-3, 2, 0),
	//	2, 0.0f, 0.0f);

	//spotLight.Load(
	//	FsVector3(1, 0, 1),
	//	FsVector3(1, 0, 1),
	//	FsVector3(1, 0, 1),
	//	FsVector3(0, 2, 0),
	//	FsVector3(0, -1, 0),
	//	0.5f, 0.0f, 0.0f);
	//spotLight.SetActive(false);
}

Ilumination::~Ilumination()
{
}