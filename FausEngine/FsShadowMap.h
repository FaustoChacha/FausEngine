#ifndef FSSHADOWMAP
#define FSSHADOWMAP

#include "FsDLL.h"

class EXPORTDLL FsShadowMap
{
public:
	FsShadowMap();

	virtual bool Init(unsigned int width, unsigned int height);

	virtual void Write();

	virtual void Read(unsigned int textureUnit);

	unsigned int GetShadowWidth();
	unsigned int GetShadowHeight();

	~FsShadowMap();

protected:
	unsigned int FBO, shadowMap;
	unsigned int shadowWidth, shadowHeight;
};

#endif // !FSSHADOWMAP