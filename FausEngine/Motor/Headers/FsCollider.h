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
		no
	};

	class EXPORTDLL FsCollider
	{
	public:
		FsCollider();

		bool CheckCollision(FsCollider&);
		FsVector3 DistanceToPivot(FsVector3 pivot, CollisionDirection m);
		void Load(int id);

		void SetActive(bool);
		void SetBoundMax(FsVector3);
		void SetBoundMin(FsVector3);
		void SetRight(FsVector3);
		void SetLeft(FsVector3);
		void SetUp(FsVector3);
		void SetDown(FsVector3);

		CollisionDirection GetDirection(FsCollider&);
		bool GetActive();
		FsVector3 GetRight();
		FsVector3 GetLeft();
		FsVector3 GetUp();
		FsVector3 GetDown();
		FsVector3 GetBoundMax();
		FsVector3 GetBoundMin();
		FsVector3 GetPivot();
		int GetId();
		
		~FsCollider();

	private:
		int id;
		bool active;
		bool colliderLoaded;

		//bounds
		FsVector3 boundMax, boundMin;

		//directions
		FsVector3 right;
		FsVector3 left;
		FsVector3 up;
		FsVector3 down;
		FsVector3 pivot;
	};
}
#endif // !FSCOLLIDER
