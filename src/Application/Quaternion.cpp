#include "Quaternion.h"


Quaternion::Quaternion()
{
	w = 1;
	v = glm::vec3(0);
}

Quaternion::Quaternion(const glm::vec3& n, float a)
{
	a = a / 360 * (float)M_PI * 2;

	w = cos(a / 2);
	
	v.x = n.x * sin(a / 2);
	v.y = n.y * sin(a / 2);
	v.z = n.z * sin(a / 2);
	
}

const Quaternion Quaternion::Inverted() const
{
	Quaternion q;
	q.w = w;
	q.v.x = -v.x;
	q.v.y = -v.y;
	q.v.z = -v.z;

	return q;
}

const Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion r;
	r.w = w * q.w + glm::dot(v,q.v);
	r.v = v * q.w + q.v * w + glm::cross(v, q.v);

	return r;
}

const glm::vec3 Quaternion::operator*(const glm::vec3& V) const
{
	Quaternion p;
	p.w = 0;
	p.v = V;

	// Could do it this way:
	/*
	const Quaternion& q = (*this);
	return (q * p * q.Inverted()).v;
	*/

	// But let's optimize it a bit instead.
	glm::vec3 vcV = glm::cross(v,V);
	return V + vcV * (2 * w) + glm::cross(v,vcV) * 2.0f;
}

// const Quaternion Quaternion::operator^(float t) const
// {
// 	// Convert the quaternion back into axis/angle
// 	float a;
// 	glm::vec3 n;
//
// 	ToAxisAngle(n, a);
//
// 	// Scale the angle by t
// 	float at = a * t;
//
// 	// Make a new quaternion out of the new value
// 	return Quaternion(n, at);
// }
//
// const Quaternion Quaternion::Slerp(const Quaternion& other, float t) const
// {
// 	const Quaternion& q = *this;
// 	Quaternion r = other;
//
// 	return ((r * q.Inverted()) ^ t) * q;
// }
