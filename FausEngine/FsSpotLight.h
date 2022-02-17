#ifndef FSSPOTLIGHT
#define FSSPOTLIGHT

#include "FsDLL.h"

#include "FsPointLight.h"

namespace FausEngine {

	class EXPORTDLL FsSpotLight : public FsPointLight
	{
	public:
		FsSpotLight();

		FsSpotLight(float shadowWidth, float shadowHeight,
			float near, float far,
			float red, float green, float blue,
			float aIntensity, float dIntensity,
			float xPos, float yPos, float zPos,
			float xDir, float yDir, float zDir,
			float con, float lin, float exp,
			float edg);

		void Load()override;

		void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
			unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation,
			unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation,
			unsigned int edgeLocation);

		void SetDirection(FsVector3);
		void SetCuttOff(float);

		~FsSpotLight();

	private:
		FsVector3 direction;

		float edge, procEdge;

	};
}

#endif // !FSSPOTLIGHT

