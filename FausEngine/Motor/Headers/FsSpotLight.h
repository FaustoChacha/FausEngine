#ifndef FSSPOTLIGHT
#define FSSPOTLIGHT

#include"FsExport.h"
#include"FsPointLight.h"

namespace FausEngine {
	class FAUSENGINE_API  FsSpotLight : public FsPointLight
	{
	public:
		FsSpotLight();
		void Load(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
			FsVector3 position, FsVector3 direction, float constant, float linear, float exponent);
		
		void SetDirection(FsVector3);
		FsVector3 GetDirection();
		~FsSpotLight();

	private:
		FsVector3 direction;
	};

}

#endif // !FSSPOTLIGHT
