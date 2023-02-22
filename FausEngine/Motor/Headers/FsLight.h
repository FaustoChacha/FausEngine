#ifndef FSLIGHT
#define FSLIGHT

#include"FsDLL.h"
#include "FsMaths.h"
#include<iostream>

namespace FausEngine {
	class EXPORTDLL FsLight
	{
	public:
		FsLight();
		FsLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular);

		//virtual void Load();
		//virtual void Render();
		bool on;
		
		//FsVector3* GetAmbient();
		//FsVector3* GetDiffuse();
		//FsVector3* GetSpecular();
		std::shared_ptr<FsVector3> GetAmbient();
		std::shared_ptr<FsVector3> GetDiffuse();
		std::shared_ptr<FsVector3> GetSpecular();

		~FsLight();

	protected:
		FsVector3  ambient, diffuse, specular;
		
	};
}

#endif // !FSLIGHT
