#ifndef FSOBJECT
#define FSOBJECT

#include"FsDLL.h"

namespace FausEngine {

	class EXPORTDLL FsScene
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