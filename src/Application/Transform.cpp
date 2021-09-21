
#include "Transform.h"

#include <iostream>

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale    = scale;
	rotationq = glm::quat(1,0,0,0);
	desiredRotation = glm::quat(1, 0, 0, 0);
}

// Transform::Transform(Transform& trans)
// {
// 	m_position = trans.m_position;
// 	m_rotation = trans.m_rotation;
// 	m_scale		= trans.m_scale;
// }


const glm::vec3& Transform::GetPosition()
{
	return m_position;
}

const glm::vec3& Transform::GetRotation()
{
	return m_rotation;
}

const glm::vec3& Transform::GetScale()
{
	return m_scale;
}

void Transform::SetPosition(glm::vec3 pos)
{
	m_position = pos;
}

void Transform::SetRotation(glm::vec3 rot)
{
	//m_rotation = rot;
	glm::quat rotx = glm::angleAxis(glm::radians(rot.x), glm::vec3(1, 0, 0));
	glm::quat roty = glm::angleAxis(glm::radians(rot.y), glm::vec3(0, 1, 0));
	glm::quat rotz = glm::angleAxis(glm::radians(rot.z), glm::vec3(0, 0, 1));


	desiredRotation = rotx * roty * rotz;
	std::cout << "\n desired rotation - x: " << rot.x << " y: " << rot.y << " z: " << rot.z;
	//rotationq = rotx * roty * rotz;
}

void Transform::SetScale(glm::vec3 sc)
{
	m_scale = sc;
}

void Transform::SetRotationImmediate(glm::vec3 rot)
{
	//m_rotation = rot;
	glm::quat rotx = glm::angleAxis(glm::radians(rot.x), glm::vec3(1, 0, 0));
	glm::quat roty = glm::angleAxis(glm::radians(rot.y), glm::vec3(0, 1, 0));
	glm::quat rotz = glm::angleAxis(glm::radians(rot.z), glm::vec3(0, 0, 1));

	rotationq = rotx * roty * rotz;
	desiredRotation = rotx * roty * rotz;
}

void Transform::AddPosition(glm::vec3 pos)
{
	m_position += pos;
}


void Transform::AddRotation(glm::vec3 rot)
{
	float x = glm::radians(rot.x);
	float y = glm::radians(rot.y);
	float z = glm::radians(rot.z);
	glm::vec3 radRot = glm::vec3(x, y, z);
	m_rotation += radRot;
	std::cout << "x rot: " << m_rotation.x << " y rot: " << m_rotation.y << " z rot: " << m_rotation.z << "\n";

}

void Transform::AddScale(glm::vec3 sc)
{
	m_scale += sc;
}


glm::mat4 Transform::GetModel() const
{

	glm::mat4 positionMatrix = glm::translate(m_position);
	//
	// glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.0f),m_rotation.x, glm::vec3(1.0f, 0, 0));
	// glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.0f),m_rotation.y, glm::vec3(0, 1.0f, 0));
	// glm::mat4 rotationZMatrix = glm::rotate(glm::mat4(1.0f),m_rotation.z, glm::vec3(0, 0, 1.0f));
	//
	glm::mat4 scaleMatrix = glm::scale(m_scale);
	//
	// glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

	glm::mat4 rotationquat = glm::toMat4(rotationq);
	
	return positionMatrix * scaleMatrix * rotationquat;//rotationMatrix;
}

glm::mat4 Transform::GetModel(glm::mat4 parentTransform) const
{

	glm::mat4 positionMatrix = glm::translate(parentTransform,m_position);

	// glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0, 0));
	// glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0, 1.0f, 0));
	// glm::mat4 rotationZMatrix = glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0, 0, 1.0f));

	glm::mat4 scaleMatrix = glm::scale(m_scale);

	// glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

	glm::mat4 rotationquat = glm::toMat4(rotationq);

	return positionMatrix * scaleMatrix * rotationquat;//rotationMatrix;
}

glm::vec3 Transform::GetForwardVector()
{
	const glm::mat4 inverted = glm::inverse(GetModel());
	const glm::vec3 forward = glm::normalize(glm::vec3(inverted[2])) * glm::vec3(1, 1, -1);
	return forward;
}



glm::quat Transform::RotateTowards(glm::quat q1, glm::quat q2, float maxAngle) {
	std::cout << "\n";
	if (maxAngle < 0.001f) {
		// No rotation allowed. Prevent dividing by 0 later.
		std::cout << "edge case 1";
		return q1;
	}

	float cosTheta = glm::dot(q1, q2);

	// q1 and q2 are already equal.
	// Force q2 just to be sure
	if (cosTheta > 0.9999f) {
		return q2;
	}

	// Avoid taking the long path around the sphere
	if (cosTheta < 0) {
		q1 = q1 * -1.0f;
		cosTheta *= -1.0f;
	}

	float angle = acos(cosTheta);

	// If there is only a 2&deg; difference, and we are allowed 5&deg;,
	// then we arrived.
	if (angle < maxAngle) {
		return q2;
	}

	float fT = maxAngle / angle;
	angle = maxAngle;

	glm::quat res = (sin((1.0f - fT) * angle) * q1 + sin(fT * angle) * q2) / sin(angle);
	res = glm::normalize(res);
	return res;

}
