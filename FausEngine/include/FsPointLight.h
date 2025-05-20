#ifndef FSPOINTLIGHT
#define FSPOINTLIGHT

#include"FsDLL.h"
#include"FsLight.h"

namespace FausEngine {
	class EXPORTDLL FsPointLight : public FsLight
	{
	public:
		FsPointLight();
		void Load(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
			FsVector3 position, float constant, float linear, float exponent);
		
		void SetPosition(FsVector3);
		void SetConstant(float);
		void SetLinear(float);
		void SetExponent(float);

		FsVector3 GetPosition();
		float GetConstant();
		float GetLinear();
		float GetExponent();
		~FsPointLight();

	protected:
		FsVector3 position;
		float constant, linear, exponent;
	};


}


#endif // !FSPOINTLIGHT
