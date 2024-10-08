#ifndef FSMATERIAL
#define FSMATERIAL

#include"FsExport.h"
#include"FsMaths.h"

#include<iostream>
//#include"FsShader.h"

namespace FausEngine {

	class FAUSENGINE_API  FsMaterial
	{
	public:
		FsMaterial();
		void Load(FsVector3 ambient, FsVector3 specular, FsVector3 color, float shineness, std::string path);
		void Load(FsVector3 color);

		void SetAmbient(FsVector3);
		void SetSpecular(FsVector3);
		void SetColor(FsVector3);
		void SetShine(float);
		//void SetBind(bool);

		FsVector3 GetAmbient();
		FsVector3 GetSpecular();
		FsVector3 GetColor();
		float GetShine();
		//bool GetBind();
		unsigned int GetTexture();
		bool GetLit();
		~FsMaterial();

	private:
		unsigned int textureID;
		FsVector3 ambient;
		FsVector3 specular;
		FsVector3 color;
		float shineness;

		//bool bind_TexToColor;
		bool lit;
	};
}


#endif