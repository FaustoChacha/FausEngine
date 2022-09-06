#include"../Headers/FsCollider.h"

using namespace FausEngine;

FsCollider::FsCollider()
{
	max = {1,1,1};
	min = {-1,-1,-1};
	id = 0;
}

FsCollider::FsCollider(FsVector3 max, FsVector3 min) {
	this->max = max;
	this->min = min;
	id = 0;
}

FsVector3 FsCollider::GetMax() {
	return max;
}

FsVector3 FsCollider::GetMin() {
	return min;
}

void FsCollider::SetMax(FsVector3 v) {
	max = v;
}
void FsCollider::SetMin(FsVector3 v) {
	min = v;
}

bool FsCollider::CheckCollision(FsCollider& c) {
	return(max.x >= c.min.x &&
		min.x <= c.max.x &&
		max.y >= c.min.y &&
		min.y <= c.max.y);
	//colMax1.z > colMin2.z &&
	//colMin1.z < colMax2.z
}

CollisionDirection FsCollider::GetDirection(FsCollider& c) {
	//if (CheckCollision(c)) {
		if (max.x >= c.min.x && min.x <= c.max.x  ) {
			return CollisionDirection::Xaxis;
		}
		//if (min.x <= c.max.x ) {
		//	return CollisionDirection::mXaxis;
		//}
	//}
	return CollisionDirection::nada;
	//return;
}

FsCollider::~FsCollider()
{
}