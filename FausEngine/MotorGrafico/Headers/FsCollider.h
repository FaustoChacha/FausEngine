#ifndef FSCOLLIDER
#define FSCOLLIDER

#include"FsDLL.h"
#include"FsMaths.h"

namespace FausEngine {
	
	enum class CollisionDirection {
		Xaxis,
		mXaxis,
		nada
	};

	class EXPORTDLL FsCollider
	{
	public:
		FsCollider();
		FsCollider(FsVector3 max, FsVector3 min);
		bool CheckCollision(FsCollider&);
		CollisionDirection GetDirection(FsCollider&);
		FsVector3 GetMax();
		FsVector3 GetMin();
		void SetMax(FsVector3);
		void SetMin(FsVector3);
		~FsCollider();

		int id;

	private:
		FsVector3 max, min;
	};
}
#endif // !FSCOLLIDER
