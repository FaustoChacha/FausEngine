#ifndef FSCAMERA
#define FSCAMERA

#include "FsExport.h"
#include "FsMaths.h"
#include <iostream>

namespace FausEngine {

	class FAUSENGINE_API  FsCamera
	{
	public:
		FsCamera();

		void SetFrustrum(FsVector3);
		void SetPosition(FsVector3);
		void SetPitch(float);
		void SetYaw(float);
		void SetRoll(float);
		void SetTarget(FsVector3);
		void SetForward(FsVector3);
		void SetRight(FsVector3);
		void SetUp(FsVector3);

		FsVector3 GetFrustrum();
		FsVector3 GetPosition();
		float GetPitch();
		float GetYaw();
		float GetRoll();
		FsVector3 GetTarget();
		FsVector3 GetForward();
		FsVector3 GetRight();
		FsVector3 GetUp();

		~FsCamera();

	private:
		FsVector3 position;
		std::shared_ptr<FsVector3> frustrum; //fovy, near, far
		FsVector3 target;

		// Directions (auto normalice)
		FsVector3 forward;
		FsVector3 up;
		FsVector3 right;

		float yaw;
		float pitch;
		float roll;
	};
}



#endif // !FSCAMERA
