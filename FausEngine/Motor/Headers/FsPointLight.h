#ifndef FSPOINTLIGHT
#define FSPOINTLIGHT

#include"FsDLL.h"
#include"FsLight.h"
#include<memory>

namespace FausEngine {
	class EXPORTDLL FsPointLight : public FsLight, std::enable_shared_from_this<FsPointLight>
	{
	public:
		FsPointLight();
		//FsPointLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
		//	FsVector3 position, float constant, float linear, float exponent);
		void Load(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular,
			FsVector3 position, float constant, float linear, float exponent);
		~FsPointLight();

		//FsVector3* GetPosition();
		std::shared_ptr<FsVector3> GetPosition();
		//float* GetConstant();
		//float* GetLinear();
		//float* GetExponent();
		std::shared_ptr<float> GetConstant();
		std::shared_ptr<float> GetLinear();
		std::shared_ptr<float> GetExponent();
	
		void SetPosition(FsVector3);
		void SetDiffuse(FsVector3);
		void SetLinear(float);

	protected:
		FsVector3 position;
		float constant, linear, exponent;
	};


}


#endif // !FSPOINTLIGHT
