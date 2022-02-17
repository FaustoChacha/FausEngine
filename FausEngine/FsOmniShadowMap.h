#ifndef FSOMNISHADOWMAP
#define FSOMNISHADOWMAP


#include "FsDLL.h"
#include "FsShadowMap.h"

class EXPORTDLL FsOmniShadowMap :
	public FsShadowMap
{
public:
	FsOmniShadowMap();

	bool Init(unsigned int width, unsigned int height);

	void Write();

	void Read(unsigned int TextureUnit);

	~FsOmniShadowMap();
};

#endif // !FSOMNISHADOWMAP