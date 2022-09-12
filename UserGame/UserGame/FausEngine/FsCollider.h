#ifndef FSCOLLIDER
#define FSCOLLIDER

#include"FsDLL.h"
#include"FsMaths.h"

namespace FausEngine {
	
	enum class CollisionDirection {
		RIGHT,
		LEFT,
		UP,
		DOWN,
		MAX,
		MIN,
		nada
	};

	class EXPORTDLL FsCollider
	{
	public:
		FsCollider();
		FsCollider(FsVector3 max, FsVector3 min);
		bool CheckCollision(FsCollider&);
		CollisionDirection GetDirection(FsCollider&);
		FsVector3 GetRight();
		FsVector3 GetLeft();
		FsVector3 GetUp();
		FsVector3 GetDown();
		FsVector3 GetMax();
		FsVector3 GetMin();
		FsVector3 GetPivot();
		FsVector3 DistanceToPivot(FsVector3 pivot, CollisionDirection m);
		void SetMax(FsVector3);
		void SetMin(FsVector3);
		void SetRight(FsVector3);
		void SetLeft(FsVector3);
		void SetUp(FsVector3);
		void SetDown(FsVector3);
		~FsCollider();

		int id;
		//bool on;

	private:
		FsVector3 max, min;
		FsVector3 right;
		FsVector3 left;
		FsVector3 up;
		FsVector3 down;
		FsVector3 pivot;
	};
}
#endif // !FSCOLLIDER
