#ifndef FSDIRECTIONALLIGHT
#define FSDIRECTIONALLIGHT

#include "FsDLL.h"
#include "FsMaths.h"
#include "FsLight.h"
#include "FsShader.h"
#include<iostream>

namespace FausEngine {
	class EXPORTDLL FsDireciontalLight : public FsLight
	{
	public:
		FsDireciontalLight();
		//FsDireciontalLight(FsVector3 direction,FsVector3 ambient, FsVector3 diffuse, FsVector3 specular);
		void Load(FsVector3 direction, FsVector3 ambient, FsVector3 diffuse, FsVector3 specular);

		//FsVector3* GetDirection();
		std::shared_ptr<FsVector3> GetDirection();
		void SetDirection(FsVector3);

		~FsDireciontalLight();

	private:
		//FsShader* shader;
		//std::shared_ptr<FsShader> shader;
		FsVector3 direction;
	};
}


#endif // !FSDIRECTIONALLIGHT
