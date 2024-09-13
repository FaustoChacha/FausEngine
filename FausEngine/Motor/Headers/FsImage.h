#ifndef FSIMAGE2D
#define FSIMAGE2D

#include"FsExport.h"
#include"FsShader.h"

#include<iostream>

namespace FausEngine {
	class FAUSENGINE_API  FsImage
	{
	public:
		FsImage();
		void Load(std::string path);

		void SetPosition(FsVector3);
		void SetRotation(FsVector3);
		void SetScale(FsVector3);
		FsVector3 GetPosition();
		FsVector3 GetRotation();
		FsVector3 GetScale();

		void Render();
		~FsImage();

	private:
		unsigned int textureID;
		unsigned int vbo, ibo, vao;
		std::shared_ptr<FsShader> shader;
		FsTransform transform;
	};
}



#endif // !FSIMAGE2D
