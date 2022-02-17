#ifndef FSTEXTURE
#define FSTEXTURE

#include "FsDLL.h"

class EXPORTDLL FsTexture
{
public:
	FsTexture();
	FsTexture(const char* fileLoc);

	bool LoadTexture();

	void UseTexture();
	void ClearTexture();

	~FsTexture();
private:
	unsigned int textureID;
	int width, height, bitDepth;

	const char* fileLocation;
};

#endif // !FSTEXTURE