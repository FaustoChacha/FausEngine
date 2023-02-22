#ifndef FSSPOTLIGHT
#define FSSPOTLIGHT

#include"FsDLL.h"
#include"FsPointLight.h"
#include<iostream>

namespace FausEngine {
	class EXPORTDLL FsSpotLight : public FsPointLight
	{
	public:
		FsSpotLight();
		//FsSpotLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
		//	FsVector3 position,FsVector3 direction ,float constant, float linear, float exponent);
		void Load(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
			FsVector3 position, FsVector3 direction, float constant, float linear, float exponent);
		~FsSpotLight();

		//FsVector3* GetDirection();
		std::shared_ptr<FsVector3> GetDirection();

	private:
		FsVector3 direction;
	};

}

#endif // !FSSPOTLIGHT
