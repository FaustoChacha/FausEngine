#include "../Headers/FsCamera.h"
#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

using namespace FausEngine;

FsCamera::FsCamera() {}

FsCamera::FsCamera(FsVector3 startPosition, FsVector3 startUp, 
	float startYaw, float startPitch)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	forward = FsVector3(0.0f, 0.0f, -1.0f);
	frustrum = new FsVector3(glm::radians(60.0f), 0.1f, 1000.0f);

	updateCameraVectors();
}

FsVector3 FsCamera::getForward() {
	return forward;
}

FsVector3 FsCamera::getRight() {
	return right;
}

FsVector3 FsCamera::getUp() {
	return up;
}

void FsCamera::SetPosition(FsVector3 pos) {
	position = pos;
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

void FsCamera::SetYaw(float nYaw) {
	yaw = nYaw;
}

void FsCamera::SetPitch(float nPitch) {
	pitch = nPitch;
}

void FsCamera::SetRoll(float nRoll) {
	roll = nRoll;
}

void FsCamera::SetFrustrum(FsVector3 settings) {
	frustrum->x = glm::radians(settings.x); //fovy
	frustrum->y = settings.y; //near
	frustrum->z = settings.z; //far
}

FsVector3* FsCamera::GetFrustrum() {
	return frustrum;
}

FsVector3 FsCamera::GetCameraPosition()
{
	return position;
}

FsVector3 FsCamera::GetCameraDirection()
{
	auto resultado = glm::normalize(glm::vec3(forward.x, forward.y, forward.z));
	return FsVector3(resultado.x, resultado.y, resultado.z);
}

void FsCamera::updateCameraVectors()
{
	forward.x = cos(FsVector3::toRadians(yaw)) * cos(FsVector3::toRadians(pitch));
	forward.y = sin(FsVector3::toRadians(pitch));
	forward.z = sin(FsVector3::toRadians(yaw)) * cos(FsVector3::toRadians(pitch));
	auto frontNormalice = FsVector3::Normalize(forward);
	forward = frontNormalice;
	auto rightnormalice = FsVector3::Normalize(FsVector3::Cross(forward, worldUp));
	right = rightnormalice;
	auto upnormalice = FsVector3::Normalize(FsVector3::Cross(right, forward));
	up = upnormalice;
}

FsCamera::~FsCamera()
{
}
