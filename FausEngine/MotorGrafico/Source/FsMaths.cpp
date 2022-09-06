#include"../Headers/FsMaths.h"
#include<math.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

using namespace FausEngine;

//------------------------FsVector2-------------------------------

FsVector2::FsVector2() {
	this->x = 0;
	this->y = 0;
}

FsVector2::FsVector2(float x, float y) {
	this->x = x;
	this->y = y;
}

//------------------------FsVector3-------------------------------

FsVector3::FsVector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

FsVector3::FsVector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

FsVector3 FsVector3::operator+(FsVector3 _vector) {
	FsVector3 result;
	result.x = this->x + _vector.x;
	result.y = this->y + _vector.y;
	result.z = this->z + _vector.z;
	return result;
}

FsVector3 FsVector3::operator-(FsVector3 _vector) {
	FsVector3 result;
	result.x = this->x - _vector.x;
	result.y = this->y - _vector.y;
	result.z = this->z - _vector.z;
	return result;
}

FsVector3 FsVector3::operator*(float _scalar) {
	FsVector3 result;
	result.x = this->x * _scalar;
	result.y = this->y * _scalar;
	result.z = this->z * _scalar;
	return result;
}

FsVector3 FsVector3::operator/(float _scalar) {
	FsVector3 result;
	result.x = this->x / _scalar;
	result.y = this->y / _scalar;
	result.z = this->z / _scalar;
	return result;
}

FsVector3 FsVector3::operator+=(FsVector3 _vector) {
	this->x += _vector.x;
	this->y += _vector.y;
	this->z += _vector.z;
	return *this;
}

FsVector3 FsVector3::operator-=(FsVector3 _vector) {
	this->x -= _vector.x;
	this->y -= _vector.y;
	this->z -= _vector.z;
	return *this;
}

FsVector3 FsVector3::Normalize(FsVector3 vector) {
	auto res = glm::normalize(glm::vec3(vector.x, vector.y, vector.z));
	return FsVector3(res.x, res.y,res.z);
}

FsVector3 FsVector3::Cross(FsVector3 vector1, FsVector3 vector2) {
	auto resultado = glm::cross(glm::vec3(vector1.x, vector1.y, vector1.z), glm::vec3(vector2.x, vector2.y, vector2.z));
	return FsVector3(resultado.x, resultado.y, resultado.z);
}

FsVector3 FsVector3::Distance(FsVector3 a, FsVector3 b) {
	return {abs((a - b).x), abs((a - b).y), abs((a - b).z) };
}

float FsVector3::toRadians(float degress) {
	return glm::radians(degress);
}

float FsVector3::toDegress(float radians) {
	return glm::degrees(radians);
}

float FsVector3::Clamp(float value, float minVal, float maxVal) {
	return glm::clamp(value, minVal, maxVal);
}

FsVector3::~FsVector3(){}

//........................Transform....................

FsTransform::FsTransform() {
	this->position = { 0,0,0 };
	this->rotation = { 0,0,0 };
	this->scale = { 1,1,1 };
}

FsTransform::FsTransform(FsVector3 _position, FsVector3 _rotation, FsVector3 _scale) {
	this->position = _position;
	this->rotation = _rotation;
	this->scale = _scale;
}

FsTransform::~FsTransform(){}