#ifndef FSIMAGE2D
#define FSIMAGE2D

#include"FsDLL.h"
#include<iostream>
#include"FsShader.h"

namespace FausEngine {
	class EXPORTDLL FsImage2D 
	{
	public:
		FsImage2D();
		void LoadImage(std::string path);
		void SetPosition(FsVector3);
		void SetRotation(FsVector3);
		void SetScale(FsVector3);
		void Render();
		~FsImage2D();

	private:
		unsigned int textureID;
		unsigned int vbo, ibo, vao;
		FsShader* shader;
		FsTransform transform;
	};
}



#endif // !FSIMAGE2D