#include"../Headers/FsCollider.h"
#include<math.h>

using namespace FausEngine;

FsCollider::FsCollider()
{
	max = {1,1,1};
	min = {-1,-1,-1};
	id = 0;
	right = { 0,0,0 };
	left = {0,0,0};
	down = {0,0,0};
	up = {0,0,0};
	on = true;
}

FsCollider::FsCollider(FsVector3 max, FsVector3 min) {
	this->max = max;
	this->min = min;
	id = 0;
	on = true;
}



void FsCollider::SetMax(FsVector3 v) {
	max = v;
}
void FsCollider::SetMin(FsVector3 v) {
	min = v;
}

void FsCollider::SetRight(FsVector3 p) {
	right = p;
}
void FsCollider::SetLeft(FsVector3 p) {
	left = p;
}

void FsCollider::SetUp(FsVector3 v) {
	up = v;
}

void FsCollider::SetDown(FsVector3 v) {
	down = v;
}

FsVector3 FsCollider::GetMax() {
	return max;
}

FsVector3 FsCollider::GetMin() {
	return min;
}

FsVector3 FsCollider::GetRight() {
	return right;
}

FsVector3 FsCollider::GetLeft() {
	return left;
}

FsVector3 FsCollider::GetPivot() {
	return pivot;
}

FsVector3 FsCollider::GetUp() {
	return up;
}

FsVector3 FsCollider::GetDown() {
	return down;
}



bool FsCollider::CheckCollision(FsCollider& c) {
	return(c.on && 
		max.x >= c.min.x &&
		min.x <= c.max.x &&
		max.y >= c.min.y &&
		min.y <= c.max.y &&
		max.z >= c.min.z &&
		min.z <= c.max.z
		);
}

FsVector3 FsCollider::DistanceToPivot(FsVector3 _pivot, CollisionDirection m) {
	pivot = _pivot;
	if(m==CollisionDirection::MAX)	return FsVector3::Distance(_pivot, (_pivot + max));
	if(m==CollisionDirection::MIN)  return FsVector3::Distance(_pivot, (_pivot + min));
}

CollisionDirection FsCollider::GetDirection(FsCollider& c) {
	if (CheckCollision(c) && c.on) {
		if (left.x <= c.GetMax().x && c.GetLeft().x <= min.x && left.y <= c.GetMax().y /*para Up*/ && up.y >= c.GetMax().y /*para down*/) {
			return CollisionDirection::RIGHT;
		}
		if (right.x >=c.GetMin().x && c.GetRight().x >= max.x && left.y <= c.GetMax().y /*para Up*/ && up.y >= c.GetMax().y/*para down*/) {
			return CollisionDirection::LEFT;
		}
		if (down.y <= c.GetMax().y && c.GetUp().y <= max.y && left.y >= c.GetMax().y) {
			return CollisionDirection::UP;
		}
		if (up.y >= c.GetMin().y && c.GetDown().y >= min.y && left.y ) {
			return CollisionDirection::DOWN;
		}
	}
	return CollisionDirection::nada;
}

FsCollider::~FsCollider()
{
}