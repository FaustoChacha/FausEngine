#include"../Headers/FsCollider.h"
#include<math.h>

using namespace FausEngine;

FsCollider::FsCollider()
{
	boundMax = {1,1,1};
	boundMin = {-1,-1,-1};
	id = 0;
	right = { 0,0,0 };
	left = {0,0,0};
	down = {0,0,0};
	up = {0,0,0};
	active = true;
}

//FsCollider::FsCollider(FsVector3 max, FsVector3 min) {
//	this->max = max;
//	this->min = min;
//	id = 0;
//	on = true;
//}



void FsCollider::SetId(int i) {
	id = i;
}

void FsCollider::SetActive(bool on) {
	active = on;
}

void FsCollider::SetBoundMax(FsVector3 v) {
	boundMax = v;
}
void FsCollider::SetBoundMin(FsVector3 v) {
	boundMin = v;
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

bool FsCollider::GetActive() {
	return active;
}

FsVector3 FsCollider::GetBoundMax() {
	return boundMax;
}

FsVector3 FsCollider::GetBoundMin() {
	return boundMin;
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

int FsCollider::GetId() {
	return id;
}


bool FsCollider::CheckCollision(FsCollider& c) {
	return(c.active && 
		boundMax.x >= c.boundMin.x &&
		boundMin.x <= c.boundMax.x &&
		boundMax.y >= c.boundMin.y &&
		boundMin.y <= c.boundMax.y &&
		boundMax.z >= c.boundMin.z &&
		boundMin.z <= c.boundMax.z
		);
}

FsVector3 FsCollider::DistanceToPivot(FsVector3 _pivot, CollisionDirection m) {
	pivot = _pivot;
	if(m==CollisionDirection::MAX)	return FsVector3::Distance(_pivot, (_pivot + boundMax));
	if(m==CollisionDirection::MIN)  return FsVector3::Distance(_pivot, (_pivot + boundMin));
}

CollisionDirection FsCollider::GetDirection(FsCollider& c) {
	if (CheckCollision(c) && c.active) {
		if (left.x <= c.GetBoundMax().x && c.GetLeft().x <= boundMin.x && left.y <= c.GetBoundMax().y /*para Up*/ && up.y >= c.GetBoundMax().y /*para down*/) {
			return CollisionDirection::RIGHT;
		}
		if (right.x >=c.GetBoundMin().x && c.GetRight().x >= boundMax.x && left.y <= c.GetBoundMax().y /*para Up*/ && up.y >= c.GetBoundMax().y/*para down*/) {
			return CollisionDirection::LEFT;
		}
		if (down.y <= c.GetBoundMax().y && c.GetUp().y <= boundMax.y && left.y >= c.GetBoundMax().y) {
			return CollisionDirection::UP;
		}
		if (up.y >= c.GetBoundMin().y && c.GetDown().y >= boundMin.y && left.y ) {
			return CollisionDirection::DOWN;
		}
	}
	return CollisionDirection::no;
}

FsCollider::~FsCollider()
{
}