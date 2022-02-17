#ifndef FSSHADER
#define FSSHADER

#include "FsDLL.h"
#include "FsDirectionalLight.h"
#include "FsPointLight.h"
#include "FsSpotLight.h"
#include <string>

namespace FausEngine {

	class EXPORTDLL FsShader
	{
	public:
		FsShader();

		void CreateFromString(const char* vertexCode, const char* fragmentCode);
		void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
		void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation); //NUEVO

		void Validate();

		std::string ReadFile(const char* fileLocation);

		unsigned int GetProjectionLocation();
		unsigned int GetModelLocation();
		unsigned int GetViewLocation();
		unsigned int GetAmbientIntensityLocation();
		unsigned int GetAmbientColourLocation();
		unsigned int GetDiffuseIntensityLocation();
		unsigned int GetDirectionLocation();
		unsigned int GetSpecularIntensityLocation();
		unsigned int GetShininessLocation();
		unsigned int GetEyePositionLocation();
		unsigned int GetOmniLightPosLocation();//NUEVO
		unsigned int GetFarPlaneLocation();//NUEVO

		void SetDirectionalLight(FsDirectionalLight* dLight);
		void SetPointLights(std::vector<FsPointLight*>, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
		void SetSpotLights(std::vector<FsSpotLight*>, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
		void SetTexture(unsigned int textureUnit);
		void SetDirectionalShadowMap(unsigned int textureUnit);
		template<typename Mat4>
		void SetDirectionalLightTransform(Mat4* lTransform);
		template<typename Mat4>
		void SetOmniLightMatrices(std::vector<Mat4> lightMatrices);//NUEVO

		void UseShader();
		void ClearShader();

		~FsShader();

	private:


		unsigned int shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
			uniformSpecularIntensity, uniformShininess,
			uniformTexture,
			uniformDirectionalLightTransform, uniformDirectionalShadowMap,
			uniformOmniLightPos, uniformFarPlane; //NUEVO

		unsigned int uniformLightMatrices[6];//NUEVO

		struct {
			unsigned int uniformColour;
			unsigned int uniformAmbientIntensity;
			unsigned int uniformDiffuseIntensity;

			unsigned int uniformDirection;
		} uniformDirectionalLight;

		unsigned int uniformPointLightCount;

		struct UniformPonitLightStruct {
			unsigned int uniformColour;
			unsigned int uniformAmbientIntensity;
			unsigned int uniformDiffuseIntensity;

			unsigned int uniformPosition;
			unsigned int uniformConstant;
			unsigned int uniformLinear;
			unsigned int uniformExponent;
		};
		UniformPonitLightStruct* uniformPointLight;

		unsigned int uniformSpotLightCount;

		struct UniformSpotLightStruct {
			unsigned int uniformColour;
			unsigned int uniformAmbientIntensity;
			unsigned int uniformDiffuseIntensity;

			unsigned int uniformPosition;
			unsigned int uniformConstant;
			unsigned int uniformLinear;
			unsigned int uniformExponent;

			unsigned int uniformDirection;
			unsigned int uniformEdge;
		};
		UniformSpotLightStruct* uniformSpotLight;

		struct UniformOmniShadowMapStruct{
			unsigned int uniformShadowMap;
			unsigned int uniformFarPlane;
		};
		UniformOmniShadowMapStruct* uniformOmniShadowMap;

		void CompileShader(const char* vertexCode, const char* fragmentCode);
		void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);//NUEVO
		void AddShader(unsigned int theProgram, const char* shaderCode, unsigned int shaderType);

		void CompileProgram(); //NUEVO
	};

}

#endif // !FSSHADER