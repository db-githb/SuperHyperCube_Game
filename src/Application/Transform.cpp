#include "Transform.h"

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
}

void Transform::AddScale(glm::vec3 sc)
{
	m_scale += sc;
}


glm::mat4 Transform::GetModel() const
{
	glm::mat4 finalMatrix = glm::mat4(1.0f);// glm::scale(positionMatrix, m_scale);
	finalMatrix = glm::rotate(finalMatrix, m_rotation.x, glm::vec3(1.0f, 0, 0));
	finalMatrix = glm::rotate(finalMatrix, m_rotation.y, glm::vec3(0, 1.0f, 0));
	finalMatrix = glm::rotate(finalMatrix, m_rotation.z, glm::vec3(0, 0, 1.0f));
	glm::mat4 positionMatrix = glm::translate(finalMatrix,m_position);

	/*glm::mat4 rotationXMatrix = glm::rotate(m_rotation.x, glm::vec3(1.0f, 0, 0));
	glm::mat4 rotationYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotationZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1.0f));*/
	
	glm::mat4 scaleMatrix = glm::scale(m_scale);

	// glm::mat4 rotationMatrix = //rotationZMatrix * rotationYMatrix * rotationXMatrix;
	//
	// return positionMatrix * rotationMatrix * scaleMatrix;
	

	return positionMatrix;
}