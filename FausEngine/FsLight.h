#ifndef FSLIGHT
#define FSLIGHT

#include "FsDLL.h"
#include "FsMaths.h"
#include "FsShadowMap.h"

namespace FausEngine {
	class EXPORTDLL FsLight
	{
	public:
		FsLight();
		FsLight(float shadowWidth, float shadowHeight,
			float red, float green, float blue,
			float aIntensity, float dIntensity);

		virtual void Load();
		void SetActive(bool);
		void SetColour(FsVector3);
		void SetAmbient(float);
		void SetDiffuse(float);

		FsShadowMap* GetShadowMap();

		~FsLight();

	protected:
		bool isOn;
		FsVector3 colour;
		float ambientIntensity;
		float diffuseIntensity;
		FsShadowMap* shadowMap;
	};
}

#endif // !FSLIGHT