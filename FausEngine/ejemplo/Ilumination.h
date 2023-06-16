#ifndef ILUMINATION
#define ILUMINATION

#include"../Motor/Headers/FsDirectionalLight.h"
#include"../Motor/Headers/FsPointLight.h"
#include"../Motor/Headers/FsSpotLight.h"

#include<vector>
#include<iostream>

using namespace std;
using namespace FausEngine;

class Ilumination
{
public:
	Ilumination();
	void Init();
	~Ilumination();

private:
	FsDireciontalLight directionalLight;
	FsSpotLight spotLight;
	vector<shared_ptr<FsPointLight>>pointLights;
};



#endif // !ILUMINATION
