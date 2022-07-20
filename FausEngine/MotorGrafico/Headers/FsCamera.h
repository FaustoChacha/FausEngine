#ifndef FSCAMERA
#define FSCAMERA

#include "FsDLL.h"
#include "FsMaths.h"

namespace FausEngine {

	class EXPORTDLL FsCamera
	{
	public:
		FsCamera();
		FsCamera(FsVector3 position, FsVector3 up, float yaw, float pitch);

		FsVector3* GetFrustrum();
		FsVector3 GetCameraPosition();
		FsVector3 GetCameraDirection();
		FsVector3 getForward();
		FsVector3 getRight();
		FsVector3 getUp();
		float GetPitch();
		float GetYaw();
		float GetRoll();

		void SetFrustrum(FsVector3);
		void SetPosition(FsVector3);
		void SetPitch(float);
		void SetYaw(float);
		void SetRoll(float);

		void updateCameraVectors();
		~FsCamera();

	private:
		FsVector3 position;
		FsVector3 forward;
		FsVector3 up;
		FsVector3 right;
		FsVector3 worldUp;
		FsVector3* frustrum; //fovy, near, far
		float yaw;
		float pitch;
		float roll;
	};
}



#endif // !FSCAMERA
