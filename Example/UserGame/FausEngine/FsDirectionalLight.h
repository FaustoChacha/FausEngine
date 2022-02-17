#ifndef FSDIRECTIONALLIGHT
#define FSDIRECTIONALLIGHT

#include "FsDLL.h"
#include"FsLight.h"
#include"FsMaths.h"

namespace FausEngine {

	class EXPORTDLL FsDirectionalLight : public FsLight
	{
	public:
		FsDirectionalLight();
		FsDirectionalLight(float shadowWidth, float shadowHeight,
			float red, float green, float blue,
			float aIntensity, float dIntensity,
			float xDir, float yDir, float zDir);

		void Load()override;

		void UseLight(float ambientIntensityLocation, float ambientColourLocation,
			float diffuseIntensityLocation, float directionLocation);

		void SetDirection(FsVector3);

		template<typename Mat4> Mat4 GetProj();
		FsVector3 getDirection();

		~FsDirectionalLight();

	private:
		FsVector3 direction;
	};
}

#endif // !FSDIRECTIONALLIGHT