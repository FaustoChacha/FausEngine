#ifndef FSIMAGE2D
#define FSIMAGE2D

#include"FsDLL.h"
#include<iostream>
#include"FsShader.h"

namespace FausEngine {
	class EXPORTDLL FsImage
	{
	public:
		FsImage();
		void Load(std::string path);
		void SetPosition(FsVector3);
		void SetRotation(FsVector3);
		void SetScale(FsVector3);
		void Render();
		~FsImage();

	private:
		unsigned int textureID;
		unsigned int vbo, ibo, vao;
		//FsShader* shader;
		std::shared_ptr<FsShader> shader;
		FsTransform transform;
		//FsLog logger;
	};
}



#endif // !FSIMAGE2D
