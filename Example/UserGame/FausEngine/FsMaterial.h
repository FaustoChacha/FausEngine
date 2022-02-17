#ifndef FSMATERIAL
#define FSMATERIAL

#include "FsDLL.h"

class EXPORTDLL FsMaterial
{
public:
	FsMaterial();
	FsMaterial(float sIntensity, float shine);

	void UseMaterial(unsigned int specularIntensityLocation, unsigned int shininessLocation);

	~FsMaterial();

private: 
	float specularIntensity;
	float shininess;
};

#endif // !FSMATERIAL