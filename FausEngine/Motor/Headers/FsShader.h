#ifndef SHADER_H
#define SHADER_H

#include "FsExport.h"
#include "FsMaths.h"

#include<string>
#include<map>
#include<vector>

namespace FausEngine {

	enum class uTypeVariables
	{
		uModel, uView, uProjection, uEyePos, //general
		uAmbient, uSpecular, uShininess, uTexture, uColor, uLit, //material
		uDir_direction, uDir_ambient, uDir_diffuse, uDir_specular, //direciotnal light
		//Point & Spot lights
		uPoint_ambient, uPoint_diffuse, uPoint_specular, uPoint_position, 
		uPoint_const, uPoint_lin, uPoint_exp,
		uSpot_Dir,
		//text
		uOrtoProjection, uTextColor,
		//imagen
		utexture
	};
	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};
	class FAUSENGINE_API  FsShader
	{
	public:
		FsShader();
		bool Load(const char* vsFilename,const char* fsFilename);
		bool Load2(const char* vsFilename, const char* fsFilename);
		void Compile(int, int);
		void Use();

		unsigned int GetShaderId() const;
		unsigned int GetUVariableLocation(uTypeVariables);
		unsigned int GetUPointsLocation(uTypeVariables, int);
		unsigned int GetUSpotLocation(uTypeVariables, int);
		~FsShader();
	private:
		//uniforms variables
		std::map<uTypeVariables, unsigned int> uVariablesLocation;
		std::vector<std::map<uTypeVariables, unsigned int>> uPointlights;
		std::vector<std::map<uTypeVariables, unsigned int>> uSpotLights;
		unsigned int ShaderID;
	};
}
#endif // SHADER_H