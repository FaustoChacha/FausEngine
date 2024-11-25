#ifndef ILUMINATION
#define ILUMINATION

#include"FausEngine/FsDirectionalLight.h"
#include"FausEngine/FsPointLight.h"
#include"FausEngine/FsSpotLight.h"

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
