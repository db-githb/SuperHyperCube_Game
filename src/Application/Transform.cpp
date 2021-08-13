
#include "Transform.h"

#include <iostream>

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale    = scale;
}


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
	m_rotation = rot;
}

void Transform::SetScale(glm::vec3 sc)
{
	m_scale = sc;
}

void Transform::AddPosition(glm::vec3 pos)
{
	m_position += pos;
}


void Transform::AddRotation(glm::vec3 rot)
{
	m_rotation += rot;
	std::cout << "x rot: " << m_rotation.x << " y rot: " << m_rotation.y << " z rot: " << m_rotation.z << "\n";
}

void Transform::AddScale(glm::vec3 sc)
{
	m_scale += sc;
}


glm::mat4 Transform::GetModel() const
{

	glm::mat4 positionMatrix = glm::translate(m_position);

	glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.0f),m_rotation.x, glm::vec3(1.0f, 0, 0));
	glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.0f),m_rotation.y, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotationZMatrix = glm::rotate(glm::mat4(1.0f),m_rotation.z, glm::vec3(0, 0, 1.0f));
	
	glm::mat4 scaleMatrix = glm::scale(m_scale);

	glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;
	
	return positionMatrix * scaleMatrix * rotationMatrix;
}

glm::mat4 Transform::GetModel(glm::mat4 parentTransform) const
{

	glm::mat4 positionMatrix = glm::translate(parentTransform,m_position);

	glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0, 0));
	glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotationZMatrix = glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0, 0, 1.0f));

	glm::mat4 scaleMatrix = glm::scale(m_scale);

	glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

	return positionMatrix * scaleMatrix * rotationMatrix;
}

glm::vec3 Transform::GetForwardVector()
{
	const glm::mat4 inverted = glm::inverse(GetModel());
	const glm::vec3 forward = glm::normalize(glm::vec3(inverted[2])) * glm::vec3(1, 1, -1);
	return forward;
}
