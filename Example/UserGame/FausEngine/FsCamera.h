#ifndef FSCAMERA
#define FSCAMERA

#include "FsDLL.h"
#include "FsMaths.h"

namespace FausEngine {

	class EXPORTDLL FsCamera
	{
	public:
		FsCamera();
		FsCamera(FsVector3 startPosition, FsVector3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);

		void KeyControl(bool* keys, float deltaTime);
		void MouseControl(float xChange, float yChange);

		void SetFrustrum(FsVector3);
		
		FsVector3* GetFrustrum();
		FsVector3 GetCameraPosition();
		FsVector3 GetCameraDirection();
		FsVector3 Forward();
		FsVector3 Right();
		FsVector3 Up();
		float GetPitch();
		float GetYaw();
		float GetRoll();

		void SetPosition(FsVector3);
		void SetPitch(float);
		void SetYaw(float);
		void SetRoll(float);

		template<typename Mat4x4> 
		Mat4x4 CalculateViewMatrix();

		void update();

		~FsCamera();

	private:
		FsVector3 position;
		FsVector3 front;
		FsVector3 up;
		FsVector3 right;
		FsVector3 worldUp;
		FsVector3* frustrum; //fovy, near, far

		float yaw;
		float pitch;
		float roll;

		float moveSpeed;
		float turnSpeed;

		
	};
}



#endif // !FSCAMERA
