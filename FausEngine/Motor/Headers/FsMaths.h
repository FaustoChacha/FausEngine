#ifndef FMATHS
#define FMATHS

#include"FsExport.h"

namespace FausEngine {

	struct FAUSENGINE_API  FsVector3 final
	{
	public:
		float x, y, z;

		FsVector3();
		FsVector3(float x, float y, float z);
		FsVector3 operator+(FsVector3 _vector);
		FsVector3 operator-(FsVector3 _vector);
		FsVector3 operator*(float _scalar);
		FsVector3 operator/(float _scalar);
		FsVector3 operator+=(FsVector3 _vector);
		FsVector3 operator-=(FsVector3 _vector);
		//static float Abs(FsVector3 _vector);
		static FsVector3 Normalize(FsVector3);
		static FsVector3 Cross(FsVector3, FsVector3);
		static FsVector3 Distance(FsVector3, FsVector3);
		static float toRadians(float);
		static float toDegress(float);
		static float Clamp(float value, float minVal, float maxVal);
		
		~FsVector3();
	};

	struct FAUSENGINE_API  FsTransform final
	{

	public:
		FsVector3 position;
		FsVector3 rotation;
		FsVector3 scale;

		FsTransform();
		FsTransform(FsVector3 _position, FsVector3 _rotation, FsVector3 _scale);
		~FsTransform();
	};


}

#endif // !FMATHS