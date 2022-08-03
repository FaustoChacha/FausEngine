#ifndef FSDIRECTIONALLIGHT
#define FSDIRECTIONALLIGHT

#include "FsDLL.h"
#include "FsMaths.h"
#include "FsLight.h"

namespace FausEngine {
	class EXPORTDLL FsDireciontalLight : public FsLight
	{
	public:
		FsDireciontalLight();
		FsDireciontalLight(FsVector3 direction,FsVector3 ambient, FsVector3 diffuse, FsVector3 specular);
		void Load()override;

		FsVector3* GetDirection();
		void SetDirection(FsVector3);

		~FsDireciontalLight();

	private:
		FsVector3 direction;
	};
}


#endif // !FSDIRECTIONALLIGHT
