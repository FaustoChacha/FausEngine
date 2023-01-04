#include "../Headers/FsCamera.h"
#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

using namespace FausEngine;

FsCamera::FsCamera() 
{
	position = {0,1,-1};
	yaw = 0;
	pitch = 0;
	roll = 0;
	forward = FsVector3(0.0f, 0.0f, -1.0f);
	up = FsVector3(0, 1, 0);
	right = FsVector3(1, 0, 0);
	//frustrum = new FsVector3(glm::radians(60.0f), 0.1f, 1000.0f);
	frustrum.reset(new FsVector3(glm::radians(60.0f), 0.1f, 1000.0f));
	target = position + forward;
}

FsCamera::FsCamera(FsVector3 startPosition)
{
	position = startPosition;
	yaw = 0;
	pitch = 0;
	roll = 0;
	forward = FsVector3(0.0f, 0.0f, -1.0f);
	up = FsVector3(0,1,0);
	right = FsVector3(1,0,0);
	//frustrum = new FsVector3(glm::radians(60.0f), 0.1f, 1000.0f);
	frustrum.reset(new FsVector3(glm::radians(60.0f), 0.1f, 1000.0f));
	target = position + forward;
}

//getters

FsVector3 FsCamera::GetFrustrum() {
	return *frustrum;
}

FsVector3 FsCamera::GetPosition(){
	return position;
}

float FsCamera::GetPitch() {
	return pitch;
}

float FsCamera::GetYaw() {
	return yaw;
}

float FsCamera::GetRoll() {
	return roll;
}

FsVector3 FsCamera::GetTarget() {
	return target;
}

FsVector3 FsCamera::GetForward() {
	return forward;
}

FsVector3 FsCamera::GetRight() {
	return right;
}

FsVector3 FsCamera::GetUp() {
	return up;
}

//setters

void FsCamera::SetFrustrum(FsVector3 settings){
	frustrum->x = glm::radians(settings.x); //fovy
	frustrum->y = settings.y; //near
	frustrum->z = settings.z; //far
}

void FsCamera::SetPosition(FsVector3 pos) {
	position = pos;
}

void FsCamera::SetPitch(float nPitch) {
	pitch = nPitch;
}

void FsCamera::SetYaw(float nYaw){
	yaw = nYaw;
}

void FsCamera::SetRoll(float nRoll) {
	roll = nRoll;
}

void FsCamera::SetTarget(FsVector3 targ) {
	target = targ;
}

void FsCamera::SetForward(FsVector3 f){
	forward = FsVector3::Normalize(f);
}

void FsCamera::SetRight(FsVector3 r) {
	right = FsVector3::Normalize(r);
}

void FsCamera::SetUp(FsVector3 u) {
	up = FsVector3::Normalize(u);
}

FsCamera::~FsCamera()
{
}
