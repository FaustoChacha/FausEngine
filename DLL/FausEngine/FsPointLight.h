#ifndef FSPOINTLIGHT
#define FSPOINTLIGHT

#include"FsDLL.h"
#include"FsLight.h"

namespace FausEngine {
	class EXPORTDLL FsPointLight : public FsLight
	{
	public:
		FsPointLight();
		FsPointLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular, 
			FsVector3 position, float constant, float linear, float exponent);
		void Load()override;
		~FsPointLight();

		FsVector3* GetPosition();
		float* GetConstant();
		float* GetLinear();
		float* GetExponent();

	protected:
		FsVector3 position;
		float constant, linear, exponent;
	};


}


#endif // !FSPOINTLIGHT
