#ifndef FSSPOTLIGHT
#define FSSPOTLIGHT
//#pragma once

#include"FsDLL.h"
#include"FsPointLight.h"

namespace FausEngine {
	class EXPORTDLL FsSpotLight : public FsPointLight
	{
	public:
		FsSpotLight();
		FsSpotLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
			FsVector3 position,FsVector3 direction ,float constant, float linear, float exponent);
		void Load()override;
		~FsSpotLight();

		FsVector3* GetDirection();

	private:
		FsVector3 direction;
	};

}

#endif // !FSSPOTLIGHT
