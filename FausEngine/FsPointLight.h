#ifndef FSPOINTLIGHT
#define FSPOINTLIGHT

#include "FsDLL.h"
#include <vector>

#include "FsLight.h"
#include "FsOmniShadowMap.h"
#include "FsMaths.h"



namespace FausEngine {

	class EXPORTDLL FsPointLight : public FsLight
	{
	public:
		FsPointLight();
		FsPointLight(float shadowWidth, float shadowHeight,
			float near, float far,
			float red, float green, float blue,
			float aIntensity, float dIntensity,
			float xPos, float yPos, float zPos,
			float con, float lin, float exp);

		void Load()override;

		void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
			unsigned int diffuseIntensityLocation, unsigned int positionLocation,
			unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation);


		template<typename Mat4>
		std::vector<Mat4> CalculateLightTransform();

		void SetPosition(FsVector3);
		void SetAttenuation(float, float, float);
		FsVector3* GetPosition();
		float GetFarPlane();//nuevo

		~FsPointLight();

	protected:
		FsVector3 position;
		float constant, linear, exponent;
		float farPlane; //nuervo
	};
}



#endif // !FSPOINTLIGHT