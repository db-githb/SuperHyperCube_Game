#pragma once
#define  _USE_MATH_DEFINES
#include "../../glm/vec3.hpp"
#include "../../glm/glm.hpp"
#include <cmath>

class Quaternion
{
public:
	Quaternion();
	Quaternion(const glm::vec3& n, float a);
	const Quaternion Inverted() const;
	const Quaternion operator*(const Quaternion& q) const;
	const glm::vec3 operator*(const glm::vec3& V) const;
	//const Quaternion operator^(float t) const;
	//const Quaternion Slerp(const Quaternion& other, float t) const;
	//void ToAxisAngle(glm::vec3& vecAxis, float& flAngle) const;


private:
	float w;
	glm::vec3 v;
};
