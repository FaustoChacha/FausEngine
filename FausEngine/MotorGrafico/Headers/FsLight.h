#ifndef FSLIGHT
#define FSLIGHT

#include"FsDLL.h"
#include "FsMaths.h"

namespace FausEngine {
	class EXPORTDLL FsLight
	{
	public:
		FsLight();
		FsLight(FsVector3 ambient, FsVector3 diffuse, FsVector3 specular);

		virtual void Load();
		
		FsVector3* GetAmbient();
		FsVector3* GetDiffuse();
		FsVector3* GetSpecular();

		~FsLight();

	protected:
		FsVector3  ambient, diffuse, specular;
	};
}

#endif // !FSLIGHT
