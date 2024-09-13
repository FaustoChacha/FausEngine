#ifndef FSOBJECT
#define FSOBJECT

#include"FsExport.h"

namespace FausEngine {

	class FAUSENGINE_API  FsScene
	{
	public:
		FsScene();
		~FsScene();
		//virtual ~FsScene() = 0;

		virtual void Begin() = 0;
		virtual void Update(float deltaTime, float time) = 0;

	};
}
#endif // !FSOBJECT