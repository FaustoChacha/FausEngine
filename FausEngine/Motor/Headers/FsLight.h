#ifndef FSLIGHT
#define FSLIGHT

#include"FsExport.h"
#include "FsMaths.h"

namespace FausEngine {
	class FAUSENGINE_API  FsLight
	{
	public:
		FsLight();
		
		void SetActive(bool);
		void SetAmbient(FsVector3);
		void SetDiffuse(FsVector3);
		void SetSpecular(FsVector3);
		
		bool GetActive();
		FsVector3 GetAmbient();
		FsVector3 GetDiffuse();
		FsVector3 GetSpecular();
		~FsLight();

	protected:
		FsVector3  ambient, diffuse, specular;
		bool active;
	};
}

#endif // !FSLIGHT
